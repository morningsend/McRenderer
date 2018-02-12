//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_SAMPLER1D_HPP
#define RENDERER_SAMPLER1D_HPP

#include <glm/glm.hpp>

namespace McRenderFace {
    using namespace glm;
    class UvSampler1D {
    public:
        virtual ~UvSampler1D() = default;
        virtual float sample(vec2 uv) const = 0 ;
        virtual float sample(float u, float v) const = 0;
    };
}

#endif //RENDERER_SAMPLER1D_HPP
