//
// Created by Zaiyang Li on 13/02/2018.
//

#ifndef RENDERER_PATHTRACER_HPP
#define RENDERER_PATHTRACER_HPP

#include <glm/glm.hpp>
#include "../scene/Ray.hpp"
#include "../scene/Scene.hpp"
#include "../scene/Mesh.hpp"
#include "RayTracerConfig.hpp"
#include "GaussianSampler.hpp"
#include "RenderTarget.hpp"
#include "../shading/pbr/PbrShader.hpp"

namespace McRenderFace {
    using namespace std;
    using namespace glm;
    using namespace Shading;

    constexpr float INVERSE2PI = static_cast<const float>(.25f / M_PI);

    struct RayPath {
        Ray incomingRay;
        RayHit hit;
        vec3 lightContribution;
        int objectIndex;
    };

    class PathTracer {
    private:
        RayTracerConfig config;
        PbrShader pbrShader;
        PbrLightParameters lightParameters;
        PbrSurfaceParameters surfaceParameters;
        PbrMaterial* currentMaterial {nullptr};
        vector<RayPath> indirectRayPaths;
    public:
        explicit PathTracer(RayTracerConfig configIn)
                : config{configIn},
                  pbrShader{},
                  lightParameters{},
                  surfaceParameters{},
                  indirectRayPaths{static_cast<unsigned long>(configIn.maxRayDepth)}
        {};

        ~PathTracer(){};

        vec3 traceRay(Scene &scene, const Ray &ray);
        int selectLight(vector <shared_ptr<Light>> lights, const int size, vec3 position);

        float sampleUniform(float min, float max);

        void traceDirectRay(const Ray &ray, Scene &scene, RayHit& hit, vec3 &colour);
        void traceIndirectRay(Scene& scene, const RayHit& hit, vec3 &indirect);
        RayHit traceShadowRay(vec3 position, Scene& scene, Light& light, float lightDistance);
        vec3 evaluateLightContributions(const PbrSurfaceParameters &surface, Scene &scene);
        float sampleRussianRoulette();
    };

    void closestIntersection(vector<shared_ptr<SceneObject>>& models, const Ray& ray, RayHit& hitResult, int& closestIndex);
}


#endif //RENDERER_PATHTRACER_HPP
