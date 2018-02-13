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

        Light() = default;
        virtual ~Light() = default;
    };

    struct AmbientLight : Light {
        AmbientLight() = default;

        ~AmbientLight() override = default;
    };
    struct AreaLightSource : public Light{
        float fallOffAngle { 0.0f};
        float width {1.0f};
        float height {1.0f};
        vec3 direction {0.0f, -1.0f, 0.0f};
        vec3 position{0.0f};
        float rotation{0.0f};

        AreaLightSource() {
            type = LightType::AreaLight;
        }

        ~AreaLightSource() override = default;
    };

    struct PointLight: public Light {
        PointLight() {
            type = LightType::PointLight;
        }
        ~PointLight() override = default;
    };

    struct SpotLight : public Light {
        float fallOffAngle { 45.0f};
        vec3 direction { 0.0f, -1.0f, 0.0f};

        SpotLight() {
            type = LightType::SpotLight;
        }
        ~SpotLight() override = default;
    };

    struct DirectionalLight : public Light {
        vec3 direction{0.0f, -1.0f, 0.0f};

        DirectionalLight() = default;
        ~DirectionalLight() override = default;
    };
    
}


#endif //RENDERER_LIGHTSOURCE_HPP
