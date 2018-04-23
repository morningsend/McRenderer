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
        void castRay(const Ray& ray, RayHit & rayHit) override ;
        void computeBoundingBox() override ;
        void applyTransform() override ;

        inline float surfaceArea() {
            return 4.0f * radius * radius * (float) M_PI;
        }
    };

}


#endif //RENDERER_SPHERE_HPP
