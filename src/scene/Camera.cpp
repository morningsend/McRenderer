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

    }

    void Camera::rotate(float angle) {

    }

    mat4 Camera::viewingMatrix() {
        return glm::mat4();
    }

    vec3 Camera::toWorldCoordinate(float screenX, float screenY) const {

        return glm::vec3();
    }
}