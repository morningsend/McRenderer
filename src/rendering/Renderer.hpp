//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include "RenderTarget.hpp"

#include "../scene/SimpleScene.hpp"
#include "../scene/Scene.hpp"

namespace McRenderFace {
    class Renderer {
    public:
        virtual void render(const SimpleScene& scene, RenderTarget& target) {};
        virtual void render(const Scene& scene, RenderTarget& target) { }
        virtual ~Renderer() = default;;
    };
}


#endif //RENDERER_RENDERER_HPP
