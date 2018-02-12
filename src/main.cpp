#define GLM_SWIZZLE
#include <iostream>
#include "window/Window.hpp"
#include "window/TestDrawFunction.hpp"
#include "scene/SimpleScene.hpp"
#include "scene/TestModelH.h"
#include "CameraKeyboardController.hpp"
#include "rendering/RenderTarget.hpp"
#include "rendering/RayTracer.hpp"
#include "rendering/RenderTargetDrawFunction.hpp"

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

void setupCornellBoxScene(SimpleScene& scene) {
    vector<::Triangle> triangles;
    LoadTestModel(triangles);

    scene.camera.position = vec3(0,0,-2);
    scene.camera.forward = vec3(0,0,1);
    scene.camera.up = vec3(0,1,0);
    scene.camera.computeRightVector();

    //35mm camera lens.
    scene.camera.focalLength = .55;

    PointLight light1;
    light1.type = LightType::PointLight;
    light1.position = vec3(-.2f, 0.7f, -0.8f);
    light1.intensity = 20.0f;
    scene.lights.push_back(light1);

    PointLight light2;
    light2.type = LightType::PointLight;
    light2.position = vec3(0, 0.99f, 0.0f);
    light2.intensity = 15.0f;
    scene.lights.push_back(light2);

    convertTriangles(triangles, scene.model);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    SimpleScene scene;
    Scene scene2;
    createTestScene(scene2);

    setupCornellBoxScene(scene);

    CameraKeyboardController cameraKeyboardController{&scene.camera};
    RenderTarget renderTarget(SCREEN_WIDTH, SCREEN_HEIGHT);

    RayTracerConfigBuilder builder;
    RayTracerConfig config = builder.useMultithreading(4)
            .maxRayDepth(5)
            .maxSamplingLevel(0)
            .minSamplingLevel(-3)
            .traceShadowsWithBias(.001f)
            .softShadow(true)
            .build();

    RayTracer rayTracer{config};
    RenderTargetDrawFunction drawFunction{&scene2, &rayTracer, &renderTarget};

    Window window{"", SCREEN_WIDTH, SCREEN_HEIGHT, false};
    window.registerDrawFunction(&drawFunction);
    window.registerKeyboardEventHandler(&cameraKeyboardController);
    window.renderLoop();
    
    return 0;
}