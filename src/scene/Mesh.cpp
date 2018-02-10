//
// Created by Zaiyang Li on 25/01/2018.
//

#include "Mesh.hpp"

namespace McRenderFace {

    void Mesh::computeBoundingBox() {
        boundingBox.max = vec3(std::numeric_limits<float>.max());
        boundingBox.min = vec3(std::numeric_limits<float>.min());
        for(auto tri : vertices) {
            boundingBox.min = glm::min(boundingBox.min, tri.position);
            boundingBox.max = glm::max(boundingBox.max, tri.position);
        }
    }
}