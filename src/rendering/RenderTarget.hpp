//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RENDERTARGET_HPP
#define RENDERER_RENDERTARGET_HPP

#include <glm/vec3.hpp>
#include "../Exception.hpp"

namespace McRenderer {
    using namespace glm;
    class RenderTarget {
    private:
        int width;
        int height;
        vec3* frameBuffer;
    public:
        RenderTarget(int widthIn = 256, int heightIn = 256);
        ~RenderTarget();
        void setColor(int x, int y, vec3 colour);
        void fillColor(int xMin, int yMin, int xMax, int yMax, vec3 colour);
        int getWidth();
        int getHeight();
    };
}


#endif //RENDERER_RENDERTARGET_HPP
