//
// Created by Zaiyang Li on 05/02/2018.
//

#ifndef RENDERER_WINDOW_HPP
#define RENDERER_WINDOW_HPP

#include <ctime>
#include <vector>
#include "../SDLauxiliary.hpp"
#include "KeyboardEventHandler.hpp"

namespace McRenderFace {
    class DrawFunction {
    public:
        virtual ~DrawFunction() = default;

        virtual void draw(screen *screen, Uint32 elapsedTime) = 0;
        void clearScreen(screen* screen){
            memset(screen->buffer, 0, screen->width * screen->height*sizeof(uint32_t));
        }
    };
    class Window {
    private:
        Uint32 elapsedTime {0};
        Uint32 deltaTime {0};

        int width {0};
        int height {0};

        screen* screenBuffer {nullptr};

        std::vector<KeyboardEventHandler*> handlers;

        DrawFunction* drawFunction {nullptr};
        void notifyEventHandlers(KeyboardEvent event);

        bool shouldStopRender {false};

    public:
        Window(const std::string& title, int width, int height, bool fullscreen);
        ~Window();
        void renderLoop();
        void stop() { shouldStopRender = true; }
        void registerKeyboardEventHandler(KeyboardEventHandler* handler) {
            handlers.push_back(handler);
        };
        void registerDrawFunction(DrawFunction* function) {
            drawFunction = function;
        }
        void update();
        void saveImage(std::string filename);
    };
}


#endif //RENDERER_WINDOW_HPP
