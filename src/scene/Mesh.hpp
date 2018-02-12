//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_MESH_HPP
#define RENDERER_MESH_HPP
#include <limits>
#include <vector>
#include "Transform.hpp"
#include "Vertex.hpp"
#include "BoundingBox.hpp"
#include "../shading/Material.hpp"

namespace McRenderFace {
    using namespace std;
    using namespace Shading;
    enum class MeshType{ PerFaceNormal, PerVertexNormal };

    struct TriangleGeometry {
        vec3 vertices[3];
        vec3 normal;

        TriangleGeometry(vec3 v1, vec3 v2, vec3 v3, vec3 normalIn)
                : vertices{v1, v2, v3}, normal{normalIn} { }

        vec2 barycentric();
        void computeNormal();
    };

    struct TriangleUV{
        vec2 r0[3];
        int materialId;
    };

    struct MeshData {
        vector<TriangleGeometry> triangles;
        vector<TriangleUV> uvCoords;
        BoundingBox computeBoundingBox();
        ~MeshData(){};
    };

    struct VertexFace {
        int vertexIndices[3];
    };
    /**
     * Mesh implementing per vertex normal.
     */
    struct Mesh {
        int meshId;
        MeshType type;
        Transform transform;
        BoundingBox boundingBox;
        int materialId;
        MeshData* meshData;

        void computeBoundingBox();

        ~Mesh(){
            if(meshData != nullptr) {
                delete meshData;
            }
        }
        void setMaterial(Material* material);
    };
}


#endif //RENDERER_MESH_HPP
