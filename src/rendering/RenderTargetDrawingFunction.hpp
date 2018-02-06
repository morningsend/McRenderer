//
// Created by Zaiyang Li on 05/02/2018.
//

#ifndef RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP
#define RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP

#include "../window/Window.hpp"
#include "RenderTarget.hpp"

namespace McRenderer {
    /**
     * Writes the content of render target to screen buffer to be shown in SDL window every time draw
     * method is called.
     */
    class RenderTargetDrawingFunction : DrawFunction{
    private:
        RenderTarget* renderTarget;

    public:
        /**
         * Writes the content of render target to screen.
         * Will throw exception if render target and screen have different width and height.
         * @param screen
         * @param deltaTime
         */
        void draw(screen* screen, Uint32 deltaTime);
    };
}


#endif //RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP
