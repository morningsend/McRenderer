//
// Created by Zaiyang Li on 08/02/2018.
//

#ifndef RENDERER_OBJFILEREADER_HPP
#define RENDERER_OBJFILEREADER_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <fstream>
namespace McRenderFace {

    struct ObjFace {
        unsigned int vertex;
        unsigned int normal;
        unsigned int textureCoord;
    };
    struct ObjFile {
        std::string modelName;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvCoords;
        std::vector<ObjFace> faces;
    };

    class ObjFileReader {
    private:
        std::string filePath;
    public:
        explicit ObjFileReader(const std::string& filePath);
        explicit ObjFileReader(const char* filePath);
        ObjFile read();
    };
}


#endif //RENDERER_OBJFILEREADER_HPP
