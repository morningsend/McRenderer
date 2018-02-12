//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_MATERIAL_HPP
#define RENDERER_MATERIAL_HPP

namespace McRenderFace {
    namespace Shading {
        struct Material {
            int materialId {0};
            virtual ~Material() = default;
        };
    }
}


#endif //RENDERER_MATERIAL_HPP
