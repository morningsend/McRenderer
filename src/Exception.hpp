//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_EXCEPTION_HPP
#define RENDERER_EXCEPTION_HPP

#include <string>

namespace McRenderFace {
    using namespace std;
    class Exception {
    private:
        string message;
    public:
        Exception(string messageIn) : message{messageIn} {};
        Exception(Exception& exception) : message(exception.message) {};
    };
}


#endif //RENDERER_EXCEPTION_HPP
