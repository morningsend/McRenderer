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
        const Camera& camera = scene.camera;
        Light* light = scene.lights[0].get();
        Ray ray{camera.position, vec3(0, 0, 0)};
        RayHit hit;
        int closestIndex = 0;
        float fovLength = tan(0.5f * camera.fieldOfViewDegrees / 180.0f * (float) M_PI);
        vec3 meshColour(0.75, 0.75, 0.75);
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                float screenX = (float(x) / float(width - 1) - 0.5f) * 2.0f * fovLength;
                float screenY = -(float(y) / float(height - 1) - 0.5f) * 2.0f * fovLength;
                vec3 direction = vec3(screenX, screenY, camera.focalLength);
                vec3 worldCoord = camera.toWorldCoordinate(screenX, screenY);

                ray.forward = glm::normalize(worldCoord - camera.position);
                closestIntersection(scene.meshes, ray, hit, closestIndex);

                // ray escaped, set pixel colour to background colour: assume black;
                if(!hit.isHit || closestIndex < 0) {
                    target.setColor(x, y, scene.backgroundColour);
                }
                else {
                    auto model = scene.meshes[closestIndex];
                    Material* material = scene.materials[model->materialId].get();

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
                    vec3 lightColour = light->colour * cosine * INVERSE2PI * light->intensity / (distance2) ;
                    vec3 colour = lightColour * dynamic_cast<LambertMaterial*>(material)->diffuseColour;

                    target.setColor(x, y, colour);

                }
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
