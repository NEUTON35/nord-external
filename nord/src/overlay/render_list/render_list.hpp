#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "../../imgui/imgui.h"

namespace nord::render
{
    struct base
    {
        virtual void render( ImDrawList* dl ) = 0;
        virtual ~base() = default;
    };

    struct rectangle : public base
    {
        rectangle( ImVec2 point1, ImVec2 point2, ImColor col ) : point1{ point1 }, point2{ point2 }, col{ col }
        {
        }

        ImVec2 point1, point2;
        ImColor col;

        void render( ImDrawList* dl ) override;
    };

    struct text : public base
    {
        text( ImVec2 pos, ImColor col, const std::string& text, bool center )
            : pos{ pos },
              col{ col },
              val{ text },
              center{ center }
        {
        }

        std::string val;
        ImColor col;
        ImVec2 pos;
        bool center;

        void render( ImDrawList* dl ) override;
    };

    class render_list
    {
       public:
        template< typename T, typename... Args >
        void add( const Args&... args )
        {
            temp.emplace_back( new T{ args... } );
        }

        void begin() noexcept;
        void end() noexcept;
        void clear() noexcept;
        void draw( ImDrawList* dl );
        void update() noexcept;

       private:
        std::vector< std::shared_ptr< base > > temp;

        std::vector< std::shared_ptr< base > > list;
        std::mutex mutex;
    };
}  // namespace nord::render
