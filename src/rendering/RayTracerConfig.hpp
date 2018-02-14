//
// Created by Zaiyang Li on 09/02/2018.
//

#ifndef RENDERER_RAYTRACERCONFIG_HPP
#define RENDERER_RAYTRACERCONFIG_HPP

#include <utility>

namespace McRenderFace {
    struct RayTracerConfig {
        int threadCount{1};
        bool renderShadows{true};
        bool softShadow{true};
        float shadowRayBias{0.001};
        float secondaryRayBias{0.001};
        int maxRayDepth{2};
        int samplingLevel{0}; // we sample (2^sampling level) many rays per pixel.
        // allow path to continue x% of time, when probabilty > x, kill path.
        float killProbabilityThreshold{0.74};
    };
    /**
     * Fluent Builder API
     */
    class RayTracerConfigBuilder {
    private:
        RayTracerConfig config;
    public:
        RayTracerConfigBuilder() = default;

        RayTracerConfigBuilder& useMultithreading(int threadsCount) {
            config.threadCount = threadsCount > 1 ? threadsCount : 1;
            return *this;
        }
        RayTracerConfigBuilder& samplingLevel(int level){
            config.samplingLevel = level >= 0 ? level : 0;
            return *this;
        }
        RayTracerConfigBuilder& maxRayDepth(int depth) {
            config.maxRayDepth = depth > 0 ? depth : 1;
            return *this;
        }
        RayTracerConfigBuilder& traceShadowsWithBias(float bias) {
            config.shadowRayBias = bias;
            return *this;
        }
        RayTracerConfigBuilder& softShadow(bool soft) {
            config.softShadow = soft;
            return *this;
        }
        RayTracerConfigBuilder& secondaryBias(float bias) {
            config.secondaryRayBias = bias;
            return *this;
        }
        RayTracerConfig build() {
            return config;
        }
    };
}


#endif //RENDERER_RAYTRACERCONFIG_HPP
