//
// Created by Zaiyang Li on 31/01/2018.
//

#include "Triangle.hpp"

void McRenderFace::Triangle::computeNormal() {
    vec3 edge1 = vertices[1] - vertices[0];
    vec3 edge2 = vertices[2] - vertices[0];

    normal = glm::cross(edge1, edge2);

}

void McRenderFace::Triangle::computeNormal(bool normalize) {
    computeNormal();
    if(normalize) {
        normal = glm::normalize(normal);
    }
}
