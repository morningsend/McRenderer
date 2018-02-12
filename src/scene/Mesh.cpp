//
// Created by Zaiyang Li on 25/01/2018.
//

#include <iostream>
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
            if(hit.isHit && hit.t < closest.t) {
                closest = hit;
            }
        }
        return closest;
    }

    void Mesh::initializeMeshFromObj(Mesh &mesh, const ObjModel &obj, bool computeNormalAsNeeded) {
        if(mesh.meshData != nullptr) {
            delete mesh.meshData;
        }

        MeshData* meshData = new MeshData();
        mesh.meshData = meshData;

        //construct triangles
        Triangle tri;
        TriangleUV triUv;

        for(vec3 v: obj.vertices) {
            std::cout << v.x << ' ' << v.y << ' ' << v.z << endl;
        }
        const vector<vec3> vertices = obj.vertices;
        const vector<vec3> normals = obj.normals;
        const vector<vec2> uvCoords = obj.uvCoords;
        int i = 0;
        for(auto& face: obj.faces) {

            tri.vertices[0] = vertices[face.vertex[0]];
            tri.vertices[1] = vertices[face.vertex[1]];
            tri.vertices[2] = vertices[face.vertex[2]];

            if(uvCoords.size() > 0) {
                triUv.uvCoords[0] = uvCoords[face.uvCoord[0]];
                triUv.uvCoords[1] = uvCoords[face.uvCoord[0]];
                triUv.uvCoords[2] = uvCoords[face.uvCoord[0]];
            }

            if(computeNormalAsNeeded && normals.size() < 1)
                tri.computeNormal(true);
            else if(normals.size() > 0){
                tri.normal = vertices[face.normal[0]];
            }

            meshData->triangles.push_back(tri);
            meshData->uvCoords.push_back(triUv);

            cout << i << ':' << face.vertex[0] << ' ' << face.vertex[1] << ' ' << face.vertex[2] << endl;
            cout << i << ':' << tri.vertices[0].x << ' '
                    << tri.vertices[0].y << ' '
                    << tri.vertices[0].z << ' '
                    <<endl;
            cout << i << ':' << tri.vertices[1].x << ' '
                 << tri.vertices[1].y << ' '
                 << tri.vertices[1].z << ' '
                 <<endl;
            cout << i << ':' << tri.vertices[2].x << ' '
                 << tri.vertices[2].y << ' '
                 << tri.vertices[2].z << ' '
                 <<endl;
            i++;

        }
        mesh.computeBoundingBox();
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