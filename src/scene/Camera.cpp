//
// Created by Zaiyang Li on 29/01/2018.
//

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace  McRenderer {


    void Camera::move(vec3 delta) {
        position += delta;
    }

    Camera::Camera(const vec3& positionIn, const vec3& forwardIn, const vec3& upIn)
            : position(positionIn),
              forward(forwardIn),
              up(upIn),
              nearClippingDistance{0.1f},
              farClippingDistance{1000.0f},
              aspectRatio{1.0f},
              focalLength{.02f}
    {
        computeRightVector();
    }


    mat4 Camera::viewingMatrix() {
        return glm::mat4();
    }

    vec3 Camera::toWorldCoordinate(float screenX, float screenY) const {
        vec3 result{position};
        result += right * screenX;
        result += forward * focalLength;
        result += up * screenY;
        return result;
    }
    vec2 Camera::toScreenCoordinate(const vec3& point) {
        return {0.0f, 0.0f};
    }

    void Camera::rotateY(float angle) {
        float radians = static_cast<float>(angle / 180.0f * M_PI);
        float cosAngle = cos(radians);
        float sinAngle = sin(radians);
        mat3 rotation(
                vec3(cosAngle, 0,  -sinAngle),
                vec3(0, 1, 0),
                vec3(sinAngle, 0, cosAngle)
        );

        forward = rotation * forward;
        right = rotation * right;
    }
}