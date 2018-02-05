//
// Created by Zaiyang Li on 29/01/2018.
//

#ifndef RENDERER_CAMERA_HPP
#define RENDERER_CAMERA_HPP

#include <glm/glm.hpp>
namespace McRenderer {
    using namespace glm;
    struct Camera {
        vec3 position{0.0f, 0.0f, 0.0f};
        vec3 forward{0.0f, 0.0f, -1.0f};
        vec3 right{1.0f, 0.0f, 0.0f};
        vec3 up{0.0f, 1.0f, 0.0f};

        float aspectRatio{1.0f};
        float nearClippingDistance{0.001f};
        float farClippingDistance{100.0f};
        float focalLength{0.035f};
        mat4 viewingMatrix();

        explicit Camera(const vec4& positionIn, const vec4& forwardIn, const vec4& upIn);

        void move(vec3 translation);
        void rotate(float angle);
        // range -0.5 to 0.5
        vec3 toWorldCoordinate(float screenX, float screenY) const;
        vec2 toScreenCoordinate(const vec3& point);
    };

}



#endif //RENDERER_CAMERA_HPP
