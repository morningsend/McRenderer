//
// Created by Zaiyang Li on 13/02/2018.
//

#ifndef RENDERER_SCENEOBJECT_HPP
#define RENDERER_SCENEOBJECT_HPP

#include "AxisAlignedBoundingBox.hpp"
#include "Transform.hpp"
#include "RayIntersecting.hpp"

namespace McRenderFace {

    /**
     * Abstract base class for all renderable scene objects
     */
    struct SceneObject : public RayIntersecting {
        int objectId {0};
        Transform transform {};
        AxisAlignedBoundingBox boundingBox {};
        int materialId {0};

        virtual void computeBoundingBox() = 0;
        virtual void applyTransform() = 0;
        ~SceneObject() override = default;
    };
}


#endif //RENDERER_SCENEOBJECT_HPP
