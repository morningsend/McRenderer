//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_OBJREADERTESTS_HPP
#define RENDERER_OBJREADERTESTS_HPP
#include <catch.hpp>

#include "../../src/obj/ObjFileReader.hpp"

using namespace McRenderFace;

TEST_CASE("None existent file should throw error", "[ObjFileReader read()]") {
    ObjFileReader reader("idontexist.obj");
    try {
        auto models = reader.read();
        REQUIRE(false);
    }catch (std::runtime_error& e) {
        REQUIRE(true);
    }
}

TEST_CASE("cube file should return 8 vertices and 24 triangles", "[ObjFileReader read()2]") {
    ObjFileReader reader("models/cube.obj");
    auto models = reader.read();

    CHECK(models.size() == 1);
    CHECK(models["cube"]->vertices.size() == 8);
    CHECK(models["cube"]->faces.size() == 12);
    ObjFace& face = models["cube"]->faces[0];

    CHECK(face.vertex[0] == 1);
    CHECK(face.uvCoord[0] == 1);
    CHECK(face.normal[0] == 1);

    CHECK(face.vertex[1] == 2);
    CHECK(face.uvCoord[1] == 2);
    CHECK(face.normal[1] == 1);

    CHECK(face.vertex[2] == 3);
    CHECK(face.uvCoord[2] == 3);
    CHECK(face.normal[2] == 1);
}

TEST_CASE("face data with missing texture coordinate should work", "[ObjFileReader read()3]") {
    ObjFileReader reader("models/icosahedron.obj");
    auto models = reader.read();
    CHECK(models.size() == 1);

    ObjModel* model = models["icosahedron"];
    CHECK(model->faces.size() == 20);
    CHECK(model->vertices.size() == 12);

}
#endif //RENDERER_OBJREADERTESTS_HPP
