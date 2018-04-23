//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_BOUNDINGBOX_HPP
#define RENDERER_BOUNDINGBOX_HPP

#include <glm/glm.hpp>
#include "RayIntersecting.hpp"

namespace McRenderFace {
    /**
     * Axis Aligned Bounding Box
     */
    struct AxisAlignedBoundingBox : public RayIntersecting{
        glm::vec3 min{0,0,0};
        glm::vec3 max{0,0,0};

        AxisAlignedBoundingBox() = default;
        AxisAlignedBoundingBox(glm::vec3 minIn, glm::vec3 maxIn): min{minIn}, max{maxIn} { }
        AxisAlignedBoundingBox(const AxisAlignedBoundingBox& box) = default;

        void castRay(const Ray& ray, RayHit& hit) override;
        inline float surfaceArea() {
            vec3 deltas = min - max;
            vec3 components(deltas.y, deltas.z, deltas.x);
            return glm::dot(deltas, components) * 2.0f;
        }
    };
}

#endif //RENDERER_BOUNDINGBOX_HPP
