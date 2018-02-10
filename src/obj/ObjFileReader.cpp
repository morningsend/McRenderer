//
// Created by Zaiyang Li on 08/02/2018.
//

#include "ObjFileReader.hpp"

#include <utility>


namespace McRenderFace {
    using namespace std;

    ObjFileReader::ObjFileReader(const std::string& filePath): filePath{filePath} {

    }

    ObjFileReader::ObjFileReader(const char *filePath):filePath{filePath} {

    }

    ObjFile ObjFileReader::read() {
        char buffer[128];
        ObjFile obj;
        ifstream inputFile(filePath, ios::in);
        if(!inputFile) {
            throw runtime_error("file not found: " +filePath);
        }
        inputFile.getline(buffer, 128);
        inputFile.close();
        return obj;
    }
}
