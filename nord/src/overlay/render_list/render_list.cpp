#include "render_list.hpp"

namespace nord::render
{
    void rectangle::render( ImDrawList* dl )
    {
        dl->AddRect( point1, point2, col );
    }

    void text::render( ImDrawList* dl )
    {
        //printf( "'%s'     %f     %f\n", val.c_str(), pos.x, ImGui::CalcTextSize( val.c_str() ).x / 2.0f );
        if ( center )
            pos.x -= ImGui::CalcTextSize( val.c_str() ).x / 2.0f;

        ImGui::GetBackgroundDrawList()->AddText( pos, col, val.c_str() );
    }

    void render_list::begin() noexcept
    {
        mutex.lock();
    }

    void render_list::end() noexcept
    {
        mutex.unlock();
    }

    void render_list::clear() noexcept
    {
        list.clear();
    }

    void render_list::update() noexcept
    {
        mutex.lock();
        list = temp;
        temp.clear();
        mutex.unlock();
    }

    void render_list::draw( ImDrawList* dl )
    {
        for ( const auto& item : list )
            item->render( dl );
    }
}  // namespace nord::render