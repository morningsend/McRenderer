//
// Created by Zaiyang Li on 20/04/2018.
//

#ifndef RENDERER_UNIFORMSTRATIFIEDSAMPLER_HPP
#define RENDERER_UNIFORMSTRATIFIEDSAMPLER_HPP

#include <vector>
#include <glm/glm.hpp>
#include <random>
namespace McRenderFace {
    using namespace glm;
    using namespace std;
    class UniformSampler {
    private:
        uniform_real_distribution<float> dist;
        default_random_engine engine;
    public:

        inline vec2 sample() {
            return vec2(dist(engine), dist(engine));
        }
    };
}


#endif //RENDERER_UNIFORMSTRATIFIEDSAMPLER_HPP
