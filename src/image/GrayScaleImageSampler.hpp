//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_GRAYSCALEIMAGESAMPLER_HPP

#define RENDERER_GRAYSCALEIMAGESAMPLER_HPP

#include "UvSampler1D.hpp"
#include <glm/glm.hpp>
namespace McRenderFace {
    using namespace glm;

    class GrayScaleImageSampler : public UvSampler1D {
    public:
        float sample(float u, float v) const override;
        float sample(vec2 uv) const override;
    };
}

#endif