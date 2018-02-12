//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_SPHERE_HPP
#define RENDERER_SPHERE_HPP

#include <glm/glm.hpp>
#include "Transform.hpp"

namespace McRenderFace {
    using namespace glm;
    struct Sphere {
        Transform transform;
        float radius;
        vec3 origin;

    };

}


#endif //RENDERER_SPHERE_HPP
