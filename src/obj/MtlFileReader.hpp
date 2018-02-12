//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_MTLFILEREADER_HPP
#define RENDERER_MTLFILEREADER_HPP

#include <glm/glm.hpp>

namespace McRenderFace {
    using namespace glm;

    enum IlluminationMode {

    };

    struct MtlMaterial {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float specularExponent;
        float transparency;
        float transmission;
        IlluminationMode illuminationMode;

    };
    class MtlFileReader {

    };
}


#endif //RENDERER_MTLFILEREADER_HPP
