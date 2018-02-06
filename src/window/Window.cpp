//
// Created by Zaiyang Li on 05/02/2018.
//

#include "Window.hpp"

namespace McRenderer {
    void Window::notifyEventHandlers(KeyboardEvent event) {
        for (KeyboardEventHandler *handler : handlers) {
            handler->onKeyActive(event);
        }
    }

    Window::Window(const std::string& title, int width = 256, int height = 256, bool fullscreen = false) {
        if(width < 1 || height < 1) {
            throw std::runtime_error("window size cannot be negative");
        }
        screenBuffer = InitializeSDL(title.c_str(), width, height, fullscreen);
    }

    Window::~Window() {
        if(screenBuffer != nullptr) {
            KillSDL(screenBuffer);
        }
    }

    void Window::renderLoop() {
        elapsedTime = SDL_GetTicks();

        while(!shouldStopRender && NoQuitMessageSDL()) {
            update();
            if(drawFunction!= nullptr){
                drawFunction->draw(screenBuffer, deltaTime);
            }
            SDL_Renderframe(screenBuffer);
        }
    }

    void Window::update() {
        uint32_t currentClockTicks = SDL_GetTicks();
        deltaTime = currentClockTicks - elapsedTime;
        elapsedTime = currentClockTicks;

        int keystates = 0;

        const Uint8* keys = SDL_GetKeyboardState(&keystates);
        std::cout << keystates << " keys are pressed"<<std::endl;
        std::cout << "last frame took " << deltaTime << " ms to render" << std::endl;
        if(keystates > 0) {
            notifyEventHandlers(KeyboardEvent{keys[0]});
        }
    }
}
