//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_SCENE_HPP
#define RENDERER_SCENE_HPP

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "../shading/Material.hpp"
#include <memory>

namespace McRenderFace {
    using namespace Shading;
    using namespace std;
    struct Scene {
        Camera camera;
        vector<shared_ptr<Mesh>> meshes{};
        vector<shared_ptr<Light>> lights{};
        vector<shared_ptr<Material>> materials;
        vec3 backgroundColour{0.0f};
        void addMesh(Mesh* mesh);
        void addLight(Light* light);
        void addMaterial(Material* material);
    };

    void createTestScene(Scene& scene);
}


#endif //RENDERER_SCENE_HPP
