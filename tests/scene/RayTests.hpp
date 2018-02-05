//
// Created by Zaiyang Li on 31/01/2018.
//
#include "../catch.hpp"

#include "../../src/scene/Ray.hpp"

using namespace McRenderer;
using namespace glm;
TEST_CASE("ray cast on triangle will not hit if ray has 0 direction", "[rayCast]") {

}

TEST_CASE("ray cast on triangle will fail if parallel with the plane", "[rayCast]") {

}

TEST_CASE("good case", "[rayCast]") {
    Triangle triangle;
    triangle.vertices[0] = vec3(0.0f, 0.0f,0.0f);
    triangle.vertices[1] = vec3(1.0f, 0.0f,0.0f);
    triangle.vertices[2] = vec3(0.0f, 1.0f,0.0f);

    triangle.computeNormal();

    Ray ray;
    ray.origin = vec3(0,0,1);
    ray.forward = vec3(0.2, 0.2, -1);

    RayHit result = castRay(ray. &triangle);

    REQUIRE(result.isHit == true);
}

