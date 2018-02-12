//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Mesh.hpp"

namespace McRenderFace {
    void Mesh::computeBoundingBox() {
        boundingBox = (meshData != nullptr) ? meshData->computeBoundingBox() : BoundingBox();

    }

    BoundingBox MeshData::computeBoundingBox() {
        BoundingBox boundingBox;

        if(triangles.size() < 2) {
            return boundingBox;
        }
        boundingBox.max = vec3(FLT_MIN);
        boundingBox.min = vec3(FLT_MAX);
        for(auto tri : triangles) {
            boundingBox.min = glm::min(boundingBox.min, tri.vertices[0]);
            boundingBox.max = glm::max(boundingBox.max, tri.vertices[0]);

            boundingBox.min = glm::min(boundingBox.min, tri.vertices[1]);
            boundingBox.max = glm::max(boundingBox.max, tri.vertices[1]);

            boundingBox.min = glm::min(boundingBox.min, tri.vertices[2]);
            boundingBox.max = glm::max(boundingBox.max, tri.vertices[2]);
        }
        return boundingBox;
    }

    vec2 TriangleGeometry::barycentric() {
        return glm::vec2(0, 1);
    }

    void TriangleGeometry::computeNormal() {
        vec3 e1 = vertices[1] - vertices[0];
        vec3 e2 = vertices[2] - vertices[0];
        normal = glm::normalize(glm::cross(e1, e2));
    }
}