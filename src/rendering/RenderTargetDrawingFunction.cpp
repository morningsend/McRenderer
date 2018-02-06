//
// Created by Zaiyang Li on 05/02/2018.
//

#include "RenderTargetDrawingFunction.hpp"
#include "../SDLauxiliary.hpp"

namespace McRenderer {
    void RenderTargetDrawingFunction::draw(screen *screen, Uint32 deltaTime) {
        int width = renderTarget->getWidth();
        int height = renderTarget->getHeight();
        if(width != screen->width && height != screen->height) {
            throw runtime_error("screen must be same size as render target");
        }

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++){
                PutPixelSDL(screen, x, y, renderTarget->getColor(x,y));
            };
        };
    }
}
