//
// Created by Zaiyang Li on 10/02/2018.
//

#include "Scene.hpp"
#include "../shading/lambert/LamberShader.hpp"
namespace McRenderFace {

    void createTestScene(Scene &scene) {
        scene.camera.position = vec3(0,0,1);
        scene.camera.forward = vec3(0,0,-1);
        scene.camera.up = vec3(0, 1, 0);
        scene.camera.right = vec3(-1, 0, 0);

        PointLight* light = new PointLight();
        light->colour = vec3(1.0f, 1.0f, 1.0f);
        light->intensity = 10.0f;
        light->position = vec3(0.0f, 0.98f, 0.0f);
        scene.lights.push_back(shared_ptr<PointLight>(light));

        // default material;
        LambertMaterial* grayMaterial = new LambertMaterial;

        LambertMaterial* redMaterial = new LambertMaterial;
        redMaterial->diffuseColour = vec3(0.75f, 0.1f, 0.1f);

        LambertMaterial* blueMaterial = new LambertMaterial;
        blueMaterial->diffuseColour = vec3(0.1f, 0.1, 0.75f);

        scene.materials.push_back(shared_ptr<LambertMaterial>(grayMaterial));
        scene.materials.push_back(shared_ptr<LambertMaterial>(redMaterial));
        scene.materials.push_back(shared_ptr<LambertMaterial>(blueMaterial));

        Mesh* room = new Mesh;
        MeshData* data = new MeshData;

    }
}