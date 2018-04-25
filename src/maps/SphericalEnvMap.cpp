//
// Created by Zaiyang Li on 24/04/2018.
//

#include "SphericalEnvMap.hpp"
#include "../math/FastMath.hpp"

namespace McRenderFace {

    SphericalEnvMap::SphericalEnvMap(const string &path, float thetaoffsetIn, float phiOffsetIn)
            : thetaOffset{thetaoffsetIn}, phiOffset{phiOffsetIn}, envMap{new TextureMap2D(path)} {

    }

    vec2 SphericalEnvMap::normalToSphericalCoord(vec3 unitNormal) {
        // assume normal vector is normalized
        //float theta = fastArcCos(unitNormal.z);

        if(std::isnan(unitNormal.x)) {
            cout << "x is nan" << endl;
        } else if (std::isnan(unitNormal.y)) {
            cout << "y is nan" << endl;
        } else if (std::isnan(unitNormal.z)) {
            cout << "z is nan" << endl;
        }
        unitNormal = clamp(unitNormal, vec3(-1), vec3(1));
        float theta = std::acos(unitNormal.z);
        float phi = std::atan2(unitNormal.y,  unitNormal.x);
        return glm::vec2(phi, theta);
    }
}