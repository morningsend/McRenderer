//
// Created by Zaiyang Li on 05/02/2018.
//

#include "RenderTargetDrawFunction.hpp"

namespace McRenderFace {
    void RenderTargetDrawFunction::draw(screen *screen, Uint32 deltaTime) {
        int width = renderTarget->getWidth();
        int height = renderTarget->getHeight();
        if (width != screen->width && height != screen->height) {
            throw runtime_error("screen must be same size as render target");
        }
        renderer->render(*scene, *renderTarget);
        if(gammaCorrect) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    vec3 gammaCorrected = glm::pow(renderTarget->getColor(x, y), vec3(1.0f/2.2f));
                    PutPixelSDL(screen, x, y, gammaCorrected);
                };
            };
        } else {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    PutPixelSDL(screen, x, y, renderTarget->getColor(x, y));
                };
            };
        }
    }
}