//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Mesh.hpp"

namespace McRenderFace {
    void Mesh::computeBoundingBox() {
        boundingBox = (meshData != nullptr) ? meshData->computeBoundingBox() : BoundingBox();
    }

    RayHit Mesh::castRay(const Ray &ray) {
        // optimization: if ray does not hit bounding box, terminate.
        RayHit hit = boundingBox.castRay(ray);
        if(!hit.isHit) {
            return hit;
        }
        const auto& triangles = meshData -> triangles;
        RayHit closest;
        for(auto tri : triangles) {
            hit = tri.castRay(ray);
            if(hit.isHit && hit.t > 0 && hit.t < closest.t) {
                closest = hit;
            }
        }
        return closest;
    }

    BoundingBox MeshData::computeBoundingBox() {
        BoundingBox boundingBox;

        if(triangles.size() < 1) {
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

    void MeshData::invertNormals() {
        for(auto& tri : triangles) {
            tri.invertNormal();
        }
    }

    void MeshData::computeNormals() {
        for(auto& tri: triangles) {
            tri.computeNormal();
        }
    }
}