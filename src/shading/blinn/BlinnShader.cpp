//
// Created by Zaiyang Li on 10/02/2018.
//

#include "BlinnShader.hpp"

namespace McRenderFace {
    namespace Shading {
        /**
         * Shader to compute pixel colour for Blinn-Phong
         * https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model
         * @param material
         * @param parameters
         * @return
         */
        glm::vec3 BlinnShader::compute(const McRenderFace::Shading::BlinnMaterial &material,
                                       const McRenderFace::Shading::BlinnParameters &parameters) {

            vec3 halfWay = glm::normalize(parameters.viewerDirection + parameters.lightDirection);
            float cosineAngle = glm::dot(parameters.lightDirection, parameters.surfaceNormal);
            cosineAngle = cosineAngle > 0 ? cosineAngle : 0;

            float specularAngle = glm::dot(halfWay, parameters.surfaceNormal);
            specularAngle = specularAngle > 0 ? specularAngle : 0;

            float specularIntensity = pow(specularAngle, material.specularExponent);
            float distance2 = parameters.lightDistance * parameters.lightDistance;

            vec3 lightColour = parameters.lightColour * parameters.lightIntensity / distance2;
            vec3 diffuse = material.diffuseColour * lightColour;
            vec3 specular = material.specularColor * lightColour * specularIntensity;

            return diffuse + specular;
        }
    }
}
