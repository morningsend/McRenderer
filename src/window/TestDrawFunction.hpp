//
// Created by Zaiyang Li on 05/02/2018.
//

#ifndef RENDERER_TESTDRAWINGFUNCTION_HPP
#define RENDERER_TESTDRAWINGFUNCTION_HPP

#include "Window.hpp"

namespace McRenderFace {

    class TestDrawFunction : public DrawFunction {
    public:
        void draw(screen *screen, Uint32 elapsedTime) override {
            clearScreen(screen);
            glm::vec3 colour{1.0f, 0.0f, 0.0f};
            for(int i=0; i<1000; i++)
            {
                uint32_t x = static_cast<uint32_t>(rand() % screen->width);
                uint32_t y = static_cast<uint32_t>(rand() % screen->height);
                PutPixelSDL(screen, x, y, colour);
            }
        }
        ~TestDrawFunction(){}
    };
}


#endif //RENDERER_TESTDRAWINGFUNCTION_HPP
