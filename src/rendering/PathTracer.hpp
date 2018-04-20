//
// Created by Zaiyang Li on 13/02/2018.
//

#ifndef RENDERER_PATHTRACER_HPP
#define RENDERER_PATHTRACER_HPP

#include <glm/glm.hpp>
#include <random>
#include "../scene/Ray.hpp"
#include "../scene/Scene.hpp"
#include "../scene/Mesh.hpp"
#include "RayTracerConfig.hpp"
#include "GaussianSampler.hpp"
#include "RenderTarget.hpp"
#include "../brdf/MicroFacetShader.hpp"

namespace McRenderFace {
    using namespace std;
    using namespace glm;
    using namespace Shading;

    constexpr float INVERSE2PI = static_cast<const float>(0.5f / M_PI);
    constexpr float INVERSEPI = static_cast<const float>(1.0f / M_PI);
    struct RaySurfaceInteraction {
        vec3 wIn;
        vec3 wOut;
        vec3 normal;
        RayHit hit{};
        int objectIndex {-1};
        PbrBrdfSampleOutput sample;
        vec3 emission;
        PbrMaterial* material;
    };

    class PathTracer {
    private:
        RayTracerConfig config;
        MicroFacetShader pbrShader;
        PbrLightParameters lightParameters;
        PbrSurfaceParameters surfaceParameters;
        random_device rd;
        mt19937 gen;
        uniform_real_distribution<float> uniform{0.0f, 1.0f};
        std::vector<RaySurfaceInteraction> pathVertices;

    public:
        explicit PathTracer(RayTracerConfig configIn)
                : config{configIn},
                  pbrShader{},
                  lightParameters{},
                  surfaceParameters{}
        {
            gen = mt19937(rd());
            pathVertices.reserve(config.maxRayDepth + 1);
        };

        ~PathTracer(){};

        vec3 traceRay(Scene &scene, const Ray &ray);
        int selectLight(vector <shared_ptr<Light>> lights, const int size, vec3 position);

        float sampleUniform(float min, float max);

        void traceSinglePath(const Ray &ray, Scene &scene, RayHit &hit, RaySurfaceInteraction &path);
        bool sampleRussianRoulette();
        vec3 evaluateLightContributions(std::vector<RaySurfaceInteraction> vertices);
    };

    void closestIntersection(vector<shared_ptr<SceneObject>>& models, const Ray& ray, RayHit& hitResult, int& closestIndex);
}


#endif //RENDERER_PATHTRACER_HPP
