//
// Created by Zaiyang Li on 08/02/2018.
//

#ifndef RENDERER_OBJFILEREADER_HPP
#define RENDERER_OBJFILEREADER_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <fstream>
#include <unordered_map>
#include <ctype.h>

namespace McRenderFace {

    struct ObjFace {
        int vertex[3];
        int normal[3];
        int uvCoord[3];
    };
    struct ObjModel {
        std::string modelName;
        std::string materialName;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvCoords;
        std::vector<ObjFace> faces;

        ObjModel() = default;
        explicit ObjModel(const std::string& name): modelName{name}{}
        explicit ObjModel(const char* name): modelName{name}{}
    };

    class ObjFileReader {
    private:
        std::string filePath;
    public:
        explicit ObjFileReader(const std::string& filePath);
        explicit ObjFileReader(const char* filePath);
        std::unordered_map<std::string, ObjModel*> read();
    };
}


#endif //RENDERER_OBJFILEREADER_HPP
