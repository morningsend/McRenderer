//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_TRANSFORM_HPP
#define RENDERER_TRANSFORM_HPP

#include <glm/glm.hpp>

namespace McRenderFace {
    using namespace glm;
    struct Transform {
        vec3 translation {0,0,0};
        vec3 rotation {0,0,0};
        vec3 scale {1,1,1};

        mat4 matrix();
    };
}


#endif //RENDERER_TRANSFORM_HPP
