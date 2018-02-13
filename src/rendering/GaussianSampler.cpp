//
// Created by Zaiyang Li on 13/02/2018.
//

#include "GaussianSampler.hpp"
namespace McRenderFace {

    void GaussianSampler::sample(vec2 &v, vec2 mean, vec2 sigma) {
        v.x = dist(generator);
        v.y = dist(generator);
        v = v * sigma + mean;
    }

    void GaussianSampler::sample(vec3& v, vec3 mean, vec3 sigma) {
        v.x = dist(generator);
        v.y = dist(generator);
        v.z = dist(generator);

        v = v * sigma + mean;
    }
}
