//
// Created by Zaiyang Li on 27/03/2018.
//
#include <cmath>
#include "HemisphereSampler.hpp"

using namespace glm;
using namespace std;

namespace McRenderFace {

    /**
     * U and V are randomly generated numbers with uniform distribution
     * 0 < u < 1, 0 < v < 1
     * @param u
     * @param v
     * @return
     */
    HemisphereSample HemisphereSampler::sampleUnitHemisphere(float u, float v) {
        vec3 direction;
        direction.z = u;
        float r = sqrt(fmax(0.0f, 1.0f - u * u));
        float phi = PI()* 2 * v;
        direction.x = cos(phi) * r;
        direction.y = sin(phi) * r;
        float pdf = INVERSE2PI();
        return HemisphereSample{direction, pdf};
    }

    HemisphereSample HemisphereSampler::sampleCosineWeightedUnitHemisphere(float u, float v) {
        vec2 pointOnDisk = sampleConcentricDisk(u, v);
        float r2 = pointOnDisk.x * pointOnDisk.x + pointOnDisk.y * pointOnDisk.y;
        float z = sqrt(1 - r2);
        return HemisphereSample{ vec3(pointOnDisk, z), z * INVERSEPI()};
    }

    glm::vec2 HemisphereSampler::sampleUniformDisk(float rSquared, float theta) {
        return vec2();
    }

    /**
     * u and v are floating point numbers between 0 and 1
     * @param u
     * @param v
     * @return
     */
    glm::vec2 HemisphereSampler::sampleConcentricDisk(float u, float v) {
        float r = 0, theta = 0;
        u = 2.f * u - 1.0f;
        v = 2.f * v - 1.0f;
        if(u == 0.0f && v == 0.0f){
            return vec2(0,0);
        }
        if(abs(u) > abs(v)) {
            r = u;
            theta = PI() * 0.25f * v / u;
        } else {
            r = v;
            theta = PI() * 0.5f - PI()*0.25f * u / v;
        }

        return vec2(cos(theta), sin(theta)) * r;
    }

    constexpr float HemisphereSampler::INVERSEPI() const {
        return static_cast<float>(1 / M_PI);
    }
}