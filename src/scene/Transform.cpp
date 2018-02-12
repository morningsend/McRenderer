//
// Created by Zaiyang Li on 25/01/2018.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Transform.hpp"

glm::mat4 McRenderFace::Transform::matrix() {
    // identity matrix;
    mat4 mat(1.0f);
    mat[3] = vec4(translation, 1.0f);
    mat = glm::rotate(mat, rotation.x, vec3(1.0f, 0.0f, 0.0f));
    mat = glm::scale(mat, scale);
    return mat;
}
