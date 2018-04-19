//
// Created by Zaiyang Li on 10/02/2018.
//

#include "LamberShader.hpp"

namespace McRenderFace {
    namespace Shading {

        vec3 LamberShader::compute(const LambertMaterial &material, const LambertParameters &parameters) const {
            float distance2 = parameters.lightDistance * parameters.lightDistance;
            float cosineAngle = glm::dot(parameters.surfaceNormal, parameters.lightDirection);
            cosineAngle = cosineAngle > 0 ? cosineAngle : 0;
            vec3 lightColour = parameters.lightDiffuse * (cosineAngle * parameters.lightIntensity) / distance2;
            vec3 materialColour;
            if(material.diffuseMap!= nullptr) {
                materialColour = material.diffuseMap->sample(parameters.uvCoord);
            } else {
                materialColour = material.diffuseColour;
            }
            return materialColour * lightColour;
        }
    }
}
