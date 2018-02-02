//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RAYTRACER_HPP
#define RENDERER_RAYTRACER_HPP


#include "../scene/Scene.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"

namespace McRenderer {
    class RayTracer : public Renderer{
    private:
        int threads;

    public:
        RayTracer(int threadsIn): threads{threadsIn} { };
        void render(const Scene& scene, RenderTarget& target);
        ~RayTracer(){};
    };
}


#endif //RENDERER_RAYTRACER_HPP
