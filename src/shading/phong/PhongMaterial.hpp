//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP

#include <glm/glm.hpp>
#include "../../scene/TextureSampler2D.hpp"
#include "../UvSampler3D.hpp"

namespace McRenderFace {
    using namespace glm;
    class PhongMaterial {
        vec3 ambientColor {0.2f, 0.2f, 0.2f};
        UvSampler3D* ambientMap {nullptr};
        vec3 diffuseColor {0.75f, 0.75f, 0.75f};
        UvSampler3D* diffuseMap {nullptr};
        vec3 specularColor { 0.75f, 0.75f, 0.75f};
        UvSampler3D* specularMap {nullptr};
        float specularExponent{1.0f};
    };
}

#endif //RENDERER_MATERIAL_HPP
