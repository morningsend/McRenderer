//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_PBRMATERIAL_HPP
#define RENDERER_PBRMATERIAL_HPP

#include <glm/glm.hpp>
#include "../UvSampler3D.hpp"
#include "../UvSampler1D.hpp"

namespace McRenderFace {
    using namespace glm;
    /**
     * Simple physically based shading model.
     */
    struct PbrMaterial {
        vec3 diffuseColour;
        UvSampler3D* diffuseMap;
        float diffuseRoughness;
        UvSampler1D* diffuseRoughnessMap;
        vec3 specularColour;
        UvSampler3D* specularMap;
        float specularRoughness;
        UvSampler1D* specularRoughnessMap;
        float metalness;
        UvSampler1D* metalnessMap;
        float indexOfRefraction;
        bool fresnelReflection;
        UvSampler3D* normalMap;
    };
}


#endif //RENDERER_PBRMATERIAL_HPP
