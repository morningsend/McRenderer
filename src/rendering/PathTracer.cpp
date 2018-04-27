//
// Created by Zaiyang Li on 13/02/2018.
//

#include <iostream>
#include "PathTracer.hpp"

namespace McRenderFace {
    vec3 debugPathSize(vector<RaySurfaceInteraction> vertices, int maxDepth) {
        float weight = (float) vertices.size() / maxDepth;
        return vec3(1) * weight;
    }
    vec3 debugDiffuse(vector<RaySurfaceInteraction> vertices) {
        if(vertices.size() < 1) {
            return vec3(0);
        } else {
            return vertices[0].material->diffuseColour;
        }
    }
    vec3 PathTracer::traceRay(Scene &scene, const Ray& ray) {
        Ray currentRay = ray;
        int hitObjectIndex = -1;
        RayHit hit;
        PbrMaterial* currentMaterial;
        int materialId = 0;
        BxdfSample sample;
        RaySurfaceInteraction inter;
        pathVertices.clear();
        float currentRefractiveIOR = 1.0f;
        for(int i = 0; i < config.minRayBounces; i++) {
            hit.isHit = false;
            closestIntersection(scene.objects, currentRay, hit, hitObjectIndex);

            if(!hit.isHit || hitObjectIndex < 0) {
                inter.objectIndex = -1;
                inter.wOut = -currentRay.forward;
                inter.wIn = vec3(0);
                inter.normal = vec3(0);
                inter.material = nullptr;
                inter.emission = scene.envMap ? scene.envMap->sampleNormal(currentRay.forward) : vec3(.2f);
                inter.sample = BxdfSample();
                pathVertices.push_back(inter);
                break;
            }
            inter.hit = hit;
            inter.objectIndex = hitObjectIndex;
            inter.wOut = -currentRay.forward;
            inter.normal = hit.normal;
            materialId = scene.objects[hitObjectIndex]->materialId;

            currentMaterial = scene.materials[materialId].get();
            switch(currentMaterial->type) {
                case MaterialType::Specular:
                    cookTorranceBrdf.sampleGGXNormalDistribution(inter.wOut,
                                                                      inter.normal,
                                                                      currentMaterial->specularRoughness,
                                                                      sample);
                    break;
                case MaterialType::Reflective:
                    sample.direction = currentRay.forward - inter.normal * (dot(currentRay.forward, inter.normal) * 2);
                    sample.probability = 1;
                    break;
                case MaterialType::Diffuse:
                    lambertBrdf.sample(inter.wOut, sample);
                    break;
                case MaterialType::Refractive:
                    fresnelBsdf.sampleRefraction(currentRefractiveIOR,
                                                 currentMaterial->refractiveIndexOfRefraction,
                                                 inter.wOut,
                                                 inter.normal,
                                                 sample);
                    // must reverse normal when inside a medium.
                    if(dot(sample.direction, inter.normal) < 0) {
                        inter.normal *= -1.0f;
                        currentRefractiveIOR = currentMaterial->refractiveIndexOfRefraction;
                    } else {
                        currentRefractiveIOR = 1.0f;
                    }
                    break;
                // fall back to lambert
                default:
                    lambertBrdf.sample(inter.wOut, sample);
                    break;
            }

            currentRay.origin = hit.position + hit.normal * 0.001f;
            currentRay.forward = sample.direction;

            inter.material = currentMaterial;
            inter.emission = currentMaterial->emissiveColour * currentMaterial->emissiveIntensity;
            inter.wIn = sample.direction;
            inter.sample = sample;
            inter.materialType = currentMaterial->type;
            pathVertices.push_back(inter);
        }
        /*
        float russianRouletteProb = config.killProbability;
        while(sampleRussianRoulette()) {
            hit.isHit = false;
            closestIntersection(scene.objects, currentRay, hit, hitObjectIndex);

            if(!hit.isHit || hitObjectIndex < 0) {
                inter.hit = hit;
                inter.objectIndex = -1;
                inter.wOut = -currentRay.forward;
                inter.wIn = vec3(0);
                inter.normal = vec3(0);
                inter.material = nullptr;
                inter.emission = scene.envMap->sampleNormal(currentRay.forward);
                inter.sample = BxdfSample();
                break;
            }
            inter.hit = hit;
            inter.objectIndex = hitObjectIndex;
            inter.wOut = -currentRay.forward;
            inter.normal = hit.normal;
            materialId = scene.objects[hitObjectIndex]->materialId;

            currentMaterial = scene.materials[materialId].get();
            lambertBrdf.sample(inter.normal, sample);
            currentRay.origin = hit.position + hit.normal * 0.001f;
            currentRay.forward = sample.direction;

            inter.material = currentMaterial;
            inter.emission = currentMaterial->emissiveColour * currentMaterial->emissiveIntensity;
            inter.wIn = sample.direction;
            inter.sample = sample;
            pathVertices.push_back(inter);
        }*/

        return evaluateLightContributions(pathVertices);
        //return debugPathSize(pathVertices, config.maxRayDepth);
        //return debugDiffuse(pathVertices);
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
    void PathTracer::traceSinglePath(const Ray &ray, Scene &scene, RayHit &hit, RaySurfaceInteraction &path) {
        int closestObjectIndex = -1;
        // primary ray
        closestIntersection(scene.objects, ray, hit, closestObjectIndex);
        if(!hit.isHit || closestObjectIndex < 0){
            return;
        }

        path.wIn = -ray.forward;
        path.wOut = vec3(0);
        path.objectIndex = closestObjectIndex;
        path.hit = hit;
    }

    bool PathTracer::sampleRussianRoulette() {
        return uniform(gen) < config.killProbability;
    }

    vec3 PathTracer::evaluateLightContributions(std::vector<RaySurfaceInteraction> vertices) {
        if(vertices.size() < 1) {
            return vec3(0);
        }
        const int size = vertices.size();
        vec3 lightAccum = vertices[size - 1].emission;
        float brdf = 0.0f;
        vec3 surfaceColour;
        for(int i = size - 2; i >= 0; i--) {
            RaySurfaceInteraction& interaction = vertices[i];
            PbrMaterial* material = interaction.material;
            surfaceColour = vec3(0);
            float wInDotN = std::max<float>(dot(interaction.wIn, interaction.normal), 0.0f);
            switch(interaction.materialType) {
                case MaterialType::Reflective:
                    surfaceColour = material->reflectionColour;
                    brdf = interaction.sample.probability;
                    break;
                case MaterialType::Diffuse:
                    brdf = lambertBrdf.evaluate(interaction.wIn, interaction.wOut, interaction.normal);
                    surfaceColour = material->diffuseColour;
                    break;
                case MaterialType::Specular:
                    brdf = cookTorranceBrdf.evaluateGGXBrdf(interaction.wOut,
                                                            interaction.wIn,
                                                            interaction.normal,
                                                            material->specularRoughness,
                                                            material->specularIndexOfRefraction);
                    brdf = std::isnan(brdf) ? 0 : brdf;
                    surfaceColour = material->specularColour;
                    //cout << "specular brdf " << brdf<< endl;
                    break;
                case MaterialType::Refractive:
                    surfaceColour = material->refractiveColour;
                    brdf = interaction.sample.probability;
                default:
                    break;
            }
            lightAccum = (lightAccum * surfaceColour) * brdf * wInDotN / interaction.sample.probability + interaction.emission;
        }
        return lightAccum;
    }

    void closestIntersection(vector<shared_ptr<SceneObject>>& models, const Ray& ray, RayHit& hitResult, int& closestIndex) {
        int closest = -1;
        RayHit closestHit;
        closestHit.t = MAXFLOAT;
        closestHit.isHit = false;
        RayHit hit;
        SceneObject* obj;
        int modelCount = static_cast<int>(models.size());
        for(int i = 0; i < modelCount; i++) {
            obj = models[i].get();
            hit.isHit = false;
            obj->castRay(ray, hit);
            if(hit.isHit && hit.t > 0 && hit.t < closestHit.t) {
                closestHit = hit;
                closest = i;
            }
        }
        closestIndex = closest;
        hitResult = closestHit;
    }
}