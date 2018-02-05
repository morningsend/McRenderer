//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Ray.hpp"

namespace McRenderer {

    bool castRay(const Ray &ray, const Sphere &sphere, vec3 &hitLocation) {

        return false;
    }

    bool castRay(const Ray &ray, const Triangle &triangle, vec3 &hitLocation) {

        return false;
    }

    /**
     * Moller-Trumbore intersection algorithm
     * https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
     *
     * 1. intersection ray with plane the triangle lies in
     * 2. if did not found a point of intersection, i.e. ray is parallel to plane, return
     * 3. if found point of intersection, test if point lies on triangle.
     *
     * @param ray
     * @param triangle
     * @return
     */
    RayHit castRay(const Ray &ray, const Triangle *triangle) {
        float d = glm::dot(triangle->normal, triangle->vertices[0]);
        RayHit hit = castRay(ray, Plane{triangle->normal, d});

        if(!hit.isHit) {
            return hit;
        }

        vec3 edge1 = triangle->vertices[1] - triangle->vertices[0];
        vec3 edge2 = triangle->vertices[2] - triangle->vertices[0];



    }

    RayHit castRay(const Ray &ray, const Plane plane) {

        RayHit hitStatus;
        float denom = glm::dot(ray.forward, plane.normal);
        float num = glm::dot(ray.origin, plane.normal);

        if(denom < EPSILON && denom > -EPSILON) {
            hitStatus.isHit = false;
        }

        hitStatus = true;
        hitStatus.t = (plane.d - num) / denom;
        hitStatus.location = ray.at(hitStatus.t);
        return hitStatus;
    }
}