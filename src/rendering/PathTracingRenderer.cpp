//
// Created by Zaiyang Li on 31/01/2018.
//
#include <cmath>
#include <iostream>
#include "PathTracingRenderer.hpp"


namespace McRenderFace {

    void PathTracingRenderer::render(Scene &scene, RenderTarget &target) {
        const int width = target.getWidth();
        const int height = target.getHeight();
        target.clear();
        float focalLength = scene.camera.focalLength;
        Camera& camera = scene.camera;
        camera.computeFovLength();
        Light* light = scene.lights[0].get();
        Ray ray{camera.position, vec3(0, 0, 0)};
        RayHit hit;
        int closestIndex = 0;
        vec3 meshColour(0.75, 0.75, 0.75);
        const float inverseSampleSize = 1.0f / static_cast<float>(1 << config.samplingLevel);
        vec3 colourAccum(0.0f);
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                generateRayDirectionsAtPixel(width, height, x, y, camera, cameraRaySamples);
                colourAccum = vec3(0);
                // shoot multiple rays for anti-aliasing.
                for (int i = 0; i < cameraRaySamples.size(); i++) {
                    ray.forward = cameraRaySamples[i];
                    colourAccum += pathTracer.traceRay(scene, ray);
                }
                colourAccum *= inverseSampleSize;
                target.setColor(x, y, colourAccum);
            }
        }
    }

    void PathTracingRenderer::generateRayDirectionsAtPixel(int width, int height, int x, int y, const Camera& camera, vector<vec3>& rayDirecitons) {
        //sampler.reset();
        vec2 pixelCenter(x + 0.5f, y + 0.5f);
        vec2 variance(.26f);
        vec2 pointSample;

        for(int i = 0; i < rayDirecitons.size(); i++) {
            sampler.sample(pointSample, pixelCenter, variance);
            float screenX = (pointSample.x / float(width - 1) - 0.5f) * 2.0f * camera.fovLength;
            float screenY = -(pointSample.y / float(height - 1) - 0.5f) * 2.0f * camera.fovLength;
            vec3 worldCoord = camera.toWorldCoordinate(screenX, screenY);

            rayDirecitons[i] = glm::normalize(worldCoord - camera.position);
        }
    }
}
