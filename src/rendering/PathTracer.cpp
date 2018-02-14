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
        closestIntersection(scene.objects, ray, hit, closestIndex);
        // ray escaped, set pixel colour to background colour: assume black;
        if (!hit.isHit || closestIndex < 0) {
            return scene.backgroundColour;
        }

        // for each light, determine if it is occluded,
        // if not in shadow, compute the lights contribution to surface by evaluating BDRF.
        vec3 shadowRayOrigin = hit.position + hit.normal * 0.001f;
        vector<shared_ptr<Light>>& lights = scene.lights;
        vec3 colourOutput = vec3(0);
        for(int i = 0; i < lights.size(); i++) {

            vec3 toLight = light->position - hit.position;
            float distance2 = glm::dot(toLight, toLight);
            float distance = sqrt(distance2);
            toLight /= distance;

            RayHit shadowRayHit = traceShadowRay(shadowRayOrigin, scene, *(scene.lights[i].get()), distance);
            if (shadowRayHit.isHit && shadowRayHit.t < distance) {
                continue;
            }

            PbrShaderOutput output;

            SceneObject *model = scene.objects[closestIndex].get();
            PbrMaterial *material = dynamic_cast<PbrMaterial *>(scene.materials[model->materialId].get());

            // pure colour
            // target.setColor(x, y, dynamic_cast<LambertMaterial*>(material)->diffuseColour);
            // continue;

            surfaceParameters.surfaceNormal = hit.normal;
            surfaceParameters.rayIncoming = ray.forward;
            lightParameters.lightColour = light->colour;



            lightParameters.lightDirection = toLight;
            lightParameters.lightDistance = distance;
            lightParameters.lightExposure = light->exposure;
            // light intensity inverse square attenuation.
            lightParameters.lightIntensity = static_cast<float>(light->intensity * 0.25 * M_1_PI / distance2);
            lightParameters.lightColour = light->colour;
            lightParameters.viewerDirection = glm::normalize(camera.position - hit.position);

            pbrShader.compute(*material, lightParameters, surfaceParameters, output);
            //ray position needs a bias to avoid shadow acne.
            //https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows
            //Ray shadowRay{hit.position + hit.normal * config.shadowBias, toLight};

            //float cosine = glm::dot(toLight, hit.normal);
            //cosine = cosine > 0 ? cosine : 0;
            //vec3 lightColour = light->colour * cosine * INVERSE2PI * light->intensity / (distance2);
            //vec3 colour = lightColour * dynamic_cast<LambertMaterial *>(material)->diffuseColour;
            colourOutput += output.colour;
        }
        return colourOutput;
    }

    int PathTracer::selectLight(vector<shared_ptr<Light>> lights, const int size, vec3 position) {
        if(size < 1) {
            return -1;
        }

        float contributionsCDF[size];
        float distance2 = 0.0f;
        float total = 0.0f;
        vec3 l = lights[0]->position - position;
        contributionsCDF[0] = lights[0] -> intensity / distance2;

        for(int i = 1; i < size; i++) {
            Light* light = lights[i].get();
            l = light->position - position;
            distance2 = glm::dot(l, l);
            contributionsCDF[i] = contributionsCDF[i-1] + light->intensity / distance2;
        }

        float p = sampleUniform(0, 1) * contributionsCDF[size - 1];
        for(int i = 0; i < size; i++) {
            if(contributionsCDF[i] < p) {
                return i;
            }
        }
        return -1;
    }

    float PathTracer::sampleUniform(float min, float max) {
        return 0;
    }

    /**
     * intersects ray with geometry and
     * computes colour for primary ray bounce.
     * return true if path terminates
     * @param ray
     * @param scene
     * @param colour
     * @return
     */
    bool PathTracer::tracePrimaryRay(const Ray& ray, Scene& scene, vec3& colour) {
        RayHit hit;
        int closestIndex = -1;
        // primary ray
        closestIntersection(scene.objects, ray, hit, closestIndex);
        if(!hit.isHit || closestIndex < 0){
            colour = scene.backgroundColour;
        }
        return true;
    }

    /**
     * Terminate early if a closer intersection point is find.
     * @param position
     * @param scene
     * @param light
     * @return
     */
    RayHit PathTracer::traceShadowRay(vec3 position, Scene &scene, Light &light, float lightDistance) {
        Ray ray{position, glm::normalize(light.position - position)};
        RayHit hit;
        for(auto& obj : scene.objects) {
            hit = obj->castRay(ray);
            if(hit.isHit && hit.t < lightDistance) {
                return hit;
            }
        }
        return hit;
    }

    void traceSecondary(const Ray& ray, Scene& scene) {

    }

    void closestIntersection(vector<shared_ptr<SceneObject>>& models, const Ray& ray, RayHit& hitResult, int& closestIndex) {
        int closest = -1;
        RayHit closestHit;
        closestHit.t = MAXFLOAT;
        RayHit hit;
        SceneObject* obj;
        int modelCount = static_cast<int>(models.size());
        for(int i = 0; i < modelCount; i++) {
            obj = models[i].get();
            hit = obj->castRay(ray);
            if(hit.isHit && hit.t > 0 && hit.t < closestHit.t) {
                closestHit = hit;
                closest = i;
            }
        }
        closestIndex = closest;
        hitResult = closestHit;
    }
}