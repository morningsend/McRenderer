//
// Created by Zaiyang Li on 05/02/2018.
//

#ifndef RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP
#define RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP
#include <vector>
#include <future>
#include <glm/glm.hpp>
#include "../window/Window.hpp"
#include "RenderTarget.hpp"
#include "Renderer.hpp"
#include "../window/DrawingTask.hpp"

namespace McRenderFace {
    using namespace std;
    using namespace glm;
    class RenderTargetDrawingTask : public DrawingTask {
    private:
        RenderTarget* target;
        std::thread* renderingThread;
        std::promise<void> cancellationSignal;
    public:
        RenderTargetDrawingTask(RenderTarget* target, std::thread* thread, std::promise<void> signal)
                : target{target},
                  renderingThread{thread},
                  cancellationSignal(std::move(signal))
        {
        }
        void cancel() override { cancellationSignal.set_value(); }
        void update(screen* screenBuffer) override {
            cout << "updating scene" << endl;
            const int height = target->getHeight();
            const int width = target->getWidth();
            const vec3 gammaCorrection = vec3(1.0f / 2.2f);
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    //vec3 gammaCorrected = glm::pow(target->getColor(x, y), gammaCorrection);
                    PutPixelSDL(screenBuffer, x, y, target->getColor(x, y));
                };
            };
        }
    };
    /**
     * Writes the content of render target to screen buffer to be shown in SDL window every time draw
     * method is called.
     */
    class RenderTargetDrawFunction : public DrawFunction{
    private:
        Scene* scene;
        RenderTarget* renderTarget;
        Renderer* renderer;
        bool gammaCorrect {true};
        vec3 gamma{1.0f/2.2f};
        vector<DrawingTask> tasks;
    public:
        RenderTargetDrawFunction(Scene* sceneIn, Renderer* rendererIn, RenderTarget* renderTargetIn)
                : scene{sceneIn},
                  renderer{rendererIn},
                  renderTarget{renderTargetIn}
        {
        }
        /**
         * Writes the content of render target to screen.
         * Will throw exception if render target and screen have different width and height.
         * @param screen
         * @param deltaTime
         */
        void draw(screen* screen, Uint32 deltaTime) override;
        DrawingTask* drawAsync(screen* screen, Uint32 elapsedTime) override {
            int width = renderTarget->getWidth();
            int height = renderTarget->getHeight();
            if (width != screen->width && height != screen->height) {
                throw runtime_error("screen must be same size as render target");
            }
            std::promise<void> cancellationSignal;
            std::thread *t = new std::thread([&](){
                renderer->render(*scene, *renderTarget);
            });
            return new RenderTargetDrawingTask(renderTarget, t, std::move(cancellationSignal));
        }
    };
}


#endif //RENDERER_RENDERTARGETDRAWINGFUNCTION_HPP
