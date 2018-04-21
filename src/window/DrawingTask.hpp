//
// Created by Zaiyang Li on 21/04/2018.
//

#ifndef RENDERER_DRAWINGTASK_HPP
#define RENDERER_DRAWINGTASK_HPP

#include "../SDLauxiliary.hpp"
#include <thread>

namespace McRenderFace {
    class DrawingTask {
    public:
        virtual bool isDone() { return true; }
        virtual void cancel() {};
        virtual void waitSynchronously() {};
        virtual void update(screen* screen) {};
    };
}


#endif //RENDERER_DRAWINGTASK_HPP
