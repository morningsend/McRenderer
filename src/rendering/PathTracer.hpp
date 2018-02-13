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

    const float INVERSE2PI = static_cast<const float>(.25f / M_PI);

    struct LightPath {
        Ray incomingRay;
        int meshId;
        vec3 pointOfIntersection;
        vec3 surfaceNormal;
        float surfaceColour;
        float lightDistance;
    };
    class PathTracer {
    private:
        RayTracerConfig config;
        PbrShader pbrShader;
        PbrLightParameters lightParameters;
        PbrSurfaceParameters surfaceParameters;

    public:
        explicit PathTracer(RayTracerConfig configIn)
                : config{configIn}, pbrShader{}, lightParameters{}, surfaceParameters{}
        {};

        ~PathTracer(){};

        vec3 traceRay(Scene &scene, const Ray &ray);
    };

    void closestIntersection(vector<shared_ptr<Mesh>>& models, const Ray& ray, RayHit& hitResult, int& closestIndex);
}


#endif //RENDERER_PATHTRACER_HPP
