//
// Created by Zaiyang Li on 24/04/2018.
//

#ifndef RENDERER_SPHERICALENVMAP_HPP
#define RENDERER_SPHERICALENVMAP_HPP
#include <cmath>
#include <glm/glm.hpp>
#include "TextureMap2D.hpp"

namespace McRenderFace {
    using namespace glm;
    class SphericalEnvMap {
    private:
        std::unique_ptr<TextureMap2D> envMap;
        float thetaOffset;
        float phiOffset;
        static constexpr float INVPI = 1.0f / (float) M_PI;
        static constexpr float INV2PI = 0.5f / (float) M_PI;
        float exposure{0.0f};
        float exposureCoefficient{1.0f};
    public:
        SphericalEnvMap(const string& path, float thetaoffsetIn = 0.0f, float phiOffset = 0.0f);

        inline vec3 sampleNormal(vec3 normal) {
            vec2 sphericalCoord = normalToSphericalCoord(normal);
            vec2 uv = vec2(sphericalCoord.y * INVPI,sphericalCoord.x * INVPI * -0.5f + 0.5f);
            //cout << uv.x << ' ' << uv.y<< endl;
            return envMap->sampleNearest(uv) * exposureCoefficient;
        }
        vec2 normalToSphericalCoord(vec3 unitNormal);
        inline void setExposure(float exposureIn){
            exposure = exposureIn;
            exposureCoefficient = pow(2.0f, exposure);
        }
    };
}


#endif //RENDERER_SPHERICALENVMAP_HPP
