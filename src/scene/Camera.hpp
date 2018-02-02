//
// Created by Zaiyang Li on 29/01/2018.
//

#ifndef RENDERER_CAMERA_HPP
#define RENDERER_CAMERA_HPP

#include <glm/glm.hpp>
namespace McRenderer {
    using namespace glm;
    struct Camera {
        vec3 position;
        vec3 forward;
        vec3 up;

        float aspectRatio;
        float nearClippingDistance;
        float farClippingDistance;
        float focalLength;
        mat4 viewingMatrix();

        explicit Camera(const vec4& positionIn, const vec4& forwardIn, const vec4& upIn);

        void move(vec3 translation);
        void rotate(float angle);
        // range -0.5 to 0.5
        vec3 toWorldCoordinate(float screenX, float screenY) const;
    };

}



#endif //RENDERER_CAMERA_HPP
