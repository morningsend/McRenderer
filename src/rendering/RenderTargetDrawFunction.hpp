//
// Created by Zaiyang Li on 05/02/2018.
//

#ifndef RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP
#define RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP

#include "../window/Window.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"

namespace McRenderFace {
    /**
     * Writes the content of render target to screen buffer to be shown in SDL window every time draw
     * method is called.
     */
    class RenderTargetDrawFunction : public DrawFunction{
    private:
        SimpleScene* scene;
        RenderTarget* renderTarget;
        Renderer* renderer;
    public:
        RenderTargetDrawFunction(SimpleScene* sceneIn, Renderer* rendererIn, RenderTarget* renderTargetIn)
                : scene{sceneIn},
                  renderer{rendererIn},
                  renderTarget{renderTargetIn}
        {
        }
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
