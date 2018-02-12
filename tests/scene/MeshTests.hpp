//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_MESHTESTS_HPP
#define RENDERER_MESHTESTS_HPP



#include <catch.hpp>
#include "../../src/IOUtility.hpp"
#include "../../src/scene/Mesh.hpp"

TEST_CASE("Computing bounding box is axis aligned", "[FaceMeshData computeBoundingBox]") {
    MeshData data;
    Triangle triangle(vec3(1, -1, 1), vec3(-1, 1, -1), vec3(-1, 1, -1), vec3(0));
    data.triangles.push_back(triangle);
    BoundingBox box = data.computeBoundingBox();

    CHECK(box.min[0] == -1.0f);
    CHECK(box.min[1] == -1.0f);
    CHECK(box.min[2] == -1.0f);

    CHECK(box.max[0] == 1.0f);
    CHECK(box.max[1] == 1.0f);
    CHECK(box.max[2] == 1.0f);
}

TEST_CASE("computing bounding box on empty mesh return (0,0,0,0,0,0)", "[FaceMeshData computeBoundingBox") {
    MeshData data;
    BoundingBox box = data.computeBoundingBox();
    REQUIRE((box.min.x == 0 &&
            box.min.y == 0 &&
            box.min.z == 0
            ));

    CHECK(box.max.x == 0);
    CHECK(box.max.y == 0);
    CHECK(box.max.z == 0);
}

#endif //RENDERER_MESHTESTS_HPP