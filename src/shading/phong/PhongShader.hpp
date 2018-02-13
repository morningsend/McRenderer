//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_PHONG_SHADER_HPP
#define RENDERER_PHONG_SHADER_HPP

#include <glm/glm.hpp>
#include "../UvSampler3D.hpp"
#include "../Material.hpp"

namespace McRenderFace {
    namespace Shading {
        using namespace glm;

        struct PhongMaterial : public Material{
            vec3 diffuseColour{0.75f, 0.75f, 0.75f};
            UvSampler3D *diffuseMap{nullptr};
            vec3 specularColor{0.75f, 0.75f, 0.75f};
            UvSampler3D *specularMap{nullptr};
            float specularExponent{1.0f};
        };

        struct PhongParameters {
            vec3 lightDirection;
            vec3 surfaceNormal;
            vec3 viewerDirection;
            vec3 lightColour;
            float lightIntensity;
            float lightDistance;
            float numberOfLights;
            float ambientWeight;
            float diffuseWeight;
            float specularWeight;
        };

        struct PhongShader {
            inline vec3 compute(const PhongMaterial& material, const PhongParameters& parameters);
        };

    }
}

#endif //RENDERER_PHONG_MATERIAL_HPP
