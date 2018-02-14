//
// Created by Zaiyang Li on 13/02/2018.
//

#include <iostream>
#include "PathTracer.hpp"
#include "PathTracingRenderer.hpp"

namespace McRenderFace {

    vec3 PathTracer::traceRay(Scene &scene, const Ray& ray) {
        Light* light = scene.lights[0].get();
        RayHit hit;
        vector<RayPath>paths(static_cast<unsigned long>(config.maxRayDepth));
        vec3 direct(0);
        vec3 indirect(0);

        traceDirectRay(ray, scene, hit, direct);
        if(hit.isHit) {
            surfaceParameters.rayIncoming = ray.forward;
            traceIndirectRay(scene, hit, indirect);
        }
        return direct + indirect;
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
    void PathTracer::traceDirectRay(const Ray &ray, Scene &scene, RayHit& hit, vec3 &directColour) {
        int closestObjectIndex = -1;
        // primary ray
        closestIntersection(scene.objects, ray, hit, closestObjectIndex);
        if(!hit.isHit || closestObjectIndex < 0){
            directColour = scene.backgroundColour;
            return;
        }
        int materialId = scene.objects[closestObjectIndex]->materialId;
        currentMaterial = dynamic_cast<PbrMaterial *>(scene.materials[materialId].get());
        surfaceParameters.rayIncoming = ray.forward;
        surfaceParameters.surfaceNormal = hit.normal;
        surfaceParameters.position = hit.position;
        directColour = evaluateLightContributions(surfaceParameters, scene);
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
        return hit;
    }

    void PathTracer::traceIndirectRay(Scene& scene, const RayHit& hit, vec3 &indirect) {
        PbrBrdfSampleOutput output;

        int closestObjectIndex = -1;
        int bounces;
        RayPath path;
        RayHit lastHit = hit;

        float russianRouletteProbability = 0.0f;
        surfaceParameters.position = hit.position;
        surfaceParameters.surfaceNormal = hit.normal;
        // trace paths until we reach the termination condition.
        // store all paths but do not evaluate light contributions yet.
        for(bounces = 0; bounces < config.maxRayDepth; bounces++) {
            pbrShader.sample(*currentMaterial, surfaceParameters, output);
            path.incomingRay.origin = lastHit.position + lastHit.normal * config.secondaryRayBias;
            path.incomingRay.forward = output.direction;

            //std::cout << "bounces" << bounces << ' ' << path.incomingRay.forward.x << ',' << path.incomingRay.forward.y << ',' << path.incomingRay.forward.z << '.' << endl;
            closestIntersection(scene.objects, path.incomingRay, path.hit, path.objectIndex);
            // ray escaped, set pixel colour to background colour: assume black;
            if (!path.hit.isHit || path.objectIndex < 0) {
                path.lightContribution = vec3(0);
                //terminate.
                break;
            }
            indirectRayPaths[bounces] = path;
            lastHit = path.hit;
            surfaceParameters.position = lastHit.position;
            surfaceParameters.surfaceNormal = lastHit.normal;
            surfaceParameters.rayIncoming = path.incomingRay.forward;
            //TODO: add russian roulette termination.
            //russianRouletteProbability = sampleRussianRoulette();
            //if(russianRouletteProbability < config.killProbabilityThreshold) {
            //    break;
            //}
        }

        if(bounces < 1) {
            indirect= vec3(0);
            return;
        }

        // sum up all contribution from path segments, last segment first until we reach the starting point.
        vec3 pathContribution(0);
        float distance;
        RayPath& path2 = indirectRayPaths[bounces - 1];
        int materialId = scene.objects[path2.objectIndex]->materialId;
        currentMaterial = dynamic_cast<PbrMaterial *>(scene.materials[materialId].get());
        surfaceParameters.rayIncoming = path2.incomingRay.forward;
        surfaceParameters.surfaceNormal = path2.hit.normal;
        surfaceParameters.position = path2.hit.position;
        path2.lightContribution = evaluateLightContributions(surfaceParameters, scene);

        for(int i = bounces - 2; i >=0 ; i--) {
            RayPath& lastPath = indirectRayPaths[i + 1];
            path2 = indirectRayPaths[i];
            if(!path2.hit.isHit || path2.objectIndex < 0) {
                continue;
            }
            materialId = scene.objects[path2.objectIndex]->materialId;
            currentMaterial = dynamic_cast<PbrMaterial *>(scene.materials[materialId].get());
            surfaceParameters.rayIncoming = path2.incomingRay.forward;
            surfaceParameters.surfaceNormal = path2.hit.normal;
            surfaceParameters.position = path2.hit.position;
            path2.lightContribution = evaluateLightContributions(surfaceParameters, scene);

            vec3 toLastPoint = (lastPath.hit.position - path2.hit.position);
            float distance2 = glm::dot(toLastPoint, toLastPoint);
            distance2 = distance2 < 1 ? 1 : distance2;
            path2.lightContribution += lastPath.lightContribution / (distance2 * 0.50f * INVERSE2PI) * 0.3f;
        }

        indirect = indirectRayPaths[0].lightContribution;
    }

    vec3 PathTracer::evaluateLightContributions(const PbrSurfaceParameters &parameters, Scene &scene) {
        vec3 contributionsAccum(0);
        vector<shared_ptr<Light>>& lights = scene.lights;
        PbrShaderOutput output;
        for(auto& light : lights) {
            vec3 toLight = light->position - parameters.position;
            float distance2 = glm::dot(toLight, toLight);
            float distance = sqrt(distance2);
            toLight /= distance;
            RayHit shadowRayHit = traceShadowRay(parameters.position + parameters.surfaceNormal * config.shadowRayBias,
                                                 scene,
                                                 *(light.get()),
                                                 distance);
            // in shadow, ray hit something in front of the light.
            if(shadowRayHit.isHit && shadowRayHit.t > 0 && shadowRayHit.t < distance) {
                continue;
            }

            // pure colour
            // target.setColor(x, y, dynamic_cast<LambertMaterial*>(material)->diffuseColour);
            // continue;
            lightParameters.lightColour = light->colour;
            lightParameters.lightDirection = toLight;
            lightParameters.lightExposure = light->exposure;
            // light intensity inverse square attenuation.
            lightParameters.lightIntensity = static_cast<float>(light->intensity * 0.25 * M_1_PI / distance2);
            lightParameters.viewerDirection = glm::normalize(scene.camera.position - parameters.position);

            pbrShader.compute(*currentMaterial, lightParameters, parameters, output);
            contributionsAccum += output.colour;
        }
        return contributionsAccum;
    }

    float PathTracer::sampleRussianRoulette() {
        return 0.5;
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