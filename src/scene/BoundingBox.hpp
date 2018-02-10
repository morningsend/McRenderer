//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_BOUNDINGBOX_HPP
#define RENDERER_BOUNDINGBOX_HPP

#include <glm/glm.hpp>
namespace McRenderFace {
    /**
     * Axis Aligned Bounding Box
     */
    struct BoundingBox {
        glm::vec3 min{0,0,0};
        glm::vec3 max{0,0,0};

        BoundingBox() = default;
        BoundingBox(glm::vec3 minIn, glm::vec3 maxIn): min{minIn}, max{maxIn} { }
    };
}

#endif //RENDERER_BOUNDINGBOX_HPP
