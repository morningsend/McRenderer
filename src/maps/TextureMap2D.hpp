//
// Created by Zaiyang Li on 24/04/2018.
//

#ifndef RENDERER_TEXTURE2D_HPP
#define RENDERER_TEXTURE2D_HPP
#include <string>
#include <glm/glm.hpp>
#include <opencv/cv.hpp>
#include <iostream>

namespace McRenderFace {
    using namespace std;
    using namespace glm;
    enum TextureColourSpace {
        Linear,
        SRGB
    };
    class TextureMap2D {
    private:
        TextureColourSpace colourSpace{Linear};
        vec3* textureData{nullptr};
        bool loaded {false};
        void load(const string& path);
        void convertToLinear();
        int width{0};
        int height{0};

    public:
        TextureMap2D(const string& path, TextureColourSpace colourSpaceIn = TextureColourSpace::Linear):
                colourSpace{colourSpaceIn} {
            load(path);
            if(loaded && colourSpace == SRGB) {
                convertToLinear();
                colourSpace = Linear;
            }
        }
        ~TextureMap2D();
        TextureColourSpace getColourSpace() {
            return colourSpace;
        }
        vec3 sampleBilinear(vec2 uv) const;
        vec3 sampleNearest(vec2 uv) const;
        vec3 samplePoint(int x, int y) const;
        int getWidth()const{ return width; }
        int getHeight()const{return height; }

    };
    void testLoadingImage(const string& path);
}


#endif //RENDERER_TEXTURE2D_HPP
