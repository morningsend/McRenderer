//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RAYTRACER_HPP
#define RENDERER_RAYTRACER_HPP

#include <cmath>
#include <glm/glm.hpp>
#include <random>
#include "../scene/SimpleScene.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"
#include "../scene/Ray.hpp"
#include "RayTracerConfig.hpp"

#include "../shading/lambert/LamberShader.hpp"
#include "GaussianSampler.hpp"

#ifndef MAXFLOAT
#define MAXFLOAT 999999999
#endif


namespace McRenderFace {
    using namespace std;
    using namespace glm;
    using namespace Shading;

    const float INVERSE2PI = static_cast<const float>(.25f / M_PI);
    class PathTracer : public Renderer {
    private:
        RayTracerConfig config;
        vector<vec3> cameraRaySamples;
        GaussianSampler sampler;

        void generateRayDirectionsAtPixel(int width,
                                          int height,
                                          int x,
                                          int y,
                                          const Camera& camera,
                                          vector<vec3> rayDirecitons);
    public:
        PathTracer(RayTracerConfig configIn): config{configIn}, cameraRaySamples(1 << configIn.samplingLevel), sampler{1000}{
        };
        void render(Scene& scene, RenderTarget& target) override;
        ~PathTracer(){};
        bool traceShadow(Scene& scene, float lightDistance, const Ray& ray);
    };
    void closestIntersection(vector<shared_ptr<Mesh>> models, const Ray& ray, RayHit& hitResult, int& closestIndex);
}


#endif //RENDERER_RAYTRACER_HPP
