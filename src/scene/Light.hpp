//
// Created by Zaiyang Li on 30/01/2018.
//

#ifndef RENDERER_LIGHTSOURCE_HPP
#define RENDERER_LIGHTSOURCE_HPP

#include <glm/glm.hpp>

// si
namespace McRenderer {
    using namespace glm;

    enum class AttenuationType {
        InverseSquare,
        Linear,
        InverseExponential
    };

    struct Light {
        float intensity{1.0f};
        vec3 diffuseColour{1.0f, 1.0f, 1.0f};
        vec3 specularColour{1.0f, 1.0f, 1.0f};
        AttenuationType type{AttenuationType::InverseSquare};
        vec3 position{0,0,0};

    };

    struct AmbientLight : Light {

    };
    struct AreaLightSource : public Light{
        float fallOffAngle;
        float width;
        float height;
        vec4 direction;
    };

    struct PointLightSource: public Light {

    };

    struct SpotLight : public Light {
        float fallOffAngle;
        vec3 direction;
    };


}


#endif //RENDERER_LIGHTSOURCE_HPP
