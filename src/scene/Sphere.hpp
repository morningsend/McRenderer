//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_SPHERE_HPP
#define RENDERER_SPHERE_HPP

#include <glm/glm.hpp>
#include "SceneObject.hpp"

namespace McRenderFace {
    using namespace glm;
    struct Sphere : public SceneObject{
        float radius;
        vec3 origin;
        Sphere(float radiusIn, vec3 originIn): radius{radiusIn}, origin{originIn}{ }
        ~Sphere() override = default;

        // SceneObject virtual methods implementation
        RayHit castRay(const Ray& ray) override ;
        void computeBoundingBox() override ;
        void applyTransform() override ;
    };

}


#endif //RENDERER_SPHERE_HPP
