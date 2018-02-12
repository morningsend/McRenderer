//
// Created by Zaiyang Li on 30/01/2018.
//

#ifndef RENDERER_LIGHTSOURCE_HPP
#define RENDERER_LIGHTSOURCE_HPP

#include <glm/glm.hpp>

// si
namespace McRenderFace {
    using namespace glm;

    enum class LightType {
        PointLight,
        AreaLight,
        SpotLight,
        DirectionalLight,
        AmbientLight
    };

    struct Light {
        LightType type{LightType::PointLight};
        float intensity{1.0f};
        float exposure{1.0f};
        vec3 colour{1.0f};
        vec3 position{0.0f};
        bool castShadow{true};
    };

    struct AmbientLight : Light {

    };
    struct AreaLightSource : public Light{
        float fallOffAngle;
        float width;
        float height;
        vec4 direction;
    };

    struct PointLight: public Light {

    };

    struct SpotLight : public Light {
        float fallOffAngle;
        vec3 direction;
    };

    struct DirectionalLight {
        vec3 direction;
    };
}


#endif //RENDERER_LIGHTSOURCE_HPP
