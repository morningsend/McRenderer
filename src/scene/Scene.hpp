//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_SCENE_HPP
#define RENDERER_SCENE_HPP

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"

namespace McRenderFace {
    using namespace Shading;
    struct Scene {
        Camera camera;
        vector<Mesh> models{};
        vector<std::shared_ptr<Light>> lights{};
        vector<std::shared_ptr<Material>> materials;
        vec3 backgroundColour{0.0f};
    };

    void createTestScene(Scene& scene);
}


#endif //RENDERER_SCENE_HPP
