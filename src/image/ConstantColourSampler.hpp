//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_CONSTANTCOLOURSAMPLER_HPP
#define RENDERER_CONSTANTCOLOURSAMPLER_HPP

#include "UvSampler3D.hpp"

namespace McRenderFace {
    class ConstantColourSampler final: public UvSampler3D {
    private:
        vec3 colour;
    public:
        explicit ConstantColourSampler(vec3 colourIn): colour {colourIn} {}

        ~ConstantColourSampler() override = default;

        vec3 sample(float u, float v) const override {
            return colour;
        }

        vec3 sample(vec2 uv) const override {
            return colour;
        }
    };
}


#endif //RENDERER_CONSTANTCOLOURSAMPLER_HPP
