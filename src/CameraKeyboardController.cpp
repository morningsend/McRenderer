//
// Created by Zaiyang Li on 06/02/2018.
//

#include <iostream>
#include "CameraKeyboardController.hpp"
namespace McRenderFace {


    void CameraKeyboardController::onKeyActive(KeyboardEvent event) {
        switch(event.key) {
            case SDL_SCANCODE_UP:
                camera -> position.y += 0.1f;
            std::cout << camera->position.y << std::endl;
                break;
            case SDL_SCANCODE_DOWN:
                camera -> position.y -= 0.1f;
                break;
            case SDL_SCANCODE_LEFT:
                camera -> position.x -= 0.1f;
                break;
            case SDL_SCANCODE_RIGHT:
                camera -> position.x += 0.1f;
                break;
            case SDL_SCANCODE_A:
                camera->rotateY(5.0f);
                break;
            case SDL_SCANCODE_S:
                camera->rotateY(-5.0f);
            default:
                break;
        }
        std::cout << "camera at position ("
                  << camera->position.x << ','
                  << camera->position.y << ','
                  << camera->position.z << ')'
                  << std::endl;
    }
}