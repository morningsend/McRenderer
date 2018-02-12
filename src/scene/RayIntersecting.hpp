//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_RAYINTERSECTING_HPP
#define RENDERER_RAYINTERSECTING_HPP

#include "Ray.hpp"

namespace McRenderFace {
    struct RayIntersecting {
        virtual RayHit castRay(const Ray& ray) = 0;
        virtual ~IRayIntersecting() = default;
    };
}

#endif //RENDERER_RAYINTERSECTING_HPP
