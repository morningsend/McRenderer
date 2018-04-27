//
// Created by Zaiyang Li on 05/02/2018.
//

#include "Window.hpp"
#include <thread>
#include <chrono>
namespace McRenderFace {
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
        const Uint8* states = SDL_GetKeyboardState(&keystates);
        std::cout << "last frame took " << deltaTime << " ms to render" << std::endl;
        if(states[SDL_SCANCODE_LEFT]) {
            notifyEventHandlers(KeyboardEvent{SDL_SCANCODE_LEFT});
        } else
        if(states[SDL_SCANCODE_RIGHT]) {
            notifyEventHandlers(KeyboardEvent{SDL_SCANCODE_RIGHT});
        } else
        if(states[SDL_SCANCODE_UP]) {
            notifyEventHandlers(KeyboardEvent{SDL_SCANCODE_UP});
        } else
        if(states[SDL_SCANCODE_DOWN]) {
            notifyEventHandlers(KeyboardEvent{SDL_SCANCODE_DOWN});
        } else
        if(states[SDL_SCANCODE_A]) {
            notifyEventHandlers(KeyboardEvent{SDL_SCANCODE_A});
        }else
        if(states[SDL_SCANCODE_S]) {
            notifyEventHandlers(KeyboardEvent{SDL_SCANCODE_S});
        }

    }

    void Window::saveImage(std::string filename) {
        SDL_SaveImage(screenBuffer, filename.c_str());
    }

    void Window::renderFrame() {
        update();
        if(drawFunction!= nullptr){
            drawFunction->draw(screenBuffer, deltaTime);
        }
        SDL_Renderframe(screenBuffer);
    }
}
