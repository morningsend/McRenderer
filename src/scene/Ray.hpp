//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_RAY_HPP
#define RENDERER_RAY_HPP

#include <cmath>
#include <glm/glm.hpp>
#include <limits>
#include "Plane.hpp"

namespace McRenderFace {
    using namespace glm;
    using namespace std;

    const float EPSILON = 0.00001f;

    struct Ray {
        vec3 origin{0.0f, 0.0f, 0.0f};
        vec3 forward{1.0f, 0.0f, 0.0f};

        Ray(float originX, float originY, float originZ, float forwardX, float forwardY, float forwardZ)
            :origin{originX, originY, originZ}, forward{forwardX, forwardY, forwardZ} {};
        Ray(const vec3& originIn, const vec3& forwardIn): origin{originIn}, forward{forwardIn} {};
        Ray(): Ray(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f) { }

        vec3 at(float t) const{ return origin + forward * t; };
    };

    struct RayHit {
        bool isHit {false};
        float t = MAXFLOAT;
        vec3 position { 0.0f };
        vec3 normal { 0.0f};
    };

    /**
     * Computes intersection of ray with a mathematical sphere of equation (x - a)^2 + (y - b)^2 + (z - c)^2 = r^2
     * @param ray
     * @param sphere
     * @return
     */
    RayHit castRay(const Ray& ray, const Plane& plane);
}


#endif //RENDERER_RAY_HPP
