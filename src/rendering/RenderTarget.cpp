//
// Created by Zaiyang Li on 31/01/2018.
//

#include "RenderTarget.hpp"

namespace McRenderFace {

    RenderTarget::~RenderTarget() {

    }

    RenderTarget::RenderTarget(int widthIn, int heightIn)
            : width{widthIn}, height{heightIn} {
        if (width < 1 || height < 1) {
            throw runtime_error{"error"};
        }
        frameBuffer = new vec3[width * height];
    }

    void RenderTarget::setColor(int x, int y, glm::vec3 colour) {
        frameBuffer[x + y * width] = colour;
    }

    int RenderTarget::getWidth() {
        return width;
    }
    int RenderTarget::getHeight() {
        return height;
    }

    void RenderTarget::fillColor(int xMin, int yMin, int xMax, int yMax, vec3 colour) {
        assert(xMin <= xMax);
        assert(yMin <= yMax);

        xMin = xMin < 0 ? 0 : xMin;
        xMax = xMax >= height ? height - 1 : xMax;
        yMin = yMin < 0 ? 0 : yMin;
        yMax = yMax >= height ? height - 1 : yMax;
        for(int y = yMin; y <= yMax; y++)
            for(int x = xMin; x <= xMax; x++) {
             {
                // fill framebuffer at (x,y) with colour;
                frameBuffer[x + y * width] = colour;
            }
        }
    }



    vec3& RenderTarget::operator()(int x, int y) {
        return frameBuffer[x + y * width];
    }

    vec3& RenderTarget::getColor(int x, int y) {
        return frameBuffer[x + y * width];
    }

    void RenderTarget::clear() {
        memset(static_cast<void*>(frameBuffer), 0, sizeof(vec3) * width * height);
    }

    void RenderTarget::savePngOutput(const string &path, bool sRGB) {
        Mat image(height, width, CV_32FC3);
        Mat ldr;
        float gamma = sRGB ? 2.2f : 1.0f;
        Ptr<TonemapDurand> tonemapper = createTonemapDurand(gamma);

        // copy framebuffer to opencv image.
        for(int jj = 0; jj < height; jj++) {
            for(int ii = 0; ii < width; ii++){
                vec3 colour = frameBuffer[ii + jj * width];
                image.at<Vec3f>(jj, ii) = Vec3f(colour.z, colour.y, colour.x);
            }
        }
        //do tonemapping
        tonemapper->process(image, ldr);

        // convert to 8 bit and write output to png.
        //ldr.convertTo(image, CV_8UC3);
        Mat png(height, width, CV_8UC3);
        for(int jj = 0; jj < height; jj++) {
            for(int ii = 0; ii < width; ii++){
                Vec3f colour = ldr.at<Vec3f>(jj, ii);
                uchar r = static_cast<uchar>(colour[2] * 255);
                uchar g = static_cast<uchar>(colour[1] * 255);
                uchar b = static_cast<uchar>(colour[0] * 255);
                png.at<Vec3b>(jj, ii) = Vec3b(b,g,r);
            }
        }
        imwrite(path.c_str(), png);
    }


    void RenderTarget::saveHdrOutput(const string &path) {
        Mat image(height, width, CV_32FC3);

        // copy framebuffer to opencv image.
        for(int jj = 0; jj < height; jj++) {
            for(int ii = 0; ii < width; ii++){
                vec3 colour = frameBuffer[ii + jj * width];
                image.at<Vec3f>(jj, ii) = Vec3f(colour.z, colour.y, colour.x);
            }
        }
        imwrite(path.c_str(), image);
    }
}