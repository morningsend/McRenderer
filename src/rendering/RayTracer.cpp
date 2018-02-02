//
// Created by Zaiyang Li on 31/01/2018.
//

#include "RayTracer.hpp"
#include "../scene/Ray.hpp"


namespace McRenderer {

    void RayTracer::render(const McRenderer::Scene &scene, McRenderer::RenderTarget &target) {
        // convert from screen space coordinate to camera coordinate.
        const int width = target.getWidth();
        const int height = target.getHeight();

        float focalLength = scene.camera.focalLength;
        const Camera& camera = scene.camera;
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                float screenX = float(x) / float(width - 1) - 0.5f;
                float screenY = float(y) / float(height - 1) - 0.5f;
                vec4 direction = vec4(screenX, screenY, camera.focalLength,0);
                vec3 worldCoord = camera.toWorldCoordinate(screenX, screenY);

                Ray ray{camera.position, worldCoord};
            }
//            loop through triangles
//            find intersection using the equation
//            check intersection distance is closer than before
//            set new intersection
//                    return if any intersection exists
        }
    }
}
