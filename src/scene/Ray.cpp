//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Ray.hpp"

namespace McRenderFace {

    RayHit castRay(const Ray &ray, const Sphere &sphere) {
        return RayHit();
    }

    RayHit castRay(const Ray &ray, const Plane& plane) {

        RayHit hitStatus;
        float denom = glm::dot(ray.forward, plane.normal);
        float num = glm::dot(ray.origin, plane.normal);

        if(denom < EPSILON && denom > -EPSILON) {
            hitStatus.isHit = false;
        }

        hitStatus.isHit = true;
        hitStatus.t = (plane.d - num) / denom;
        hitStatus.position = ray.at(hitStatus.t);
        return hitStatus;
    }

}