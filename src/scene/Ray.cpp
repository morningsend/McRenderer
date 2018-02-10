//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Ray.hpp"

namespace McRenderFace {

    RayHit castRay(const Ray &ray, const Sphere &sphere) {
        return RayHit();
    }

    /**
     * Moller-Trumbore intersection algorithm
     * https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
     *
     * 1. intersection ray with plane the triangle lies in
     * 2. if did not found a point of intersection, i.e. ray is parallel to plane, return
     * 3. if found point of intersection, test if point lies on triangle.
     *  https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
     * @param ray
     * @param triangle
     * @return
     */
    RayHit castRay(const Ray &ray, const Triangle& triangle) {
        RayHit hit;

        vec3 edge1 = triangle.vertices[1] - triangle.vertices[0];
        vec3 edge2 = triangle.vertices[2] - triangle.vertices[0];

        vec3 rayTriangle = ray.origin - triangle.vertices[0];
        vec3 P = glm::cross(ray.forward, edge2);
        vec3 Q = glm::cross(rayTriangle, edge1);

        float determinant = glm::dot(P, edge1);

        // determinant is zero, no intersection
        if(abs(determinant) < EPSILON) {
            return hit;
        }
        determinant = 1.0f / determinant;
        //barycentric coordinates
        float u = glm::dot(P, rayTriangle) * determinant;
        float v = glm::dot(Q, ray.forward) * determinant;
        float t = glm::dot(Q, edge2) * determinant;
        // point is inside triangle if both uv coordinates are in [0, 1] and u+v < 1;
        if(u < 0.0f || u > 1.0f) {
            return hit;
        } else if(v < 0.0f || v > 1.0f) {
            return hit;
        } else if(v + u > 1.0f) {
            return hit;
        }

        hit.isHit = true;
        hit.t = t;
        hit.position = ray.at(t);

        return hit;
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
    /**
     * Andrew Woo fast ray AABB box intersection
     * @param ray
     * @param box
     * @return
     */
    RayHit castRay(const Ray &ray, const BoundingBox &box) {
#define MIDDLE 2
#define LESS 1
#define GREATER 2
        RayHit hit;
        bool isInside = true;
        char quadrant[3] = { MIDDLE, MIDDLE, MIDDLE};
        vec3 tMax;

        for(int i = 0; i < 3; i++) {
            if(ray.origin[i] < box.min[i]) {
                isInside = false;
                quadrant[i] = LESS;
                tMax[i] = (box.min[i] - ray.origin[i]) / ray.forward[i];
            }else if(ray.origin[i] > box.max[i]) {
                isInside = false;
                quadrant[i] = GREATER;
                tMax[i] = (box.max[i] - ray.origin[i]) / ray.forward[i];
            }
        }

        if(isInside) {
            hit.position = ray.origin;
            hit.isHit = true;
            return hit;
        }

        int candidatePlane = 0;
        candidatePlane = (tMax[0] > tMax[1]) ? 0 : 1;
        candidatePlane = (tMax[candidatePlane] > tMax[2]) ? candidatePlane : 2;
        hit.t = tMax[candidatePlane];

        vec3 point = ray.at(tMax[candidatePlane]);
        hit.position = point;
        hit.isHit = true;

        if(point[0] < (box.min[0] - EPSILON) || (point[0] > box.max[0] + EPSILON)) {
            hit.isHit = false;
            return hit;
        }

        if(point[1] < (box.min[1] - EPSILON) || (point[1] > box.max[1] + EPSILON)) {
            hit.isHit = false;
            return hit;
        }

        if(point[2] < (box.min[2] - EPSILON) || (point[2] > box.max[2] + EPSILON)) {
            hit.isHit = false;
            return hit;
        }

        return hit;
    }
}