//
// Created by Zaiyang Li on 20/04/2018.
//

#ifndef RENDERER_UNIFORMSTRATIFIEDSAMPLER_HPP
#define RENDERER_UNIFORMSTRATIFIEDSAMPLER_HPP

#include <vector>
#include <glm/glm.hpp>

namespace McRenderFace {
    using namespace glm;
    class UniformStratifiedSampler {
    private:
        int samplinglevel;
    public:
        UniformStratifiedSampler(int level) : samplinglevel{level} {}

        void sample(int samplingLevel, float x, float y, std::vector<vec2> samples);
    };
}


#endif //RENDERER_UNIFORMSTRATIFIEDSAMPLER_HPP
