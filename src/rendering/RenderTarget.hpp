//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RENDERTARGET_HPP
#define RENDERER_RENDERTARGET_HPP
#include <string>
#include <glm/vec3.hpp>
#include <opencv/cv.hpp>
#include "../Exception.hpp"
#include <stdexcept>


namespace McRenderFace {
    using namespace glm;
    using namespace std;
    using namespace cv;
    class RenderTarget {
    private:
        int width;
        int height;
        vec3* frameBuffer;
    public:
        RenderTarget(int widthIn = 256, int heightIn = 256);
        ~RenderTarget();
        void setColor(int x, int y, vec3 colour);
        vec3& getColor(int x, int y);
        void fillColor(int xMin, int yMin, int xMax, int yMax, vec3 colour);
        int getWidth();
        int getHeight();
        void saveHdrOutput(const string &path);
        void savePngOutput(const string &path, bool sRGB = true);
        vec3& operator()(int x, int y);
        void clear();
    };
}


#endif //RENDERER_RENDERTARGET_HPP
