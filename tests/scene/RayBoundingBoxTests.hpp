//
// Created by Zaiyang Li on 23/04/2018.
//

#ifndef RENDERER_RAYBOUNDINGBOXTESTS_HPP
#define RENDERER_RAYBOUNDINGBOXTESTS_HPP

#include <catch.hpp>
#include "../../src/scene/AxisAlignedBoundingBox.hpp"

using namespace McRenderFace;
using namespace glm;

TEST_CASE("Compute intersection of AABB with ray should yield true", "[AxisAlignedBoundingBox castRay]") {
    AxisAlignedBoundingBox box;
    box.min = vec3(-1);
    box.max = vec3(1,-1,1);


    Ray ray;
    ray.origin = vec3(0,0,2);
    RayHit hit;

    for(float x = -1; x <= 1; x += 0.2f) {
        for(float z = -1; z <= 1; z +=0.2f) {
            hit.isHit = false;
            ray.forward = normalize(vec3(x,-1,z) - ray.origin);
            box.castRay(ray, hit);
            REQUIRE(hit.isHit);
        }
    }
}

TEST_CASE("Intersection of Ray inside a AABB should return true", "[AxisAlignedBoundingBox castRay]") {
    AxisAlignedBoundingBox box;
    box.min = vec3(-1);
    box.max = vec3(1);
    Ray ray(vec3(0), vec3(0,0,1));
    RayHit hit;
    hit.isHit = false;
    box.castRay(ray, hit);
    REQUIRE(hit.isHit);
}

#endif //RENDERER_RAYBOUNDINGBOXTESTS_HPP
