//
// Created by Zaiyang Li on 14/02/2018.
//

#ifndef RENDERER_SPHERETEST_HPP
#define RENDERER_SPHERETEST_HPP

#include <catch.hpp>
#include "../../src/scene/Sphere.hpp"

using namespace McRenderFace;
using namespace glm;

TEST_CASE("Sphere ray intersection should return false if no hit", "[Sphere castRay]") {
    Ray ray{vec3(2,0,2), vec3(0,0,-1)};
    Sphere sphere{1, vec3(0)};
    RayHit hit = sphere.castRay(ray);
    REQUIRE(!hit.isHit);
}

TEST_CASE("Sphere ray intersection should return closest point if hit", "[Sphere castRay]") {
    Ray ray{vec3(0,0,2), vec3(0,0,-1)};
    Sphere sphere{1, vec3(0)};
    RayHit hit = sphere.castRay(ray);
    REQUIRE(hit.isHit);
    CHECK(hit.t == 1.0f);
    CHECK(hit.position.x == 0);
    CHECK(hit.position.y == 0);
    CHECK(hit.position.z == 1.0f);

    CHECK(hit.normal.x == 0);
    CHECK(hit.normal.y == 0);
    CHECK(hit.normal.z == 1.0f);
}

TEST_CASE("Sphere boundingBox should return correct values", "[Sphere computeBoundingBox]") {
    Sphere sphere(1, vec3(0));
    sphere.computeBoundingBox();
    CHECK(sphere.boundingBox.min.x == -1);
    CHECK(sphere.boundingBox.min.y == -1);
    CHECK(sphere.boundingBox.min.z == -1);

    CHECK(sphere.boundingBox.max.x == 1);
    CHECK(sphere.boundingBox.max.y == 1);
    CHECK(sphere.boundingBox.max.z == 1);
}

TEST_CASE("Sphere transformation should translate origin", "[Sphere applyTransform]") {
    Sphere sphere(1, vec3(0));
    sphere.transform.translation = vec3(5);
    sphere.applyTransform();

    CHECK(sphere.origin.x == 5);
    CHECK(sphere.origin.y == 5);
    CHECK(sphere.origin.z == 5);
}
#endif //RENDERER_SPHERETEST_HPP
