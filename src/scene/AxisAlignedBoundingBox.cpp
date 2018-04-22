//
// Created by Zaiyang Li on 31/01/2018.
//

#include "AxisAlignedBoundingBox.hpp"

namespace McRenderFace {

    /**
     * * Andrew Woo fast ray AABB box intersection
     * @param ray
     * @param box
     * @return
     */
    RayHit McRenderFace::AxisAlignedBoundingBox::castRay(const McRenderFace::Ray &ray) {
#define MIDDLE 2
#define LESS 1
#define GREATER 2
        RayHit hit;
        bool isInside = true;
        char quadrant[3] = { MIDDLE, MIDDLE, MIDDLE};
        vec3 tMax;
        AxisAlignedBoundingBox& box = *this;
        for(int i = 0; i < 3; i++) {
            if(ray.origin[i] < box.min[i]) {
                isInside = false;
                quadrant[i] = LESS;
                tMax[i] = (box.min[i] - ray.origin[i]) / ray.forward[i];
            }else if(ray.origin[i] > box.max[i]) {
                isInside = false;
                quadrant[i] = GREATER;
                tMax[i] = (box.max[i] - ray.origin[i]) / ray.forward[i];
            }
        }

        if(isInside) {
            hit.position = ray.origin;
            hit.isHit = true;
            return hit;
        }

        int candidatePlane = 0;
        candidatePlane = (tMax[0] > tMax[1]) ? 0 : 1;
        candidatePlane = (tMax[candidatePlane] > tMax[2]) ? candidatePlane : 2;
        hit.t = tMax[candidatePlane];

        vec3 point = ray.at(tMax[candidatePlane]);
        hit.position = point;
        hit.isHit = true;

        if(point[0] < (box.min[0] - EPSILON) || (point[0] > box.max[0] + EPSILON)) {
            hit.isHit = false;
            return hit;
        }

        if(point[1] < (box.min[1] - EPSILON) || (point[1] > box.max[1] + EPSILON)) {
            hit.isHit = false;
            return hit;
        }

        if(point[2] < (box.min[2] - EPSILON) || (point[2] > box.max[2] + EPSILON)) {
            hit.isHit = false;
            return hit;
        }
        return hit;
    }
}
