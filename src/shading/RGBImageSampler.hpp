//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_RGBIMAGESAMPLER_HPP
#define RENDERER_RGBIMAGESAMPLER_HPP

#include <glm/glm.hpp>
#include "UvSampler3D.hpp"

namespace McRenderFace {
    using namespace glm;
    class RGBImageSampler : public UvSampler3D{
    public:
        vec3 sample(float u, float v) const override;
        vec3 sample(vec2 uv) const override;
    };
}


#endif //RENDERER_RGBIMAGESAMPLER_HPP
