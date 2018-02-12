//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_SIMPLE_SCENE_HPP
#define RENDERER_SIMPLE_SCENE_HPP

#include <vector>
#include "Light.hpp"
#include "Triangle.hpp"
#include "Camera.hpp"

namespace McRenderFace {
    using namespace std;

    struct SimpleScene {
        vector <Light> lights{};
        vector <Triangle> model{};
        Camera camera {};
        vec3 backgroundColour{0.0f, 0.0f, 0.0f};
    };
}


#endif //RENDERER_SCENE_HPP
