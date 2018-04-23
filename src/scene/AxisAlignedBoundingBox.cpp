//
// Created by Zaiyang Li on 31/01/2018.
//

#include <algorithm>
#include "AxisAlignedBoundingBox.hpp"

namespace McRenderFace {

    /**
     * * Andrew Woo fast ray AABB box intersection
     * @param ray
     * @param box
     * @return
     */
    void McRenderFace::AxisAlignedBoundingBox::castRay(const McRenderFace::Ray &ray, RayHit& hit) {
        vec3 rayDirInv = 1.0f / ray.forward;
        float t1 = (min[0] - ray.origin[0]) * rayDirInv[0];
        float t2 = (max[0] - ray.origin[0]) * rayDirInv[0];

        float tMin = std::min(t1, t2);
        float tMax = std::max(t1, t2);

        for(int i = 1; i < 3; i++) {
            t1 = (min[i] - ray.origin[i]) * rayDirInv[i];
            t2 = (max[i] - ray.origin[i]) * rayDirInv[i];

            tMin = std::max(tMin, std::min(t1, t2));
            tMax = std::min(tMax, std::max(t1, t2));
        }
        hit.isHit = tMax >= std::max(tMin, 0.0f);
    }
}
