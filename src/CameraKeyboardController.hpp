//
// Created by Zaiyang Li on 06/02/2018.
//

#ifndef RENDERER_CAMERAKEYBOARDCONTROLLER_HPP
#define RENDERER_CAMERAKEYBOARDCONTROLLER_HPP

#include "window/KeyboardEventHandler.hpp"
#include "scene/Camera.hpp"

namespace McRenderFace {
    class CameraKeyboardController : public KeyboardEventHandler {
    private:
        Camera* camera;
    public:
        explicit CameraKeyboardController(Camera* cameraIn): camera{cameraIn} { }
        ~CameraKeyboardController() override = default;
        void onKeyActive(KeyboardEvent event) override;
    };

}

#endif //RENDERER_CAMERAKEYBOARDCONTROLLER_HPP
