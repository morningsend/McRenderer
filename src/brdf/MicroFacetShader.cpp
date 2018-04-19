//
// Created by Zaiyang Li on 10/02/2018.
//

#include "MicroFacetShader.hpp"
namespace McRenderFace {
    namespace Shading {
        void MicroFacetShader::compute(const PbrMaterial &material,
                                const PbrLightParameters &lightParameters,
                                const PbrSurfaceParameters &surfaceParameters,
                                PbrShaderOutput &output)
        {

            // cook-torrance specular begins here ====
            vec3 halfVector = glm::normalize(lightParameters.lightDirection + surfaceParameters.surfaceNormal);
            float cosineLightAngle = glm::dot(lightParameters.lightDirection, surfaceParameters.surfaceNormal);
            float cosineViewAngle = glm::dot(lightParameters.viewerDirection, surfaceParameters.surfaceNormal);
            float distance2 = glm::dot(lightParameters.lightPosition, surfaceParameters.position);
            cosineLightAngle = cosineLightAngle > 0 ? cosineLightAngle : 0;
            cosineViewAngle = cosineViewAngle> 0 ? cosineViewAngle : 0;
            float lightIntensity = lightParameters.lightIntensity * std::pow(2.0f, lightParameters.lightExposure);
            float alpha = material.specularRoughness * material.specularRoughness;
            alpha = alpha >= 0.0001f ? alpha : 0.0001f;
            float g = smithG1Shlick(cosineViewAngle, alpha);
            float f0 = fresnelF0(material.fresnelIOR);
            float fresnel = f0;
            if(material.fresnelSpecularReflection) {
                fresnel = fresnelShlick(f0, lightParameters.lightDirection, halfVector);
            }
            //float theta = blinnSampleTheta(material.specuarlGlossiness);
            float m = 2.0f / (alpha) - 2.0f;
            float d = blinnPdf(surfaceParameters.surfaceNormal, halfVector, m);
            float brdfSpecular = g * fresnel * d / (4.0f * cosineLightAngle * cosineViewAngle);
            vec3 specularLight = lightParameters.lightColour
                                 * (lightParameters.lightIntensity
                                 * brdfSpecular
                                 * cosineLightAngle);

            vec3 specularColour = material.specularColour * specularLight;
            // cook-torrance ends here.

            // TODO: replace diffuse colour calculation with Oren-Nayar sampling.
            // https://en.wikipedia.org/wiki/Oren%E2%80%93Nayar_reflectance_model

            float alpha2 = material.diffuseRoughness * material.diffuseRoughness;

            float A = 1 - 0.5f * alpha2 / (alpha2 + 0.33f);
            float B = 0.45f * alpha2 / (alpha2 + 0.09f);

            float thetaIn = acos(cosineLightAngle);
            float thetaOut = acos(cosineViewAngle);
            float a = thetaIn > thetaOut ? thetaIn : thetaOut;
            float b = thetaIn < thetaOut ? thetaIn : thetaOut;

            vec3 u = glm::normalize(-lightParameters.viewerDirection - surfaceParameters.surfaceNormal * cosineViewAngle);
            vec3 v = glm::normalize(-lightParameters.lightDirection - surfaceParameters.surfaceNormal * cosineLightAngle);
            float phiDiff = glm::dot(u, v);
            phiDiff = phiDiff > 0 ? phiDiff : 0;
            vec3 diffuseColour = material.diffuseColour * (A + B * phiDiff * sin(a) * tan(b));
            diffuseColour = diffuseColour * lightParameters.lightColour * lightIntensity * cosineLightAngle;
            // combine diffuse and specular.
            //diffuseColour *= (1-fresnel);
            output.colour = diffuseColour;
        }

        float MicroFacetShader::fresnelF0(float fresnelIOR) {
            float f = (1 - fresnelIOR) / (1 + fresnelIOR);
            return f*f;
        }

        void MicroFacetShader::microfacet(vec3 light, vec3 half) {

        }

        float MicroFacetShader::implicitGeometry(vec3 l, vec3 n, vec3 h) {
            return glm::dot(l, n) * glm::dot(h, n);
        }

        float MicroFacetShader::ggxSpecularDistribution(float alpha, vec3 m, vec3 normal) {
            float alpha2 = alpha * alpha;
            float dot = glm::dot(m, normal);
            dot = dot * dot;
            float temp = dot * (alpha2 - 1) + 1;
            temp = temp * temp;
            return static_cast<float>(alpha2 / (M_PI * temp));
        }

        float MicroFacetShader::fresnelShlick(float f0, vec3 lightDirection, vec3 halfVector) {
            float dot = glm::dot(lightDirection, halfVector);
            float dot2 = dot * dot;
            return f0 + (1 - f0) * dot2 * dot2 * dot;
        }
        float MicroFacetShader::fresnelShlick(float f0, float cosineLH) {
            float cosineLH2 = cosineLH * cosineLH;
            return f0 + (1.0f - f0) * cosineLH2 * cosineLH2 * cosineLH;
        }
        float MicroFacetShader::smithG1Shlick(vec3 v1, vec3 v2, float alpha) {
            float k = alpha * SQRT_2_PI();
            float cosineAngle = glm::dot(v1, v2);

            return cosineAngle / (cosineAngle * (1 - k) + k);
        }

        constexpr float MicroFacetShader::SQRT_2_PI() const{
            return static_cast<float>(0.7978845608);
        }

        float MicroFacetShader::smithG1Shlick(float cosineViewAngle, float alpha) {
            float k = alpha * SQRT_2_PI();
            return cosineViewAngle / (cosineViewAngle * (1 - k) + k);
        }

        constexpr float MicroFacetShader::INVERSE_2_PI() const {
            return static_cast<float>(0.5 / M_PI);
        }

        float MicroFacetShader::blinnNormalNdf(float theta, float alpha) {
            return alpha + 2 * INVERSE_2_PI() * pow(cos(theta), alpha);
        }

        float MicroFacetShader::blinnSampleTheta(float alpha) {
            float rand = 0.5f;
            float power = pow(rand, 1 / (alpha + 2));
            return acos(power);
        }

        float MicroFacetShader::blinnPdf(vec3 normal, vec3 half, float m) {
            float cosine = glm::dot(normal, half);
            cosine = cosine > 0 ? cosine : 0;
            return (m + 2) * INVERSE_2_PI() * pow(cosine, m);
        }

        void MicroFacetShader::sample(const PbrMaterial &material,
                               const PbrSurfaceParameters &surfaceParameters,
                               PbrBrdfSampleOutput& output) {

            //vec3 direction = surfaceParameters.rayIncoming - surfaceParameters.surfaceNormal *
            //                               (2.0f * glm::dot(surfaceParameters.rayIncoming,
            //                                                 surfaceParameters.surfaceNormal)
            //                                );
            //float angle = acos(glm::dot(direction, surfaceParameters.rayIncoming));
            HemisphereSample sample = sampler.sampleCosineWeightedUnitHemisphere();

            output.direction = HemisphereSampler::transformHemispherePointToNormal(
                    surfaceParameters.surfaceNormal,
                    sample.direction
            );
            output.pdf = sample.pdf;
        }
    }
}
