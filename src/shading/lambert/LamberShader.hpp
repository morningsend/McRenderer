//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_LAMBERSHADER_HPP
#define RENDERER_LAMBERSHADER_HPP
#include <glm/glm.hpp>
#include "../UvSampler3D.hpp"
#include "../Material.hpp"

namespace McRenderFace{
    namespace Shading {
        using namespace glm;

        struct LambertMaterial : Material {
            vec3 diffuseColour { 0.75f};
            UvSampler3D* diffuseMap {nullptr};
        };

        struct LambertParameters {
            vec3 lightDirection;
            vec3 lightDiffuse;
            vec3 lightPosition;
            vec3 surfaceNormal;
        };

        class LamberShader {
        public:
            vec3 compute(const LambertParameters &parameters) const;
        };
    }
}


#endif //RENDERER_LAMBERSHADER_HPP
