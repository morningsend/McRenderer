#define GLM_SWIZZLE
#include <iostream>
#include <unordered_map>
#include "window/Window.hpp"
#include "window/TestDrawFunction.hpp"
#include "scene/SimpleScene.hpp"
#include "scene/TestModelH.h"
#include "CameraKeyboardController.hpp"
#include "rendering/RenderTarget.hpp"
#include "rendering/PathTracingRenderer.hpp"
#include "rendering/RenderTargetDrawFunction.hpp"
#include "scene/Sphere.hpp"
#include "scene/Light.hpp"

using namespace std;
using namespace McRenderFace;

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

void convertTriangles(const vector<::Triangle>& testTriangles, vector<McRenderFace::Triangle>& renderTriangles) {
    for(const ::Triangle& tri : testTriangles){
        McRenderFace::Triangle t;
        t.vertices[0] = vec3(tri.v0[0],tri.v0[1],tri.v0[2]);
        t.vertices[1] = vec3(tri.v1[0],tri.v1[1], tri.v1[2]);
        t.vertices[2] = vec3(tri.v2[0],tri.v2[1], tri.v2[2]);
        t.normal = vec3(tri.normal[0], tri.normal[1], tri.normal[2]);
        renderTriangles.push_back(t);
    }
}

void setupCornellBoxScene(Scene& scene) {

    scene.camera.position = vec3(0,0,2);
    scene.camera.forward = vec3(0,0,-1);
    scene.camera.up = vec3(0,1,0);
    scene.camera.computeRightVector();

    PbrMaterial* mat = new PbrMaterial;

    // gray diffuse = 0
    mat->diffuseColour = vec3(.80f);
    mat->diffuseRoughness = 0.01f;
    mat->specularColour = vec3(0.0f);
    mat->reflectionColour = vec3(0.1f);
    mat->fresnelSpecularReflection = false;

    scene.addMaterial(mat);

    mat = new PbrMaterial;

    // red diffuse = 1
    mat->diffuseColour = vec3(0.953f, 0.357f, 0.212f);
    mat->specularColour = vec3(0.1f);
    mat->diffuseRoughness = 0.01f;
    mat->reflectionColour = vec3(0.0f);
    mat->specularGlossiness = 0.0f;
    mat->specularRoughness = 1.0f;
    mat->fresnelSpecularReflection = false;

    scene.addMaterial(mat);

    // cyan diffuse = 2
    mat = new PbrMaterial;

    mat->diffuseColour = vec3(0.486f, 0.631f, 0.663f);
    mat->specularColour = vec3(.1f);
    mat->reflectionColour = vec3(0.0f);
    mat->specularGlossiness = 0.0f;
    mat->specularRoughness = 1.0f;

    scene.addMaterial(mat);


    // dark specular = 3
    mat = new PbrMaterial;

    mat->diffuseColour = vec3(0.8);
    mat->specularColour = vec3(1.0f);
    mat->reflectionColour = vec3(0.0f);
    mat->specularGlossiness = 0.0f;
    mat->specularRoughness = .5f;
    mat->diffuseRoughness = .001f;
    scene.addMaterial(mat);

    //35mm camera lens.
    scene.camera.focalLength = .55;

    PointLight* light1 = new PointLight;
    light1->type = LightType::PointLight;
    light1->position = vec3(0, 0.9, 0);
    light1->intensity = 8.0f;
    light1->colour = vec3(1.0f, 1.0f, 0.997f);
    scene.addLight(light1);

    PointLight* light2 = new PointLight;
    light2->position = vec3(0.8,0.8,0.8);
    light2->intensity = 5.0f;
    light2->colour = vec3(1.0f, 1.0f, 0.987f);
    scene.addLight(light2);
    vec3 vertices[] = {
            vec3(-1, 1, 1),
            vec3(1, 1, 1),
            vec3(1, 1, -1),
            vec3(-1, 1, -1),

            vec3(-1, -1, 1),
            vec3(1, -1, 1),
            vec3(1, -1, -1),
            vec3(-1, -1, -1),
    };
    vec3 normals[] = {
            vec3(1, 0, 0),
            vec3(0, 1, 0),
            vec3(0, 0, 1),
            vec3(-1, 0, 0),
            vec3(0, -1, 0),
            vec3(0, 0, -1),
    };

    Mesh* mesh[] = {
            new Mesh,
            new Mesh,
            new Mesh,
            new Mesh,
            new Mesh,
    };
    //bottom -> gray
    mesh[0]->materialId = 0;
    mesh[0]->meshData = new MeshData();
    mesh[0]->meshData
            ->triangles
            .push_back(McRenderFace::Triangle(vertices[4],vertices[5],vertices[7],normals[1]));
    mesh[0]->meshData
            ->triangles
            .push_back(McRenderFace::Triangle(vertices[5],vertices[6],vertices[7],normals[1]));

    //left -> red
    mesh[1]->materialId = 1;
    mesh[1]->meshData = new MeshData();
    mesh[1]->meshData
            ->triangles
            .push_back(McRenderFace::Triangle(vertices[0],vertices[4],vertices[3],normals[0]));
    mesh[1]->meshData
            ->triangles
            .push_back(McRenderFace::Triangle(vertices[4],vertices[7],vertices[3],normals[0]));
    //top -> gray
    mesh[2]->meshData = new MeshData();
    mesh[2]->materialId = 0;
    mesh[2]->meshData
            ->triangles.push_back(McRenderFace::Triangle(vertices[0],vertices[3],vertices[1],normals[4]));
    mesh[2]->meshData
            ->triangles.push_back(McRenderFace::Triangle(vertices[1],vertices[3],vertices[2],normals[4]));
    //right -> cyan
    mesh[3]->materialId = 2;
    mesh[3]->meshData = new MeshData();
    mesh[3]->meshData
            ->triangles.push_back(McRenderFace::Triangle(vertices[1],vertices[2],vertices[5],normals[3]));
    mesh[3]->meshData
            ->triangles.push_back(McRenderFace::Triangle(vertices[2],vertices[6],vertices[5],normals[3]));
    //back -> gray
    mesh[4]->materialId = 0;
    mesh[4]->meshData = new MeshData();
    mesh[4]->meshData
            ->triangles.push_back(McRenderFace::Triangle(vertices[2],vertices[3],vertices[7],normals[2]));
    mesh[4]->meshData
            ->triangles.push_back(McRenderFace::Triangle(vertices[2],vertices[7],vertices[6],normals[2]));

    scene.addObject(mesh[0]);
    scene.addObject(mesh[1]);
    scene.addObject(mesh[2]);
    scene.addObject(mesh[3]);
    scene.addObject(mesh[4]);
}

void addObjectToTestScene(Scene& scene){
    ObjFileReader objReader("models/icosahedron.obj");
    unordered_map<string, shared_ptr<ObjModel>> namedModels = objReader.read();
    Mesh* mesh {nullptr};

    const ObjModel& obj = *namedModels["icosahedron"];
    mesh = new Mesh;
    Mesh::initializeMeshFromObj(*mesh, obj);
    mesh->materialId = 0;
    mesh->transform.scale = vec3(0.5f, 0.5f, 0.5f);
    //scene.addObject(mesh);
    Sphere* sphere = new Sphere(0.3, vec3(.5, -.7f, 0));
    sphere->materialId = 3;
    scene.addObject(sphere);

    sphere = new Sphere(0.5, vec3(-.5, -.5f, -.3));
    sphere->materialId = 3;
    scene.addObject(sphere);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Scene scene2;
    setupCornellBoxScene(scene2);
    addObjectToTestScene(scene2);
    scene2.preprocessMeshes();
    CameraKeyboardController cameraKeyboardController{&scene2.camera};
    RenderTarget renderTarget(SCREEN_WIDTH, SCREEN_HEIGHT);

    RayTracerConfigBuilder builder;
    RayTracerConfig config = builder.useMultithreading(4)
            .maxRayDepth(2)
            .samplingLevel(1)
            .traceShadowsWithBias(.001f)
            .softShadow(true)
            .build();

    PathTracingRenderer rayTracer{config};
    RenderTargetDrawFunction drawFunction{&scene2, &rayTracer, &renderTarget};

    Window window{"", SCREEN_WIDTH, SCREEN_HEIGHT, false};
    window.registerDrawFunction(&drawFunction);
    window.registerKeyboardEventHandler(&cameraKeyboardController);
    window.renderLoop();
    
    return 0;
}