//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_MESH_HPP
#define RENDERER_MESH_HPP
#include <limits>
#include <vector>
#include <glm/glm.hpp>

#include "Transform.hpp"
#include "Vertex.hpp"
#include "BoundingBox.hpp"
#include "Triangle.hpp"

namespace McRenderFace {
    using namespace std;
    using namespace glm;

    enum class MeshType{ PerFaceNormal, PerVertexNormal };

    struct TriangleUV{
        vec2 r0[3];
        int materialId {0};

        TriangleUV(): r0{vec2(0), vec2(0), vec2(0)} {}
        TriangleUV(vec2 u0, vec2 u1, vec2 u2): r0{ u0, u1, u2} {}
    };

    struct MeshData {
        vector<Triangle> triangles;
        vector<TriangleUV> uvCoords;

        void invertNormals();
        BoundingBox computeBoundingBox();
        void computeNormals();
        ~MeshData() = default;;
    };

    struct VertexFace {
        int vertexIndices[3];
    };
    /**
     * Mesh implementing per vertex normal.
     */
    struct Mesh : RayIntersecting{
        int meshId;
        MeshType type {MeshType::PerFaceNormal};
        Transform transform {};
        BoundingBox boundingBox {};
        int materialId {0};
        MeshData* meshData;
        bool visible {true};
        void computeBoundingBox();

        ~Mesh() override {
            if(meshData != nullptr) {
                delete meshData;
            }
        }
        RayHit castRay(const Ray& ray) override ;
    };
}


#endif //RENDERER_MESH_HPP
