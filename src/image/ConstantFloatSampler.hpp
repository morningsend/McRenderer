//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_FLOATSAMPLER_HPP
#define RENDERER_FLOATSAMPLER_HPP

#include "UvSampler1D.hpp"

namespace McRenderFace {
    class ConstantFloatSampler final: public UvSampler1D{
    private:
        float value;
    public:
        explicit ConstantFloatSampler(float valueIn) : value{valueIn} {}

        ~ConstantFloatSampler() override = default;

        float sample(float u, float v) const override { return value; }

        float sample(vec2 uv) const override { return value; }
    };
}


#endif //RENDERER_FLOATSAMPLER_HPP
