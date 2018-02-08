//
// Created by Zaiyang Li on 08/02/2018.
//

#ifndef RENDERER_OBJFILEREADER_HPP
#define RENDERER_OBJFILEREADER_HPP

#include <string>
#include "ObjFile.hpp"

namespace McRenderer {

    class ObjFileReader {
    public:
        ObjFileReader(std::string filePath);
        ObjFileReader(const char* filePath);
        ObjFile read();
    };
}


#endif //RENDERER_OBJFILEREADER_HPP
