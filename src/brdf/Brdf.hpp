//
// Created by Zaiyang Li on 27/03/2018.
//

#ifndef RENDERER_BRDF_HPP
#define RENDERER_BRDF_HPP

#include <cmath>
#include <glm/glm.hpp>

namespace McRenderFace {
    using namespace glm;

    class Brdf {
    public:
        virtual ~Brdf() = default;
        virtual float pdf(vec3 v, vec3 l, vec3 n) { return static_cast<float>(1 / M_2_PI); }
    };
}

#endif //RENDERER_BRDF_HPP
