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
#include "../obj/ObjFileReader.hpp"

namespace McRenderFace {
    using namespace std;
    using namespace glm;

    enum class MeshType{ PerFaceNormal, PerVertexNormal };

    struct TriangleUV{
        vec2 uvCoords[3];
        int materialId {0};

        TriangleUV(): uvCoords{vec2(0), vec2(0), vec2(0)} {}
        TriangleUV(vec2 u0, vec2 u1, vec2 u2): uvCoords{ u0, u1, u2} {}
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
        int meshId {0};
        MeshType type {MeshType::PerFaceNormal};
        Transform transform {};
        BoundingBox boundingBox {};
        int materialId {0};
        MeshData* meshData {nullptr};
        bool visible {true};

        // disallowing copying
        Mesh(const Mesh& otherMeth) = delete;
        Mesh(const Mesh&& otherMeth) = delete;

        Mesh() = default;
        ~Mesh() override {
            if(meshData != nullptr) {
                delete meshData;
            }
        }
        void computeBoundingBox();
        RayHit castRay(const Ray& ray) override ;
        static void initializeMeshFromObj(Mesh &mesh, const ObjModel &obj, bool computeNormalAsNeeded = true);
    };
}


#endif //RENDERER_MESH_HPP
