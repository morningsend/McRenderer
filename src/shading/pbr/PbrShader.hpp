//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_PBRSHADER_HPP
#define RENDERER_PBRSHADER_HPP

#include <random>
#include <glm/glm.hpp>
#include "../UvSampler3D.hpp"
#include "../UvSampler1D.hpp"
#include "../Material.hpp"

namespace McRenderFace {
    namespace Shading {
        using namespace glm;
        using namespace std;
        /**
         * Simple physically based shading model.
         */
        struct PbrMaterial : Material{
            vec3 diffuseColour{0.75};
            vec3 specularColour{0.0f};
            vec3 reflectionColour{0.0f};
            vec3 refractionColour{0.0f};

            float diffuseAlbedo {0.8f};
            float diffuseRoughness{0.0f};
            float specularRoughness{0.0f};
            float specuarlGlossiness{20.0f};
            float reflectionRoughness{0.0f};

            UvSampler3D* diffuseMap{nullptr};
            UvSampler3D* specularMap{nullptr};
            UvSampler3D* reflectionMap{nullptr};
            UvSampler3D* refractionMap{nullptr};

            float indexOfRefraction;
            bool fresnelReflection;
            float fresnelIOR;

            UvSampler3D *normalMap;

            float diffuseWeight;
            float specularWeight;
            float refractionWeight;
            float reflectionWeight;

            ~PbrMaterial() = default;
        };

        struct PbrLightParameters {
            vec3 lightColour;
            vec3 lightDirection;
            vec3 viewerDirection;
            float lightDistance;
            float lightIntensity;
            float lightExposure;
        };

        struct PbrSurfaceParameters {
            vec3 surfaceNormal;
            vec3 rayIncoming;
        };
        struct PbrShaderOutput {
            vec3 colour;
            vec3 reflectedRayDirection;
            float pdf;
        };
        struct PbrShader {
        private:
            mt19937 gen {0};
        public:
            constexpr float SQRT_2_PI () const;
            constexpr float INVERSE_2_PI() const;
            float G(float omega_i, float omega_o, vec3 halfDirection);
            float sampleNormalDistribution(vec3 halfDirection);
            float fresnelShlick(float f0, vec3 lightDirection, vec3 halfVector);
            float fresnelF0(float fresnelIOR);
            float diffuseOrenNayarDistribution(vec3 diffuseColour, float roughness, float albedo);
            vec3 torranceSparrowSpecular(vec3 specuarColour, float roughtness);
            float ggxSpecularDistribution(float alpha, vec3 m, vec3 normal);
            void microfacet(vec3 light, vec3 half);
            float smithFunction(vec3 lightDirection, vec3 halfVector, vec3 viewDirection, vec3 surfaceNormal);
            float smithG1Shlick(vec3 v1, vec3 v2, float alpha);
            float smithG1Shlick(float cosineViewAngle,float alpha);
            float implicitGeometry(vec3 l, vec3 n, vec3 h);

            float blinnNormalNdf(float theta, float alpha);
            float blinnSampleTheta(float alpha);
            vec3 sampleBlinnNormalPdf(float theta);

            void compute(const PbrMaterial& material,
                         const PbrLightParameters& lightParameters,
                         const PbrSurfaceParameters& surfaceParameters,
                         PbrShaderOutput& output);
        };
    }
}


#endif //RENDERER_PBRMATERIAL_HPP
