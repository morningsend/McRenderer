//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_PBRSHADER_HPP
#define RENDERER_PBRSHADER_HPP

#include <random>
#include <glm/glm.hpp>
#include "../image/UvSampler3D.hpp"
#include "../image/UvSampler1D.hpp"
#include "Material.hpp"
#include "HemisphereSampler.hpp"

namespace McRenderFace {
    namespace Shading {
        using namespace glm;
        using namespace std;

        /**
         * Simple physically based shading model.
         */
        struct PbrMaterial : Material {
            vec3 diffuseColour{0.75};
            vec3 specularColour{0.0f};
            vec3 reflectionColour{0.0f};
            vec3 refractionColour{0.0f};

            float diffuseAlbedo{0.8f};
            float diffuseRoughness{0.0f};
            float specularRoughness{0.1f};
            float specularGlossiness{20.0f};
            float reflectionRoughness{0.0f};

            vec3 emissiveColour{0};
            float emissiveIntensity{0};

            UvSampler3D *diffuseMap{nullptr};
            UvSampler3D *specularMap{nullptr};
            UvSampler3D *reflectionMap{nullptr};
            UvSampler3D *refractionMap{nullptr};

            float indexOfRefraction{1.0f};
            bool fresnelSpecularReflection{false};
            float fresnelIOR{1.0f};

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
            vec3 lightPosition;
            float lightIntensity;
            float lightExposure;
        };


        struct PbrSurfaceParameters {
            vec3 surfaceNormal;
            vec3 rayIncoming;
            vec3 position;
        };
        struct PbrShaderOutput {
            vec3 colour;
        };
        struct PbrBrdfSampleOutput {
            vec3 direction;
            float pdf;
        };

        struct MicroFacetShader {
        private:
            HemisphereSampler sampler;

        public:
            MicroFacetShader() {
            }

            constexpr float SQRT_2_PI() const;

            constexpr float INVERSE_2_PI() const;

            float G(float omega_i, float omega_o, vec3 halfDirection);

            float sampleNormalDistribution(vec3 halfDirection);

            float fresnelShlick(float f0, vec3 lightDirection, vec3 halfVector);

            float fresnelShlick(float f0, float cosineLH);

            float fresnelF0(float fresnelIOR);

            float diffuseOrenNayarDistribution(vec3 diffuseColour, float roughness, float albedo);

            vec3 torranceSparrowSpecular(vec3 specuarColour, float roughtness);

            float ggxSpecularDistribution(float alpha, vec3 m, vec3 normal);

            void microfacet(vec3 light, vec3 half);

            float smithFunction(vec3 lightDirection, vec3 halfVector, vec3 viewDirection, vec3 surfaceNormal);

            float smithG1Shlick(vec3 v1, vec3 v2, float alpha);

            float smithG1Shlick(float cosineViewAngle, float alpha);

            float implicitGeometry(vec3 l, vec3 n, vec3 h);

            float blinnNormalNdf(float theta, float alpha);

            float blinnSampleTheta(float alpha);

            float blinnPdf(vec3 normal, vec3 half, float m);

            vec3 sampleBlinnNormalPdf(float theta);

            void compute(const PbrMaterial &material,
                         const PbrLightParameters &lightParameters,
                         const PbrSurfaceParameters &surfaceParameters,
                         PbrShaderOutput &output);
            void sampleDiffuse(const PbrMaterial &material,
                               vec3 normal,
                               PbrBrdfSampleOutput &output);

            void sampleBeckmannNormalDistribution(const PbrMaterial &material,
                                                  vec3 normal,
                                                  PbrBrdfSampleOutput& output);

        };

        struct BeckmannShader : public MicroFacetShader {

        };

        struct BxdfSample {
            vec3 direction;
            float probability;
        };

        enum BxdfType {
            Diffuse, Specular,
        };
        class Bxdf {
        public:
            virtual BxdfType getType() { return BxdfType ::Diffuse; };
            virtual float evaluate(vec3 wIn, vec3 wOut, vec3 normal) = 0;
            virtual void sample(vec3 normal, BxdfSample& sample) = 0;
        };

        class LambertBrdf : public Bxdf {
        private:
            HemisphereSampler sampler;
        public:
            BxdfType getType() override { return BxdfType ::Diffuse; };
            float evaluate(vec3 wIn, vec3 wOut, vec3 normal) override;
            void sample(vec3 normal, BxdfSample& sample) override;
        };

        class CookTorranceBrdf: public Bxdf {

        };

        class BeckmannBrdf: public CookTorranceBrdf {
        private:
            float roughness;
        public:
            BeckmannBrdf(float roughness);
            float evaluate(vec3 wIn, vec3 wOut, vec3 normal) override;
            void sample(vec3 normal, BxdfSample& sample) override;
        };
    }
}


#endif //RENDERER_PBRMATERIAL_HPP
