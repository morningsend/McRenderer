//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_SCENE_HPP
#define RENDERER_SCENE_HPP

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"

namespace McRenderFace {

    struct Scene {
        Camera camera;
        vector<Mesh> models{};
        vector<Light> lights{};
        vec3 backgroundColour{0.0f};
    };
}


#endif //RENDERER_SCENE_HPP
