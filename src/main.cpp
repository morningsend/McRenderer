//#define GLM_SWIZZLE
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

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

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
    scene.camera.position = vec3(0,0,2.0f);
    scene.camera.forward = vec3(0,0,-1);
    scene.camera.up = vec3(0,1,0);
    scene.camera.computeRightVector();
    scene.camera.focalLength = .55;
    scene.camera.computeFovLength();
    scene.camera.aspectRatio = (float) SCREEN_WIDTH / SCREEN_HEIGHT;
    //scene.envMap.reset(new SphericalEnvMap("images/hdrmaps_com_free_076_4K.hdr"));
    //scene.envMap->setExposure(3.0f);

    PbrMaterial* mat = new PbrMaterial;

    // gray diffuse = 0
    mat->diffuseColour = vec3(1.0f);
    mat->diffuseRoughness = 0.01f;
    mat->fresnelSpecularReflection = false;
    scene.addMaterial(mat);

    mat = new PbrMaterial;

    // red diffuse = 1
    mat->diffuseColour = vec3(0.953f, 0.357f, 0.212f);
    mat->fresnelSpecularReflection = false;
    mat->type = MaterialType::Diffuse;
    scene.addMaterial(mat);

    // cyan diffuse = 2
    mat = new PbrMaterial;

    mat->diffuseColour = vec3(0.486f, 0.631f, 0.663f);
    mat->type = MaterialType::Diffuse;
    scene.addMaterial(mat);

    // dark specular = 3
    mat = new PbrMaterial;

    mat->type = MaterialType::Specular;
    mat->specularColour = vec3(1.0f);
    mat->specularRoughness = .5f;
    mat->specularIndexOfRefraction = 2.5f;
    scene.addMaterial(mat);

    // white emissive = 4
    mat = new PbrMaterial;
    mat->emissiveColour = vec3(1,1,1);
    mat->emissiveIntensity = 1.0f;
    mat->type = MaterialType::Emissive;
    scene.addMaterial(mat);

    // reflective = 5;
    mat = new PbrMaterial;
    mat->reflectionColour = vec3(1);
    mat->type = MaterialType::Reflective;
    scene.addMaterial(mat);

    // specular = 6;
    mat = new PbrMaterial;
    mat->specularColour = vec3(1);
    mat->type = MaterialType::Specular;
    mat->specularRoughness = .2f;
    mat->specularIndexOfRefraction = 2.5f;
    scene.addMaterial(mat);

    // Refractive = 7;
    mat = new PbrMaterial;
    mat->type = MaterialType::Refractive;
    mat->refractiveColour = vec3(1);
    mat->refractiveIndexOfRefraction = 1.5f;
    scene.addMaterial(mat);

    //35mm camera lens.

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
    mesh[2]->materialId = 4;
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
            ->triangles.push_back(McRenderFace::Triangle(vertices[2],vertices[7],vertices[3],normals[2]));
    mesh[4]->meshData
            ->triangles.push_back(McRenderFace::Triangle(vertices[2],vertices[6],vertices[7],normals[2]));

    scene.addObject(mesh[0]);
    scene.addObject(mesh[1]);
    scene.addObject(mesh[2]);
    scene.addObject(mesh[3]);
    scene.addObject(mesh[4]);

    Sphere* sphere = new Sphere(0.2f, vec3(0.3f, -.8f, 0));
    sphere->materialId = 6;
    scene.addObject(sphere);

    sphere = new Sphere(.2f, vec3(-.3f, -.8f, 0));
    sphere->materialId = 5;
    scene.addObject(sphere);
}

void addObjectToTestScene(Scene& scene){
    ObjFileReader objReader("models/icosahedron.obj");
    unordered_map<string, shared_ptr<ObjModel>> namedModels = objReader.read();
    Mesh* mesh {nullptr};

    const ObjModel& obj = *namedModels["icosahedron"];
    mesh = new Mesh;
    Mesh::initializeMeshFromObj(*mesh, obj);
    //scene.addObject(mesh);
}

void setupIBLTestScene(Scene& scene) {
    scene.camera.position = vec3(0,0,2.7);
    scene.camera.forward = vec3(0,0,-1);
    scene.camera.up = vec3(0,1,0);
    scene.camera.computeRightVector();
    scene.camera.focalLength = .35;
    scene.camera.aspectRatio = (float) SCREEN_WIDTH / SCREEN_HEIGHT;
    scene.envMap.reset(new SphericalEnvMap("images/hdrmaps_com_free_076_4K.hdr"));
    scene.envMap->setExposure(3.0f);

    PbrMaterial* mat = new PbrMaterial;

    // gray diffuse = 0
    mat->diffuseColour = vec3(1.0f);
    mat->diffuseRoughness = 0.01f;
    mat->specularColour = vec3(.8f);
    mat->reflectionColour = vec3(0.1f);
    mat->fresnelSpecularReflection = false;
    scene.addMaterial(mat);

    mat = new PbrMaterial;

    // red diffuse = 1
    mat->diffuseColour = vec3(0.953f, 0.357f, 0.212f);
    mat->specularColour = vec3(0.8f);
    mat->diffuseRoughness = 0.01f;
    mat->reflectionColour = vec3(0.0f);
    mat->specularRoughness = 0.01f;
    mat->fresnelSpecularReflection = false;

    scene.addMaterial(mat);

    // cyan diffuse = 2
    mat = new PbrMaterial;

    mat->diffuseColour = vec3(0.486f, 0.631f, 0.663f);
    mat->specularColour = vec3(.8f);
    mat->reflectionColour = vec3(0.0f);
    mat->specularRoughness = 0.01f;

    scene.addMaterial(mat);

    // dark specular = 3
    mat = new PbrMaterial;

    mat->diffuseColour = vec3(0.8);
    mat->specularColour = vec3(1.0f);
    mat->reflectionColour = vec3(0.0f);
    mat->specularRoughness = .5f;
    mat->diffuseRoughness = .001f;
    scene.addMaterial(mat);

    // white emissive = 4
    mat = new PbrMaterial;
    mat->emissiveColour = vec3(1,1,1);
    mat->emissiveIntensity = 1.0f;
    mat->type = MaterialType::Emissive;
    scene.addMaterial(mat);

    // reflective = 5;
    mat = new PbrMaterial;
    mat->reflectionColour = vec3(1);
    mat->type = MaterialType::Reflective;
    scene.addMaterial(mat);

    // specular = 6;
    mat = new PbrMaterial;
    mat->specularColour = vec3(1);
    mat->type = MaterialType::Specular;
    mat->specularRoughness = 0.3f;
    mat->specularIndexOfRefraction = 1.5f;
    scene.addMaterial(mat);

    // Refractive = 7;
    mat = new PbrMaterial;
    mat->type = MaterialType::Refractive;
    mat->refractiveColour = vec3(1);
    mat->refractiveIndexOfRefraction = 1.5f;
    scene.addMaterial(mat);

    Sphere* sphere = new Sphere(0.5f, vec3(0.5, 0, 0));
    sphere->materialId = 0;
    scene.addObject(sphere);

    sphere = new Sphere(.5f, vec3(-.5, 0, 0));
    sphere->materialId = 5;
    scene.addObject(sphere);

    sphere = new Sphere(0.5f, vec3(1.5f, 0, 0));
    sphere->materialId = 6;
    scene.addObject(sphere);

    sphere = new Sphere(0.5f, vec3(-1.5f, 0, 0));
    sphere->materialId = 7;
    scene.addObject(sphere);
    Mesh* plane = new Mesh();

    plane->materialId = 5;
    plane->meshData = new MeshData();
    plane->meshData->triangles.push_back(
            McRenderFace::Triangle(vec3(-5, -0.5f, -5), vec3(5, -0.5f, 5), vec3(-5, -0.5f, 5), vec3(0, 1, 0))
    );
    plane->meshData->triangles.push_back(
            McRenderFace::Triangle(vec3(-5, -0.5f, -5), vec3(5, -0.5f, -5), vec3(5, -0.5f, 5), vec3(0, 1, 0))
    );

    scene.addObject(plane);
}

int main() {
    //testLoadingImage("images/hdrmaps_com_free_076_4K.hdr");
    std::cout << "Hello, World!" << std::endl;
    Scene scene2;
    setupCornellBoxScene(scene2);

    //setupIBLTestScene(scene2);
    scene2.preprocessMeshes();
    CameraKeyboardController cameraKeyboardController{&scene2.camera};
    RenderTarget renderTarget(SCREEN_WIDTH, SCREEN_HEIGHT);

    RayTracerConfigBuilder builder;
    RayTracerConfig config = builder
            .useMultithreading(4)
            .minBounces(4)
            .russianRouletteProb(0.72f)
            .samplingLevel(2)
            .samplingMethod(PixelSamplingMethod::CorrelatedMultiJittered)
            .build();

    PathTracingRenderer renderer{config};
    RenderTargetDrawFunction drawFunction{&scene2, &renderer, &renderTarget};

    Window window{"", SCREEN_WIDTH, SCREEN_HEIGHT, false};
    window.registerDrawFunction(&drawFunction);
    window.registerKeyboardEventHandler(&cameraKeyboardController);
    window.renderLoop();

    renderTarget.saveHdrOutput("output.hdr");
    renderTarget.savePngOutput("output.png");
    return 0;
}