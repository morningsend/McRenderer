//
// Created by Zaiyang Li on 13/02/2018.
//

#ifndef RENDERER_GAUSSIANSAMPLER_HPP
#define RENDERER_GAUSSIANSAMPLER_HPP

#include <random>
#include <glm/glm.hpp>
namespace McRenderFace {
    using namespace std;
    using namespace glm;
    // z = (x - u) / sigma
    class GaussianSampler {
    private:
        mt19937 generator;
        normal_distribution<float> dist{0.0f, 1.0f};
    public:
        GaussianSampler(unsigned int seed): generator{seed} {}
        void sample(vec2 &v, vec2 mean, vec2 sigma);
        void sample(vec3 &v, vec3 mean, vec3 sigma);
    };
}


#endif //RENDERER_GAUSSIANSAMPLER_HPP
