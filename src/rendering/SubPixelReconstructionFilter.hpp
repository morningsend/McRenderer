//
// Created by Zaiyang Li on 23/04/2018.
//

#ifndef RENDERER_SUBPIXELFILTER_HPP
#define RENDERER_SUBPIXELFILTER_HPP
#include <iostream>
#include <glm/glm.hpp>

namespace McRenderFace {
    using namespace glm;
    using namespace std;
    /**
     * Base class for reconstruction filters.
     */
    class SubPixelReconstructionFilter {
    protected:
        vec2 radius;
        vec2 inverseRadius;
    public:
        SubPixelReconstructionFilter(vec2 radius) : radius{radius}, inverseRadius{1.0f/radius}{}

        /**
         * input a sample's position relative to pixel center, returns weight.
         * @param point
         * @return
         */
        inline float evaluate(vec2 point) { return 0; }
    };

    class GaussianFilter : public SubPixelReconstructionFilter{
    private:
        float alpha {0.0f};
        float expx;
        float expy;
    public:
        GaussianFilter(vec2 radius, float alpha) : SubPixelReconstructionFilter(radius), alpha{alpha} {
            vec2 radius2 = radius * radius;
            expx = std::exp(-alpha * radius2.x);
            expy = std::exp(-alpha * radius2.y);
        }

        inline float evaluate(vec2 point) {
            vec2 point2 = point * point;
            float xFilter = std::max<float>(0, std::exp(-point2.x * alpha) - expx);
            float yFilter = std::max<float>(0, std::exp(-point2.y * alpha) - expy);
            return xFilter * yFilter;
        }
    };

    class MitchellNetravaliFilter : public SubPixelReconstructionFilter {
    private:
        float b = 0;
        float c = 0;
    public:
        MitchellNetravaliFilter(vec2 radius, float b, float c)
                : SubPixelReconstructionFilter(radius), b{b}, c{c} {

        }

        float evaluate1D(float v) {
            constexpr float denom = 1.0f / 6.0f;
            // map v to interval [-2, 2] and apply mitchell-netravali cubic formula.
            v = std::abs(2 * v);
            float v2 = v * v;
            float result;
            if(v < 1) {
                result = ((12 - 9 * b - 6 * c) * v2 * v + (-18.0f + 12 * b + 6 * c) * v2 +  (6 - 2 *b));
            } else {
                result = (-b - 6*c) * v2 * v + (6 * b + 30*c) * v2 + (-12 * b - 48 * c) + (8 * b + 24 * c);
            }
            return result;
        }

        inline float evaluate(vec2 point) {
            vec2 params = point * inverseRadius;
            return evaluate1D(params.x) * evaluate1D(params.y);
        }
    };
}


#endif //RENDERER_SUBPIXELFILTER_HPP
