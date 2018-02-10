//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Mesh.hpp"

namespace McRenderFace {
    void Mesh::computeBoundingBox() {
        boundingBox = (meshData != nullptr) ? meshData->computeBoundingBox() : BoundingBox();

    }

    BoundingBox VertexMeshData::computeBoundingBox() {
        BoundingBox boundingBox;
        if(vertices.size() < 2) {
            return boundingBox;
        }

        boundingBox.max = vec3(FLT_MIN);
        boundingBox.min = vec3(FLT_MAX);
        for(auto tri : vertices) {
            boundingBox.min = glm::min(boundingBox.min, tri.position);
            boundingBox.max = glm::max(boundingBox.max, tri.position);
        }
        return boundingBox;
    }

    BoundingBox FaceMeshData::computeBoundingBox() {
        BoundingBox boundingBox;

        if(vertices.size() < 2) {
            return boundingBox;
        }
        boundingBox.max = vec3(FLT_MIN);
        boundingBox.min = vec3(FLT_MAX);
        for(auto vert : vertices) {
            boundingBox.min = glm::min(boundingBox.min, vert);
            boundingBox.max = glm::max(boundingBox.max, vert);
        }
        return boundingBox;
    }
}