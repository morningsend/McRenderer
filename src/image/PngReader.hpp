//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_PNGREADER_HPP
#define RENDERER_PNGREADER_HPP

#include <string>
#include "Image.hpp"

namespace McRenderFace {
    using namespace std;

    class PngReader {
    public:
        Image read(const string& filePath);
    };
}


#endif //RENDERER_PNGREADER_HPP
