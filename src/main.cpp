#include <iostream>
#include "window/Window.hpp"
#include "window/TestDrawFunction.hpp"
#include "scene/Scene.hpp"
#include "scene/TestModelH.h"
#include "CameraKeyboardController.hpp"
#include "rendering/RenderTarget.hpp"
#include "rendering/RayTracer.hpp"
#include "rendering/RenderTargetDrawFunction.hpp"

using namespace std;
using namespace McRenderer;

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

void convertTriangles(const vector<::Triangle>& testTriangles, vector<McRenderer::Triangle>& renderTriangles) {
    for(const ::Triangle& tri : testTriangles){
        McRenderer::Triangle t;
        t.vertices[0] = tri.v0;
        t.vertices[1] = tri.v1;
        t.vertices[2] = tri.v2;
        t.normal = tri.normal;
        t.colour = tri.color;
        renderTriangles.push_back(t);
    }
}

void setupCornellBoxScene(Scene& scene) {
    vector<::Triangle> triangles;
    LoadTestModel(triangles);

    scene.camera.position = vec3(0,0,-2);
    scene.camera.forward = vec3(0,0,1);
    scene.camera.up = vec3(0,1,0);
    scene.camera.computeRightVector();

    //35mm camera lens.
    scene.camera.focalLength = .55;

    PointLightSource light1;
    light1.position = vec3(-.2f, 0.7f, -0.8f);
    light1.intensity = 20.0f;
    scene.lights.push_back(light1);

    PointLightSource light2;
    light2.position = vec3(0, 0.99f, 0.0f);

    scene.lights.push_back(light2);

    convertTriangles(triangles, scene.model);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Scene scene;
    setupCornellBoxScene(scene);

    CameraKeyboardController cameraKeyboardController{&scene.camera};
    RenderTarget renderTarget(SCREEN_WIDTH, SCREEN_HEIGHT);
    RayTracer rayTracer{4};
    RenderTargetDrawFunction drawFunction{&scene, &rayTracer, &renderTarget};

    Window window{"", SCREEN_WIDTH, SCREEN_HEIGHT, false};
    window.registerDrawFunction(&drawFunction);
    window.registerKeyboardEventHandler(&cameraKeyboardController);
    window.renderLoop();
    
    return 0;
}