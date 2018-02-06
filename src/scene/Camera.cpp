//
// Created by Zaiyang Li on 29/01/2018.
//

#include "Camera.hpp"

namespace  McRenderer {


    void Camera::move(vec3 delta) {
        position += delta;
    }

    Camera::Camera(const vec4 &positionIn, const vec4 &forwardIn, const vec4 &upIn)
            : position(positionIn),
              forward(forwardIn),
              up(upIn),
              nearClippingDistance{0.1f},
              farClippingDistance{1000.0f},
              aspectRatio{1.0f},
              focalLength{.04f}
    {
        right = glm::normalize(glm::cross(forward, up));
    }

    void Camera::rotate(float angle) {

    }

    mat4 Camera::viewingMatrix() {
        return glm::mat4();
    }

    vec3 Camera::toWorldCoordinate(float screenX, float screenY) const {
        vec3 result{right};
        result *= screenX;
        result += forward * focalLength;
        result += up * screenY;
        return result;
    }
    vec2 Camera::toScreenCoordinate(const vec3& point) {
        return {0.0f, 0.0f};
    }
}