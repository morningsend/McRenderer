//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_UVSAMPLER3D_HPP
#define RENDERER_UVSAMPLER3D_HPP
#include <glm/glm.hpp>

namespace McRenderFace{
    using namespace glm;
    class UvSampler3D {
    public:
        virtual ~UvSampler3D();
        virtual vec3 sample(float u, float v) const = 0;
        virtual vec3 sample(vec2 uv) const = 0;
    };

}



#endif //RENDERER_UVSAMPLER3D_HPP
