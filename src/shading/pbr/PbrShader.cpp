//
// Created by Zaiyang Li on 10/02/2018.
//

#include "PbrShader.hpp"
namespace McRenderFace {
    namespace Shading {
        void PbrShader::compute(const PbrMaterial &material,
                                const PbrLightParameters &lightParameters,
                                const PbrSurfaceParameters &surfaceParameters,
                                PbrOutput &output)
        {
            vec3 halfVector = glm::normalize(lightParameters.lightDirection + surfaceParameters.surfaceNormal);
            float cosineLightAngle = glm::dot(lightParameters.lightDirection, surfaceParameters.surfaceNormal);
            float cosineViewAngle = glm::dot(lightParameters.viewerDirection, surfaceParameters.surfaceNormal);
            cosineLightAngle = cosineLightAngle > 0 ? cosineLightAngle : 0;
            cosineViewAngle = cosineViewAngle> 0 ? cosineViewAngle : 0;
            float alpha = material.diffuseRoughness * material.diffuseRoughness;

            float g = smithG1Shlick(cosineViewAngle, alpha);
            float f0 = fresnelF0(material.fresnelIOR);
            float fresnel = f0;
            if(material.fresnelReflection) {
                fresnel = fresnelShlick(f0, lightParameters.lightDirection, halfVector);
            }
            float theta = blinnSampleTheta(material.specuarlGlossiness);
            float d = blinnNormalNdf(theta, alpha);
            float brdfSpecular = g * fresnel * d;
            vec3 specularLight = lightParameters.lightColour
                                 * (lightParameters.lightIntensity
                                 * brdfSpecular
                                 * cosineLightAngle);

            vec3 specularColour = material.specularColour * specularLight;

            // TODO: replace diffuse colour calculation with Oren-Nayar sampling.
            vec3 diffuseColour = material.diffuseColour * cosineLightAngle;
            diffuseColour *= (1-fresnel);
            output.colour = specularColour + diffuseColour;
        }

        float PbrShader::fresnelF0(float fresnelIOR) {
            float f = (1 - fresnelIOR) / (1 + fresnelIOR);
            return f*f;
        }

        void PbrShader::microfacet(vec3 light, vec3 half) {

        }

        float PbrShader::implicitGeometry(vec3 l, vec3 n, vec3 h) {
            return glm::dot(l, n) * glm::dot(h, n);
        }

        float PbrShader::ggxSpecularDistribution(float alpha, vec3 m, vec3 normal) {
            float alpha2 = alpha * alpha;
            float dot = glm::dot(m, normal);
            dot = dot * dot;
            float temp = dot * (alpha2 - 1) + 1;
            temp = temp * temp;
            return static_cast<float>(alpha2 / (M_PI * temp));
        }

        float PbrShader::fresnelShlick(float f0, vec3 lightDirection, vec3 halfVector) {
            float dot = glm::dot(lightDirection, halfVector);
            float dot2 = dot * dot;
            return f0 + (1 - f0) * dot2 * dot2 * dot;
        }

        float PbrShader::smithG1Shlick(vec3 v1, vec3 v2, float alpha) {
            float k = alpha * SQRT_2_PI();
            float cosineAngle = glm::dot(v1, v2);

            return cosineAngle / (cosineAngle * (1 - k) + k);
        }

        constexpr float PbrShader::SQRT_2_PI() const{
            return static_cast<float>(0.7978845608);
        }

        float PbrShader::smithG1Shlick(float cosineViewAngle, float alpha) {
            float k = alpha * SQRT_2_PI();
            return cosineViewAngle / (cosineViewAngle * (1 - k) + k);
        }

        constexpr float PbrShader::INVERSE_2_PI() const {
            return static_cast<float>(0.5 * 1 / M_PI);
        }

        float PbrShader::blinnNormalNdf(float theta, float alpha) {
            return alpha + 2 * INVERSE_2_PI() * pow(cos(theta), alpha);
        }

        float PbrShader::blinnSampleTheta(float alpha) {
            float rand = generate_canonical<float, 10>(gen);
            float power = pow(rand, 1 / (alpha + 2));
            return acos(power);
        }
    }
}
