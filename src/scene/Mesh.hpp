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
#include "Material.hpp"

namespace McRenderFace {
    using namespace std;

    enum class MeshType{ PerFaceNormal, PerVertexNormal };

    struct MeshData {
        virtual BoundingBox computeBoundingBox() = 0;
        ~MeshData(){};
    };
    struct TriangleFace {
        int vertexIndices[3];
        int normalIndices[3];
        int uvIndices[3];
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
        Material material;
        MeshData* meshData;

        void computeBoundingBox();
    };

    struct VertexMeshData : MeshData {
        vector<VertexFace> triangles;
        vector<Vertex> vertices;

        BoundingBox computeBoundingBox() override;
    };

    struct FaceMeshData : MeshData {
        vector<vec3> vertices;
        vector<vec3> normals;
        vector<vec2> uvCoords;
        vector<TriangleFace> faces;
        BoundingBox computeBoundingBox() override;
    };
}


#endif //RENDERER_MESH_HPP
