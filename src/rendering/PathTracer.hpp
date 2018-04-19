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

    constexpr float INVERSE2PI = static_cast<const float>(.25f / M_PI);

    struct RayPath {
        Ray incomingRay { vec3(0), vec3(0)};
        RayHit hit{};
        int objectIndex {-1};
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
    public:
        explicit PathTracer(RayTracerConfig configIn)
                : config{configIn},
                  pbrShader{},
                  lightParameters{},
                  surfaceParameters{}
        {
            gen = mt19937(rd());
        };

        ~PathTracer(){};

        vec3 traceRay(Scene &scene, const Ray &ray);
        int selectLight(vector <shared_ptr<Light>> lights, const int size, vec3 position);

        float sampleUniform(float min, float max);

        void traceSinglePath(const Ray &ray, Scene &scene, RayHit &hit, RayPath &path);
        RayHit traceShadowRay(vec3 position, Scene& scene, Light& light);
        vec3 evaluateLightContributions(const PbrSurfaceParameters &surface, Scene &scene);
        bool sampleRussianRoulette();
    };

    void closestIntersection(vector<shared_ptr<SceneObject>>& models, const Ray& ray, RayHit& hitResult, int& closestIndex);
}


#endif //RENDERER_PATHTRACER_HPP
