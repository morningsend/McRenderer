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
        Camera& camera = scene.camera;
        camera.computeFovLength();
        Ray ray{camera.position, vec3(0, 0, 0)};
        RayHit hit;
        vec3 colourAccum(0.0f);
        float sampleSquareWidth = static_cast<float>(1 << config.samplingLevel);
        float sampleSize = sampleSquareWidth * sampleSquareWidth;
        float sampleSizeInv = 1.0f / sampleSize;
        float sampleWidthInv = 1.0f / sampleSize;
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                colourAccum = vec3(0);
                for(int xx = 0; xx < sampleSquareWidth; xx++) {
                    for(int yy = 0; yy < sampleSquareWidth; yy++) {
                        vec2 sample = uniformSampler.sample() * sampleWidthInv;
                        sample = vec2(x, y) + vec2(xx * sampleWidthInv, yy * sampleWidthInv);
                        float screenX = -(sample.x / float(width - 1) - 0.5f) * 2.0f * camera.fovLength;
                        float screenY = -(sample.y / float(height - 1) - 0.5f) * 2.0f * camera.fovLength;
                        vec3 dir = normalize(camera.toWorldCoordinate(screenX, screenY) - camera.position);
                        ray.forward = dir;
                        colourAccum += pathTracer.traceRay(scene, ray);
                    }
                }
                colourAccum *= sampleSizeInv;
                target.setColor(x, y, colourAccum);
            }
        }
    }
}
