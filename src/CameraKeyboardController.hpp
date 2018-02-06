//
// Created by Zaiyang Li on 06/02/2018.
//

#ifndef RENDERER_CAMERAKEYBOARDCONTROLLER_HPP
#define RENDERER_CAMERAKEYBOARDCONTROLLER_HPP

#include "window/KeyboardEventHandler.hpp"

namespace McRenderer {
    class CameraKeyboardController : public KeyboardEventHandler {
    public:
        ~CameraKeyboardController() override = default;
        void onKeyActive(KeyboardEvent event) override;
    };

}

#endif //RENDERER_CAMERAKEYBOARDCONTROLLER_HPP
