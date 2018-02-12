//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RAYTRACER_HPP
#define RENDERER_RAYTRACER_HPP

#include <cmath>
#include "../scene/SimpleScene.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"
#include "../scene/Ray.hpp"
#include "RayTracerConfig.hpp"

#include "../shading/lambert/LamberShader.hpp"

#ifndef MAXFLOAT
#define MAXFLOAT 999999999
#endif

namespace McRenderFace {
    using namespace std;
    using namespace glm;
    using namespace Shading;

    const float INVERSE2PI = static_cast<const float>(.25f / M_PI);
    class RayTracer : public Renderer {
    private:
        RayTracerConfig config;
    public:
        RayTracer(RayTracerConfig configIn): config{configIn}{ };
        void render(SimpleScene& scene, RenderTarget& target) override;
        void render(Scene& scene, RenderTarget& target) override;
        ~RayTracer(){};
        bool traceShadow(SimpleScene &scene, float lightDistance, const Ray &ray);
        bool traceShadow(Scene& scene, float lightDistance, const Ray& ray);
    };

    void closestIntersection(vector<Triangle> &triangles, const Ray &ray, RayHit& hit, int& closestIndex);
    void closestIntersection(vector<shared_ptr<Mesh>> models, const Ray& ray, RayHit& hit, int& closestIndex);
}


#endif //RENDERER_RAYTRACER_HPP
