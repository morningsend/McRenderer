#include <iostream>
#include "window/Window.hpp"
#include "window/TestDrawFunction.hpp"
#include "scene/Scene.hpp"
#include "scene/TestModelH.h"

using namespace std;
using namespace McRenderer;

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

void convertTriangles(vector<::Triangle>& testTriangles, vector<McRenderer::Triangle> renderTriangles) {
    for(::Triangle& tri : testTriangles){
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

    scene.camera = Camera(
            vec4{277.5f, 277.5f, 0.0f, 0.0f},
            vec4{0,0,1,0},
            vec4{0,1,0,0}
    );
    scene.camera.position = vec3();
    scene.lights.push_back(PointLightSource());
    convertTriangles(triangles, scene.model);
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Scene scene;
    setupCornellBoxScene(scene);
    TestDrawFunction testImage;
    Window window{"", SCREEN_WIDTH, SCREEN_HEIGHT, false};
    window.registerDrawFunction(&testImage);
    window.renderLoop();
    
    return 0;
}