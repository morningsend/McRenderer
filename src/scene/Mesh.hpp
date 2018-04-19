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
#include "SceneObject.hpp"

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
    struct Mesh : SceneObject{
        MeshType type {MeshType::PerFaceNormal};
        MeshData* meshData {nullptr};

        // disallowing copying
        Mesh(const Mesh& otherMeth) = delete;
        Mesh(const Mesh&& otherMeth) = delete;

        Mesh() = default;
        ~Mesh() override {
            if(meshData != nullptr) {
                delete meshData;
            }
        }
        void computeBoundingBox() override;
        RayHit castRay(const Ray& ray) override ;
        void applyTransform() override;
        static void initializeMeshFromObj(Mesh &mesh, const ObjModel &obj, bool computeNormalAsNeeded = true);
    };
}


#endif //RENDERER_MESH_HPP
