//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP

#include <glm/glm.hpp>
#include "TextureSampler2D.hpp"

namespace McRenderer {
    using namespace glm;
    class Material {
        vec3 diffuseColor {0.75f, 0.75f, 0.75f};
        vec3 specularColor { 0.75f, 0.75f, 0.75f};
        vec3 reflectionColor{ 0.0f, 0.0f, 0.0f};
        vec3 refractionColor{ 0.0f, 0.0f, 0.0f};
    };
}

#endif //RENDERER_MATERIAL_HPP
