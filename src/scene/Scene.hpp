//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_SCENE_HPP
#define RENDERER_SCENE_HPP

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "../brdf/MicroFacetShader.hpp"
#include <memory>

namespace McRenderFace {
    using namespace Shading;
    using namespace std;
    struct Scene {
        Camera camera;
        vector<shared_ptr<SceneObject>> objects{};
        vector<shared_ptr<Light>> lights{};
        vector<shared_ptr<PbrMaterial>> materials;
        vec3 backgroundColour{0.0f};
        void addObject(SceneObject *object);
        void addLight(Light* light);
        void addMaterial(PbrMaterial* material);
        void preprocessMeshes();
    };

    void createTestScene(Scene& scene);
}


#endif //RENDERER_SCENE_HPP
