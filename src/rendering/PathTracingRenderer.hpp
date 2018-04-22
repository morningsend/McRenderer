//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_PATHTRACHINGRENDERER_HPP
#define RENDERER_PATHTRACHINGRENDERER_HPP

#include <cmath>
#include <glm/glm.hpp>
#include <random>
#include "../scene/Ray.hpp"
#include "../scene/SimpleScene.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"
#include "RayTracerConfig.hpp"
#include "GaussianSampler.hpp"

#include "../brdf/lambert/LamberShader.hpp"
#include "../brdf/MicroFacetShader.hpp"
#include "PathTracer.hpp"
#include "UniformSampler.hpp"

#ifndef MAXFLOAT
#define MAXFLOAT 999999999
#endif


namespace McRenderFace {
    using namespace std;
    using namespace glm;
    using namespace Shading;




    class PathTracingRenderer : public Renderer {
    private:
        RayTracerConfig config;
        GaussianSampler gaussianSampler;
        PathTracer pathTracer;
        UniformSampler uniformSampler;
    public:
        PathTracingRenderer(RayTracerConfig configIn):
                pathTracer{configIn},
                config{configIn},
                gaussianSampler{1000} {}
        void render(Scene& scene, RenderTarget& target) override;
        ~PathTracingRenderer(){};
    };
}


#endif //RENDERER_RAYTRACER_HPP
