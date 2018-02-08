//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RAYTRACER_HPP
#define RENDERER_RAYTRACER_HPP


#include "../scene/Scene.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"
#include "../scene/Ray.hpp"

namespace McRenderer {
    const float INVERSE2PI = static_cast<const float>(.25f / M_PI);
    class RayTracer : public Renderer {
    private:
        int threads;

    public:
        RayTracer(int threadsIn): threads{threadsIn} { };
        void render(const Scene& scene, RenderTarget& target);
        ~RayTracer(){};
        bool traceShadow(const Scene &scene, float lightDistance, const Ray &ray);
    };

    void closestIntersection(const vector<Triangle> &triangles,
                             const Ray &ray,
                             RayHit& hit,
                             int& closestIndex);
}


#endif //RENDERER_RAYTRACER_HPP
