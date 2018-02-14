//
// Created by Zaiyang Li on 10/02/2018.
//

#include "Scene.hpp"
#include "../shading/lambert/LamberShader.hpp"
namespace McRenderFace {

    void createTestScene(Scene &scene) {
        scene.camera.position = vec3(0,0, 1);
        scene.camera.forward = vec3(0,0, -1);
        scene.camera.up = vec3(0,1,0);
        scene.camera.computeRightVector();
        scene.camera.focalLength = .055;
        scene.camera.aspectRatio = 1.0f;
        scene.camera.fieldOfViewDegrees = 43.0f;

        PointLight* light = new PointLight();
        light->colour = vec3(1.0f, 1.0f, 1.0f);
        light->intensity = 10.0f;
        light->position = vec3(0.0f, 1.58f, 0.0f);
        scene.addLight(light);

        // default material;
        LambertMaterial* grayMaterial = new LambertMaterial;

        LambertMaterial* redMaterial = new LambertMaterial;
        redMaterial->diffuseColour = vec3(0.75f, 0.1f, 0.1f);

        LambertMaterial* blueMaterial = new LambertMaterial;
        blueMaterial->diffuseColour = vec3(0.1f, 0.1, 0.75f);

        scene.addMaterial(grayMaterial);
        scene.addMaterial(redMaterial);
        scene.addMaterial(blueMaterial);

        Mesh* model = new Mesh;
        MeshData* data = new MeshData;

        Triangle tri{
                vec3(-2,-2, -2),
                vec3(0,-2, -2),
                vec3(0,0, -2),
                vec3(0, 0, 1)
        };
        Triangle tri2{
                vec3(-2, -2, -2),
                vec3(0, 0, -2),
                vec3(-2, 0, -2),
                vec3(0, 0, 1)
        };

        TriangleUV uv;

        data->triangles.push_back(tri);
        data->triangles.push_back(tri2);
        data->uvCoords.push_back(uv);
        data->uvCoords.push_back(uv);
        data->uvCoords.push_back(uv);

        model->meshData = data;

        model->computeBoundingBox();
        model->materialId = 0;

        scene.addObject(model);
    }

    void Scene::addObject(SceneObject *mesh) {
        meshes.push_back(shared_ptr<SceneObject>(mesh));
        mesh->objectId = static_cast<int>(meshes.size() - 1);
    }

    void Scene::addLight(Light *light) {
        lights.push_back(shared_ptr<Light>(light));
    }

    void Scene::addMaterial(Material *material) {
        materials.push_back(shared_ptr<Material>(material));
        material->materialId = static_cast<int>(materials.size() - 1);
    }

    void Scene::preprocessMeshes() {

        for(auto& mesh : meshes) {
            mesh->applyTransform();
            mesh->computeBoundingBox();
        }
    }
}