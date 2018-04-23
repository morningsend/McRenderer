//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_RAYINTERSECTING_HPP
#define RENDERER_RAYINTERSECTING_HPP

#include "Ray.hpp"

namespace McRenderFace {
    struct RayIntersecting {
        virtual void castRay(const Ray& ray, RayHit& rayHit) = 0;
        virtual ~RayIntersecting() = default;
    };
}

#endif //RENDERER_RAYINTERSECTING_HPP
