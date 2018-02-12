//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RAYTRACER_HPP
#define RENDERER_RAYTRACER_HPP


#include "../scene/SimpleScene.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"
#include "../scene/Ray.hpp"
#include "RayTracerConfig.hpp"

namespace McRenderFace {
    const float INVERSE2PI = static_cast<const float>(.25f / M_PI);
    class RayTracer : public Renderer {
    private:
        RayTracerConfig config;
    public:
        RayTracer(RayTracerConfig configIn): config{configIn}{ };
        void render(const SimpleScene& scene, RenderTarget& target) override;
        void render(const Scene& scene, RenderTarget& target) override;
        ~RayTracer(){};
        bool traceShadow(const SimpleScene &scene, float lightDistance, const Ray &ray);
    };

    void closestIntersection(const vector<Triangle> &triangles,
                             const Ray &ray,
                             RayHit& hit,
                             int& closestIndex);
}


#endif //RENDERER_RAYTRACER_HPP
