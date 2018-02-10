//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_MESHTESTS_HPP
#define RENDERER_MESHTESTS_HPP

#endif //RENDERER_MESHTESTS_HPP

#include <catch.hpp>
#include "../../src/IOUtility.hpp"

TEST_CASE("Computing bounding box is axis aligned", "[FaceMeshData computeBoundingBox]") {
    FaceMeshData data;
    data.vertices.push_back(vec3(1, -1, 1));
    data.vertices.push_back(vec3(-1, 1, -1));
    data.vertices.push_back(vec3(0, 0, 0));
    BoundingBox box = data.computeBoundingBox();

    REQUIRE((box.min[0] == -1.0f && box.min[1] == -1.0f && box.min[2] == -1.0f));
    REQUIRE((box.max[0] == 1.0f && box.max[1] == 1.0f && box.max[2] == 1.0f));
}