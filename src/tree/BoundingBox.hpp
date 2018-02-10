//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_BOUNDINGBOX_HPP
#define RENDERER_BOUNDINGBOX_HPP

#include <glm/glm.hpp>
namespace McRenderFace {
    struct BoundingBox {
        glm::vec3 min{0,0,0};
        glm::vec3 max{1,1,1};
    };
}


#endif //RENDERER_BOUNDINGBOX_HPP
