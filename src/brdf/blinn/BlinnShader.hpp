//
// Created by Zaiyang Li on 10/02/2018.
//

#ifndef RENDERER_BLINNMATERIAL_HPP
#define RENDERER_BLINNMATERIAL_HPP

#include "../phong/PhongShader.hpp"

namespace McRenderFace {
    namespace Shading {
        struct BlinnMaterial : PhongMaterial {

        };
        struct BlinnParameters : PhongParameters{

        };

        struct BlinnShader {
            inline vec3 compute(const BlinnMaterial& material, const BlinnParameters& parameters);
        };
    }
}


#endif //RENDERER_BLINNMATERIAL_HPP
