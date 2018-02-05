//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_PLANE_HPP
#define RENDERER_PLANE_HPP

#include <glm/glm.hpp>

namespace McRenderer {
    using namespace glm;
    struct Plane {
        vec3 normal;
        float d;
    };
}


#endif //RENDERER_PLANE_HPP
