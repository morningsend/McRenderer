//
// Created by Zaiyang Li on 29/01/2018.
//

#ifndef RENDERER_CAMERA_HPP
#define RENDERER_CAMERA_HPP

#include <glm/glm.hpp>
namespace McRenderFace {
    using namespace glm;
    struct Camera {
        vec3 position{0.0f, 0.0f, 0.0f};
        vec3 forward{0.0f, 0.0f, -1.0f};
        vec3 right{1.0f, 0.0f, 0.0f};
        vec3 up{0.0f, 1.0f, 0.0f};

        float fieldOfViewDegrees{40.0f};
        float aspectRatio{1.0f};
        float nearClippingDistance{0.001f};
        float farClippingDistance{100.0f};
        float focalLength{0.035f};
        float apertureFStop{2.8};
        mat4 viewingMatrix();

        explicit Camera(const vec3& positionIn, const vec3& forwardIn, const vec3& upIn);
        explicit Camera() = default;
        void move(vec3 translation);
        void rotateY(float angle);
        // range -1 to 1
        vec3 toWorldCoordinate(float screenX, float screenY) const;
        vec2 toScreenCoordinate(const vec3& point);

        void computeRightVector(){
            right = glm::normalize(glm::cross(up, forward));
        }
    };

}



#endif //RENDERER_CAMERA_HPP
