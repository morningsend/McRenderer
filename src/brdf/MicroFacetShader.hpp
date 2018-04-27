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
#include "../rendering/UniformSampler.hpp"

namespace McRenderFace {
    namespace Shading {
        using namespace glm;
        using namespace std;

        enum class MaterialType {
            Pbr,
            Reflective,
            Refractive,
            Specular,
            Diffuse,
            Emissive,
        };
        /**
         * Simple physically based shading model.
         */
        struct PbrMaterial : Material {
            vec3 diffuseColour{0};
            vec3 specularColour{0.0f};
            vec3 reflectionColour{0.0f};
            vec3 refractiveColour{0.0f};
            MaterialType type{MaterialType::Diffuse};

            float diffuseRoughness{0.0f};
            float specularRoughness{0.1f};
            float reflectionRoughness{0.0f};

            vec3 emissiveColour{0};
            float emissiveIntensity{0};

            float specularIndexOfRefraction{1.0f};
            bool fresnelSpecularReflection{false};
            float fresnelIOR{1.5f};

            float refractiveIndexOfRefraction{1.0f};
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
            vec3 direction {0};
            float pdf{1.0f};
        };

        struct MicroFacetShader {
        private:
            HemisphereSampler sampler;

        public:
            MicroFacetShader() {
            }

            constexpr float SQRT_2_PI() const;

            constexpr float INVERSE_2_PI() const;

            float fresnelShlick(float f0, vec3 lightDirection, vec3 halfVector);

            float fresnelShlick(float f0, float cosineLH);

            float fresnelF0(float fresnelIOR);

            float ggxSpecularDistribution(float alpha, vec3 m, vec3 normal);

            void microfacet(vec3 light, vec3 half);


            float smithG1Shlick(vec3 v1, vec3 v2, float alpha);

            float smithG1Shlick(float cosineViewAngle, float alpha);

            float implicitGeometry(vec3 l, vec3 n, vec3 h);

            float blinnNormalNdf(float theta, float alpha);

            float blinnSampleTheta(float alpha);

            float blinnPdf(vec3 normal, vec3 half, float m);


            void compute(const PbrMaterial &material,
                         const PbrLightParameters &lightParameters,
                         const PbrSurfaceParameters &surfaceParameters,
                         PbrShaderOutput &output);
        };


        struct BxdfSample {
            vec3 direction{0};
            float probability{1};
        };

        enum class BxdfType {
            Diffuse, Specular, MicroFacet, Reflective, Refractive
        };
        class Bxdf {
        public:
            virtual BxdfType getType() { return BxdfType ::Diffuse; };
            virtual float evaluate(vec3 wIn, vec3 wOut, vec3 normal) = 0;
            virtual void sample(vec3 wOut, BxdfSample& sample) = 0;
            virtual float pdf(vec3 normal, vec3 wOut, vec3 wIn) = 0;
        };
        class FresnelBsdf {
        private:
            std::default_random_engine engine;
            std::uniform_real_distribution<float> uniform{0, 1};
        public:
            void sampleRefraction(float iorIn,
                                float iorOut,
                                const vec3& wOut,
                                const vec3& normal,
                                BxdfSample& sample);
        };
        class LambertBrdf : public Bxdf {
        private:
            HemisphereSampler sampler;
        public:
            BxdfType getType() override { return BxdfType ::Diffuse; };
            float evaluate(vec3 wIn, vec3 wOut, vec3 normal) override;
            void sample(vec3 wOut, BxdfSample& sample) override;
            float pdf(vec3 normal, vec3 wOut, vec3 wIn) override {
                float nDotW = glm::dot(normal, wIn);
                nDotW = nDotW < 0 ? 0 : nDotW;
                return static_cast<float>(nDotW / M_PI);
            }
            ~LambertBrdf(){}
        };

        class CookTorranceBrdf {
        private:
            UniformSampler uniform;
        public:
            /**
             * returns sqrt(2 pi)
             * @return
             */
            static constexpr float SQRT_2_PI();
            static constexpr float INVERSE_2_PI();
            /** returns (m * pi) */
            static constexpr float MULTIPLE_PI(float m){ return static_cast<float > (M_PI * m); }
            /** returns 1 / (m * pi) */
            static constexpr float INVERSE_MULTIPLE_PI(float m) { return 1.0f / MULTIPLE_PI(m); }

            inline static float beckmannNormalDistribution(float roughness, float nDotH);
            inline static float ggxNormalDistribution(float roughness, float nDotH);
            inline static float blinnPhongNormalDistribution(float shininess, float nDotH);
            inline static float schlickSmithG1(float nDotX, float roughness);
            inline static float ggxSmithG1(float xDotH, float xDotN, float roughness);
            static inline float ggxSmithGeometry(float nDotL, float nDotV, float lDotH, float vDotH, float roughness);
            inline float schlickBeckmannGeometry(float nDotL, float nDotV, float roughness);
            inline static float cookTorranceGeometry(float nDotH, float nDotl, float vDotH, float nDotV);

            void sampleBeckmannNormalDistribution(const vec3& wOut, const vec3& normal, float alpha, BxdfSample& sample);
            void sampleGGXNormalDistribution(const vec3& wOut, const vec3& normal, float alpha, BxdfSample& sample);

            float evaluateGGXBrdf(const vec3& wOut, const vec3& wIn, const vec3& normal, float alpha, float ior);

            inline float schlickGGXGeometricShadowMaskingFunc(float nDotL, float nDotV, float roughness) {
                float m = roughness / 2;
                float smith1 = nDotL / (nDotL * (1-m ) + m);
                float smith2 = nDotV / (nDotV * (1-m ) + m);
                return smith1 * smith2;
            }

            inline float shlickFresnel(float lDotH, float f0) {
                return f0 + (1-f0) * pow(1.0f - lDotH, 5.0f);
            }
            inline float f0(float ior1, float ior2) {
                float k = (ior1 - ior2) /(ior1 + ior2);
                return k * k;
            }
        };

        class BeckmannBrdf: public Bxdf {
        private:
            float roughness;
        public:
            BeckmannBrdf(float roughness) : roughness{roughness} { }
            float evaluate(vec3 wIn, vec3 wOut, vec3 normal) override{ return 0;};
            void sample(vec3 wOut, BxdfSample& sample) override{};
        };
    }
}


#endif //RENDERER_PBRMATERIAL_HPP
