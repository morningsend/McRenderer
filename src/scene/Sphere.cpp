//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Sphere.hpp"

namespace McRenderFace {
    /**
     * method to compute intersection of ray and sphere.
     * @param ray
     * @return
     */
    void Sphere::castRay(const Ray &ray, RayHit& hit) {
        vec3 hypotenuse = origin - ray.origin;

        // project raySphere onto ray direction to determine the minimum distance between
        // sphere center and ray path. if distance less than or equal to radius, we have a hit.
        vec3 adjacent = glm::dot(hypotenuse, ray.forward) * ray.forward;

        vec3 opposite = hypotenuse - adjacent;

        float miniumDistance2 = glm::dot(opposite, opposite);
        float r2 = radius * radius;
        if(miniumDistance2 > r2) {
            hit.isHit = false;
            return;
        }
        hit.isHit = true;
        // there are usually two points of intersection, we take the nearest one.
        hit.t = glm::dot(ray.forward, adjacent) - sqrt(r2 - miniumDistance2);
        hit.position = ray.at(hit.t);
        // computing normal is just to normalize a point on a sphere.
        // on unit sphere, each point is the same as the normal at that point.
        hit.normal = (hit.position - origin) / radius;
    }

    void Sphere::computeBoundingBox() {
        boundingBox.min = origin - vec3(radius);
        boundingBox.max = origin + vec3(radius);
    }

    /**
     * Sphere is not analytically surface, it can only be scaled uniformly.
     * It does not have orientation, so we dont need to rotate it.
     */
    void Sphere::applyTransform() {
        origin += transform.translation;
        radius *= transform.scale.x;
        transform.reset();
    }
}
