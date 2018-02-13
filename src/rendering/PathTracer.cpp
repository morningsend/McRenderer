//
// Created by Zaiyang Li on 13/02/2018.
//

#include "PathTracer.hpp"
#include "PathTracingRenderer.hpp"

namespace McRenderFace {

    vec3 PathTracer::traceRay(Scene &scene, const Ray& ray) {
        float focalLength = scene.camera.focalLength;
        Camera& camera = scene.camera;
        camera.computeFovLength();
        Light* light = scene.lights[0].get();
        RayHit hit;
        int closestIndex = -1;
        // primary ray
        closestIntersection(scene.meshes, ray, hit, closestIndex);
        // ray escaped, set pixel colour to background colour: assume black;
        if (!hit.isHit || closestIndex < 0) {
            return scene.backgroundColour;
        }

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

        return colour;
    }

    void closestIntersection(vector<shared_ptr<Mesh>>& models, const Ray& ray, RayHit& hitResult, int& closestIndex) {
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