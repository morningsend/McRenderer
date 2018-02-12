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
        float shadowBias{0.001};
        int maxRayDepth{2};
        int maxSamplingLevel{0}; // 2^sampling level
        int minSamplingLevel{-2};


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
        RayTracerConfigBuilder& minSamplingLevel(int level){
            config.minSamplingLevel = level;
            return *this;
        }
        RayTracerConfigBuilder& maxSamplingLevel(int level){
            config.maxSamplingLevel = level;
            return *this;
        }
        RayTracerConfigBuilder& maxRayDepth(int depth) {
            config.maxRayDepth = depth;
            return *this;
        }
        RayTracerConfigBuilder& traceShadowsWithBias(float bias) {
            config.shadowBias = bias;
            return *this;
        }
        RayTracerConfigBuilder& softShadow(bool soft) {
            config.softShadow = soft;
            return *this;
        }
        RayTracerConfig build() {
            return config;
        }
    };
}


#endif //RENDERER_RAYTRACERCONFIG_HPP
