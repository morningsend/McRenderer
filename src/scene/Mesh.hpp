//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_MESH_HPP
#define RENDERER_MESH_HPP
#define GLM_ENABLE_EXPERIMENTAL
#include <limits>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/extended_min_max.hpp>
#include "Transform.hpp"
#include "Vertex.hpp"
#include "AxisAlignedBoundingBox.hpp"
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
        AxisAlignedBoundingBox computeBoundingBox();
        void computeNormals();
        ~MeshData() = default;;
    };

    struct VertexFace {
        int vertexIndices[3];
    };
    /**
     * Mesh implementing per vertex normal.
     */
    struct Mesh : SceneObject {
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
        void castRay(const Ray& ray, RayHit & rayHit) override ;
        void applyTransform() override;
        static void initializeMeshFromObj(Mesh &mesh, const ObjModel &obj, bool computeNormalAsNeeded = true);
    };
}


#endif //RENDERER_MESH_HPP
