//
// Created by Zaiyang Li on 08/02/2018.
//

#ifndef RENDERER_OBJFILE_HPP
#define RENDERER_OBJFILE_HPP
#include <vector>
#include <glm/vec3.hpp>

namespace McRenderer {


    struct ObjFace {
        unsigned int vertex;
        unsigned int normal;
        unsigned int textureCoord;
    };
    struct ObjFile {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvCoords;
        std::vector<ObjFace> faces;
    };
}


#endif //RENDERER_OBJFILE_HPP
