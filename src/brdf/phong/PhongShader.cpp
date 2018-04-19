//
// Created by Zaiyang Li on 31/01/2018.
//

#include "PhongShader.hpp"

namespace McRenderFace {
    namespace Shading {
        glm::vec3 PhongShader::compute(const PhongMaterial &material,
                                                const PhongParameters &parameters) {
            float cosineAngle = glm::dot(parameters.lightDirection, parameters.surfaceNormal);
            cosineAngle = cosineAngle > 0 ? cosineAngle : 0;
            vec3 reflectedDirection = parameters.surfaceNormal * (2.0f * cosineAngle) - parameters.lightDirection;
            vec3 specularColour = material.specularColor *
                    pow(
                            glm::dot(reflectedDirection, parameters.viewerDirection),
                            material.specularExponent
                    );

            vec3 diffuseColour = material.diffuseColour * cosineAngle;

            return (specularColour + diffuseColour) * parameters.lightColour * parameters.lightIntensity;
        }
    }
}
