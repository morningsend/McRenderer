//
// Created by Zaiyang Li on 13/02/2018.
//

#include <iostream>
#include "PathTracer.hpp"

namespace McRenderFace {

    vec3 PathTracer::traceRay(Scene &scene, const Ray& ray) {
        PbrBrdfSampleOutput samplerOutput;
        PbrLightParameters lightParameters;
        PbrShaderOutput shaderOutput;
        Light defaultLight = *scene.lights[0];
        int closestObjectIndex = -1;
        int bounces;
        RayPath path;
        RayHit hit;
        RayHit shadowHit;
        vec3 outputColour{0};
        PbrMaterial* currentMaterial;
        int materialId;
        float scale = 1;
        // primary path.
        closestIntersection(scene.objects, ray, path.hit, path.objectIndex);

        if(!path.hit.isHit || path.objectIndex < 0) {
            return scene.backgroundColour;
        }
        shadowHit = traceShadowRay(path.hit.position+ path.hit.normal * config.shadowRayBias, scene, defaultLight);

        surfaceParameters.position = path.hit.position;
        surfaceParameters.surfaceNormal = path.hit.normal;
        surfaceParameters.rayIncoming = path.incomingRay.forward;

        lightParameters.viewerDirection = glm::normalize(path.incomingRay.forward * -1.0f);
        lightParameters.lightColour = defaultLight.colour;
        lightParameters.lightDirection = glm::normalize(defaultLight.position - path.hit.position);
        lightParameters.lightExposure = defaultLight.exposure;
        lightParameters.lightIntensity = defaultLight.intensity;
        lightParameters.lightPosition = defaultLight.position;

        materialId = scene.objects[path.objectIndex]->materialId;
        currentMaterial = dynamic_cast<PbrMaterial *>(scene.materials[materialId].get());
        if(!shadowHit.isHit) {
            pbrShader.compute(
                    *currentMaterial,
                    lightParameters,
                    surfaceParameters,
                    shaderOutput
            );
            outputColour = shaderOutput.colour;
        }
        //
        // trace paths until we reach the termination condition.
        // store all paths but do not evaluate light contributions yet.
        for(bounces = 0; bounces < 4; bounces++) {
            pbrShader.sample(*currentMaterial, surfaceParameters, samplerOutput);
            scale /= samplerOutput.pdf;
            path.incomingRay.origin = path.hit.position + path.hit.normal * config.secondaryRayBias;
            path.incomingRay.forward = samplerOutput.direction;

            //std::cout << "bounces" << bounces << ' ' << path.incomingRay.forward.x << ',' << path.incomingRay.forward.y << ',' << path.incomingRay.forward.z << '.' << endl;
            closestIntersection(scene.objects, path.incomingRay, path.hit, path.objectIndex);
            // ray escaped, set pixel colour to background colour: assume black;
            if (!path.hit.isHit || path.objectIndex < 0) {
                //terminate.
                break;
            }
            shadowHit = traceShadowRay(path.hit.position + path.hit.normal * config.shadowRayBias, scene, defaultLight);

            surfaceParameters.position = path.hit.position;
            surfaceParameters.surfaceNormal = path.hit.normal;
            surfaceParameters.rayIncoming = path.incomingRay.forward;

            lightParameters.viewerDirection = glm::normalize(path.incomingRay.forward * -1.0f);
            lightParameters.lightColour = defaultLight.colour;
            lightParameters.lightDirection = glm::normalize(defaultLight.position - path.hit.position);
            lightParameters.lightExposure = defaultLight.exposure;
            lightParameters.lightIntensity = defaultLight.intensity;
            lightParameters.lightPosition = defaultLight.position;
            materialId = scene.objects[path.objectIndex]->materialId;
            currentMaterial = dynamic_cast<PbrMaterial *>(scene.materials[materialId].get());

            if(!shadowHit.isHit){

                pbrShader.compute(
                        *currentMaterial,
                        lightParameters,
                        surfaceParameters,
                        shaderOutput
                );

                outputColour += shaderOutput.colour;
            }
            if(!sampleRussianRoulette()) {
                //cout << "Russiang roulette: ray terminated at " << bounces << " bounces" << endl;
                break;
            }
        }
        //cout << "bounces " << bounces << endl;
        return outputColour;
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
    void PathTracer::traceSinglePath(const Ray &ray, Scene &scene, RayHit &hit, RayPath &path) {
        int closestObjectIndex = -1;
        // primary ray
        closestIntersection(scene.objects, ray, hit, closestObjectIndex);
        if(!hit.isHit || closestObjectIndex < 0){
            return;
        }
        path.incomingRay = ray;
        path.objectIndex = closestObjectIndex;
        path.hit = hit;
    }

    /**
     * Terminate early if a closer intersection point is find.
     * @param position
     * @param scene
     * @param light
     * @return
     */
    RayHit PathTracer::traceShadowRay(vec3 position, Scene &scene, Light &light) {
        Ray ray{position, glm::normalize(light.position - position)};
        float lightDistance = glm::dot(ray.forward, (light.position - position));
        RayHit hit;
        switch (light.type) {
            case LightType::PointLight:
                for (auto &obj : scene.objects) {
                    hit = obj->castRay(ray);
                    if (hit.isHit && hit.t > 0 && hit.t < lightDistance) {
                        return hit;
                    }
                }
                break;
            case LightType::AreaLight:

                break;
            default:
                break;
        }
        hit.isHit = false;
        return hit;
    }

    bool PathTracer::sampleRussianRoulette() {
        return uniform(gen) < config.killProbabilityThreshold;
    }

    vec3 PathTracer::evaluateLightContributions(const PbrSurfaceParameters &surface, Scene &scene) {
        return glm::vec3(1);
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