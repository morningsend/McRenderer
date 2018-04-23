//
// Created by Zaiyang Li on 25/01/2018.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Transform.hpp"

namespace McRenderFace {
    glm::mat4 Transform::matrix() {
        // identity matrix;
        mat4 mat(1.0f);
        mat *= glm::rotate(mat, rotation.z, vec3(0.0f, 0.0f, 1.0f));
        mat *= glm::rotate(mat, rotation.y, vec3(0.0f, 1.0f, 0.0f));
        mat *= glm::rotate(mat, rotation.x, vec3(1.0f, 0.0f, 0.0f));
        mat *= glm::scale(mat, scale);
        mat[3] = vec4(translation, 1.0f);
        return mat;
    }
}
