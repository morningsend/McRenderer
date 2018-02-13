//
// Created by Zaiyang Li on 31/01/2018.
//
#include <cmath>
#include <iostream>
#include "PathTracer.hpp"


namespace McRenderFace {

    void PathTracer::render(Scene &scene, RenderTarget &target) {
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
                    closestIntersection(scene.meshes, ray, hit, closestIndex);
                    // ray escaped, set pixel colour to background colour: assume black;

                    if (!hit.isHit || closestIndex < 0) {
                        target.setColor(x, y, scene.backgroundColour);
                    } else {
                        auto model = scene.meshes[closestIndex];
                        Material *material = scene.materials[model->materialId].get();

                        // pure coloure
                        //target.setColor(x, y, dynamic_cast<LambertMaterial*>(material)->diffuseColour);
                        //continue;

                        vec3 toLight = light->position - hit.position;
                        float distance2 = glm::dot(toLight, toLight);
                        float distance = sqrt(distance2);
                        toLight /= distance;

                        //ray position needs a bias to avoid shadow acne.
                        //https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows
                        //Ray shadowRay{hit.position + hit.normal * config.shadowBias, toLight};

                        float cosine = glm::dot(toLight, hit.normal);
                        cosine = cosine > 0 ? cosine : 0;
                        vec3 lightColour = light->colour * cosine * INVERSE2PI * light->intensity / (distance2);
                        vec3 colour = lightColour * dynamic_cast<LambertMaterial *>(material)->diffuseColour;

                        colourAccum += colour;
                    }
                }
                colourAccum *= inverseSampleSize;
                target.setColor(x, y, colourAccum);
            }
//            loop through triangles
//            find intersection using the equation
//            check intersection distance is closer than before
//            set new intersection
//                    return if any intersection exists
        }
    }

    bool PathTracer::traceShadow(Scene &scene, float lightDistance, const Ray &ray) {
        return false;
    }

    void PathTracer::generateRayDirectionsAtPixel(int width, int height, int x, int y, const Camera& camera, vector<vec3> rayDirecitons) {
        vec2 pixelCenter(x + 0.5f, y + 0.5f);
        vec2 variance(0.25f);
        vec2 pointSample;
        for(int i = 0; i < cameraRaySamples.size(); i++) {
            sampler.sample(pointSample, pixelCenter, variance);
            float screenX = (pointSample.x / float(width - 1) - 0.5f) * 2.0f * camera.fovLength;
            float screenY = -(pointSample.y / float(height - 1) - 0.5f) * 2.0f * camera.fovLength;
            vec3 worldCoord = camera.toWorldCoordinate(screenX, screenY);

            cameraRaySamples[i] = glm::normalize(worldCoord - camera.position);
        }
    }

    void closestIntersection(vector<shared_ptr<Mesh>> models, const Ray& ray, RayHit& hitResult, int& closestIndex) {
        int closest = -1;
        RayHit closestHit;
        closestHit.t = MAXFLOAT;
        RayHit hit;
        shared_ptr<Mesh> mesh;
        int modelCount = static_cast<int>(models.size());
        for(int i = 0; i < modelCount; i++) {
            mesh = models[i];
            hit = mesh->castRay(ray);
            if(hit.isHit && hit.t < closestHit.t) {
                closestHit = hit;
                closest = i;
            }
        }
        closestIndex = closest;
        hitResult = closestHit;
    }
}
