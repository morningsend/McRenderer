//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Triangle.hpp"

namespace McRenderFace {

    void Triangle::computeNormal(bool normalize) {
        vec3 edge1 = vertices[1] - vertices[0];
        vec3 edge2 = vertices[2] - vertices[0];

        normal = glm::cross(edge1, edge2);
        if (normalize) {
            normal = glm::normalize(normal);
        }
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
     * @return RayHit
     */
    RayHit McRenderFace::Triangle::castRay(const McRenderFace::Ray &ray) {
        RayHit hit;
        const Triangle& triangle = *this;
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

    void Triangle::invertNormal(bool recompute) {
        vec3 temp = vertices[1];
        vertices[1] = vertices[2];
        vertices[2] = temp;
        normal *= -1;
        if(recompute) {
            computeNormal();
        }
    }

    /**
     * p = u(v1 - v0) + v(v2 - v0)
     * p = u*v1 + v*v2 - (u + v)*v0
     * @param u
     * @param v
     * @return
     */

    vec3 Triangle::positionOf(float u, float v) {
        return vertices[1] * u + vertices[2] * v - vertices[0] * (u+v);
    }

    vec2 Triangle::barycentricCoordOf(vec3 point) {
        return glm::vec2();
    }
}