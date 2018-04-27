//
// Created by Zaiyang Li on 10/02/2018.
//

#include <iostream>
#include "MicroFacetShader.hpp"
namespace McRenderFace {
    namespace Shading {
        using namespace glm;
        static inline float max(float a, float b) {
            return a > b ? a : b;
        }
        static const float INVERSEPI = static_cast<const float>(1 / M_PI);
        void MicroFacetShader::compute(const PbrMaterial &material,
                                const PbrLightParameters &lightParameters,
                                const PbrSurfaceParameters &surfaceParameters,
                                PbrShaderOutput &output)
        {

            // cook-torrance specular begins here ====
            vec3 halfVector = glm::normalize(lightParameters.lightDirection + lightParameters.viewerDirection);
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
        float LambertBrdf::evaluate(vec3 wIn, vec3 wOut, vec3 normal) {
            return max(dot(wOut, normal), 0) * INVERSEPI;
        }

        void LambertBrdf::sample(vec3 normal, BxdfSample &brdfSample) {
            HemisphereSample sample = sampler.sampleCosineWeightedUnitHemisphere();
            float dDotN = glm::dot(normal, vec3(0,0,1));
            float angle = acos(dDotN);
            if(angle < 0.01) {
                brdfSample.direction = sample.direction;
            } else {
                vec3 axis = cross(vec3(0,0,1), normal);
                brdfSample.direction = glm::rotate(sample.direction, angle, axis);
            }

            brdfSample.probability = sample.pdf;
        }

        constexpr float CookTorranceBrdf::INVERSE_2_PI()  {
            return static_cast<float>(0.5 / M_PI);
        }
        constexpr float CookTorranceBrdf::SQRT_2_PI() {
            return 0.7978845608f;
        }

        float CookTorranceBrdf::blinnPhongNormalDistribution(float alpha, float nDotH) {
            return (alpha + 2) * INVERSE_2_PI() * pow(nDotH, alpha);
        }



        float CookTorranceBrdf::ggxNormalDistribution(float roughness, float nDotH) {
            cout << nDotH << endl;
            float roughness2 = roughness * roughness;
            float nDotH2 = nDotH * nDotH;
            float tanNDotH2 = (1 - nDotH2) / nDotH2;
            float denom = nDotH2 * (roughness2 + tanNDotH2);
            denom = denom * denom * MULTIPLE_PI(1);
            float sign = nDotH > 0 ? 1 : 0;
            return sign * roughness2 / denom;
        }

        float CookTorranceBrdf::beckmannNormalDistribution(float roughness, float nDotH) {
            float invroughness2 = 1.0f / roughness * roughness;
            float nDotH2 = nDotH * nDotH;
            float exponent = (1.0f - 1.0f / nDotH2) * invroughness2;
            float denom = MULTIPLE_PI(1.0f) * nDotH2 * nDotH2;
            return std::exp(exponent) * denom * invroughness2;
        }

        float CookTorranceBrdf::cookTorranceGeometry(float nDotH, float nDotL, float vDotH, float nDotV) {
            float invVDotH = 1.0f / vDotH;
            float t1 = 2 * nDotH * nDotV * invVDotH;
            float t2 = 2 * nDotH * nDotL * invVDotH;
            return std::min<float>(std::min<float>(t1, t2), 1);
        }

        float CookTorranceBrdf::schlickSmithG1(float nDotX, float roughness) {
            return 0;
        }

        float CookTorranceBrdf::schlickBeckmannGeometry(float nDotL, float nDotV, float roughness) {
            float roughness2 = roughness * roughness;
            //0.7978845608 = sqrt (2/pi)
            float k = roughness2 * 0.7978845608f;
            float smith1L = nDotL/(nDotL * (1-k) + k);
            float smith1V = nDotV/(nDotV * (1-k) + k);
            return smith1L * smith1V;
        }

        float CookTorranceBrdf::ggxSmithG1(float xDotH, float xDotN, float roughness) {
            float chi = xDotH > 0 ? 1 : 0;
            float xDotN2 = xDotN * xDotN;
            float tanTheta2 = xDotN2 == 0 ? 100000 : (1 - xDotN2) / xDotN2;
            float denom = 1.0f + std::sqrt(1.0f + roughness * roughness * tanTheta2) * xDotN;
            return chi * xDotH * 2 / denom;
        }

        float CookTorranceBrdf::ggxSmithGeometry(float nDotL, float nDotV, float lDotH, float vDotH, float roughness) {
            return ggxSmithG1(lDotH, nDotL, roughness)
                   * ggxSmithG1(vDotH, nDotV, roughness);
        }

        void CookTorranceBrdf::sampleBeckmannNormalDistribution(const vec3& wOut, const vec3& normal, float alpha, BxdfSample &sample) {
            vec2 randomNumbers = uniform.sample();
            float alpha2 = alpha * alpha;
            float phi = randomNumbers.x * MULTIPLE_PI(2.0f);

            float logY = log(randomNumbers.y);
            logY = std::isinf(logY) ? 0 : logY;
            float tanTheta2 = -alpha2 * logY;

            float cosTheta = 1.0f / std::sqrt(tanTheta2 + 1);
            float sinTheta = std::sqrt(max(0, 1 - cosTheta * cosTheta));
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            vec3 wH = vec3(
                    sinTheta * cosPhi,
                    sinTheta * sinPhi,
                    cosTheta
            );

            vec3 axisOfRotation = cross(wH, normal);
            float angle = std::acos(dot(wH, normal));
            wH = rotate(wH ,angle, axisOfRotation);
            float wOutDotWH = max(dot(wOut, wH), 0.001);
            sample.probability = beckmannNormalDistribution(alpha, wOutDotWH) / (wOutDotWH * 4.0f);
            sample.direction = -wOut - wH * (wOutDotWH * 2.0f);
        }

        void CookTorranceBrdf::sampleGGXNormalDistribution(const vec3 &wOut, const vec3 &normal, float alpha,
                                                           BxdfSample &sample) {

            vec2 randomNumbers = uniform.sample();
            float phi = randomNumbers.x * MULTIPLE_PI(2.0f);
            float t = (1 - randomNumbers.y) / (randomNumbers.y * (alpha * alpha - 1) + 1);
            float cosTheta = std::sqrt(t);
            float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
            float cosPhi = std::cos(phi);
            float sinPhi = std::sin(phi);

            vec3 wH = vec3(
                    sinTheta * cosPhi,
                    sinTheta * sinPhi,
                    cosTheta
            );
            vec3 axis = cross(vec3(0,0,1), normal);
            float angle = std::acos(normal.z);
            wH = rotate(wH,angle, axis);
            float wODotWH = dot(wOut, wH);
            float d = ggxNormalDistribution(alpha, dot(normal, wH));// / (4.0f * max(wODotWH, 0.001f));
            sample.probability = d / (4.0f * max(wODotWH, 0.001f));
            sample.direction = normalize(-wOut + wH * (wODotWH * 2.0f));

            //cout << d << endl;
        }

        float CookTorranceBrdf::evaluateGGXBrdf(const vec3 &wOut,
                                                const vec3 &wIn,
                                                const vec3 &normal,
                                                float alpha,
                                                float ior){
            vec3 wH = normalize((wOut + wIn) * 0.5f);
            float nDotL = std::max<float>(dot(normal, wIn), 0);
            float nDotV = std::max<float>(dot(normal, wOut), 0);
            float lDotH = std::max<float>(dot(wIn, wH), 0);
            float vDotH = std::max<float>(dot(wOut, wH), 0);
            float nDotH = std::max<float>(dot(normal, wH), 0);
            //float g = ggxSmithGeometry(nDotL, nDotV, lDotH, vDotH, alpha);
            float g = schlickGGXGeometricShadowMaskingFunc(nDotL, nDotV, alpha);
            float d = ggxNormalDistribution(alpha, nDotH);
            float fresnel0 = f0(ior, 1);
            float f = shlickFresnel(lDotH, fresnel0);
            //cout << "fresnel: " << f << endl;
            return 1 * g * d / max(0.001, (4 * nDotL * nDotV));
        }
    }
}
