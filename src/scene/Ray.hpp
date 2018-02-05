//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_RAY_HPP
#define RENDERER_RAY_HPP

#include <glm/glm.hpp>
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

namespace McRenderer {
    using namespace glm;
    
    const float EPSILON = 0.00001f;

    struct Ray {
        vec3 origin{0.0f, 0.0f, 0.0f};
        vec3 forward{1.0f, 0.0f, 0.0f};

        Ray(float originX, float originY, float originZ, float forwardX, float forwardY, float forwardZ)
            :origin{originX, originY, originZ}, forward{forwardX, forwardY, forwardZ} {};
        Ray(const vec3& originIn, const vec3& forwardIn): origin{originIn}, forward{forwardIn} {};

        vec3 at(float t) const{ return origin + forward * t; };
    };

    struct RayHit {
        bool isHit {false};
        float t {0.0f};
        vec3 position { 0.0f, 0.0f, 0.0f};
        Triangle* triangle { nullptr };
    };

    RayHit castRay(const Ray& ray, const Triangle& triangle, vec3& hitLocation, float t);
    RayHit castRay(const Ray& ray, const Sphere& sphere, vec3& hitLocation, float t);
    RayHit castRay(const Ray& ray, const Triangle* triangle);
    /**
     * computes intersection of ray with plane.
     * plane equation: n*r = d
     * ray equation: r(t) = p + vt
     * n * r(t) = d => n*p + n*v * t = d => t = (d - n*p)/(n*v)
     * @param ray
     * @param plane
     * @return
     */
    RayHit castRay(const Ray& ray, const Plane plane);
}


#endif //RENDERER_RAY_HPP
