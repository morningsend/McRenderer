//
// Created by Zaiyang Li on 27/03/2018.
//

#ifndef RENDERER_HEMISPHERESAMPLER_HPP
#define RENDERER_HEMISPHERESAMPLER_HPP

#include <random>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

namespace McRenderFace {

    struct HemisphereSample {
        glm::vec3 direction{0};
        float pdf{1};

        HemisphereSample() {

        }
        HemisphereSample(glm::vec3 directionIn, float pdfIn) : direction{directionIn}, pdf{pdfIn}{ }
    };
    class HemisphereSampler {
    private:
        std::default_random_engine engine;
        std::uniform_real_distribution<float> uniform{0, 1};
    public:
        constexpr float INVERSE2PI() const {
            return static_cast<float>(0.5 / M_PI);
        }
        constexpr float PI() const{
            return static_cast<float>(M_PI);
        }
        constexpr float INVERSEPI() const ;
        HemisphereSample sampleUnitHemisphere(float u, float v);
        HemisphereSample sampleCosineWeightedUnitHemisphere(float u, float v);
        glm::vec2 sampleUniformDisk(float rSquared, float theta);
        glm::vec2 sampleConcentricDisk(float u, float v);

        HemisphereSample sampleUnitHemisphere() {
            return sampleUnitHemisphere(uniform(engine), uniform(engine));
        }
        HemisphereSample sampleCosineWeightedUnitHemisphere() {
            return sampleCosineWeightedUnitHemisphere(uniform(engine), uniform(engine));
        }
        glm::vec2 sampleUniformDisk() {
            return sampleUniformDisk(uniform(engine), uniform(engine));
        }
        glm::vec2 sampleConcentricDisk(){
            return sampleConcentricDisk(uniform(engine), uniform(engine));
        }

        static glm::vec3 transformHemispherePointToNormal(glm::vec3 normal, glm::vec3 hemispherePoint) {
            glm::vec4 rotatedVec = glm::orientation(glm::vec3(0,0,1), normal) * glm::vec4(hemispherePoint, 0);
            return glm::vec3(rotatedVec);
        }
    };
}


#endif //RENDERER_HEMISPHERESAMPLER_HPP
