//
// Created by Zaiyang Li on 05/02/2018.
//

#ifndef RENDERER_KEYBOARDEVENTHANDLER_HPP
#define RENDERER_KEYBOARDEVENTHANDLER_HPP

#include "KeyboardEvent.hpp"

namespace McRenderFace {
    class KeyboardEventHandler {
    public:
        virtual void onKeyActive(KeyboardEvent event) = 0;
        virtual ~KeyboardEventHandler(){};
    };
}


#endif //RENDERER_KEYBOARDEVENTHANDLER_HPP
