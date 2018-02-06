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
        int closestTriangle = -1;
        Ray ray{camera.position, vec3(0, 0, 0)};
        RayHit hit;
        int closestIndex = 0;
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                float screenX = float(x) / float(width - 1) - 0.5f;
                float screenY = float(y) / float(height - 1) - 0.5f;
                vec4 direction = vec4(screenX, screenY, camera.focalLength,0);
                vec3 worldCoord = camera.toWorldCoordinate(screenX, screenY);

                ray.forward = worldCoord - camera.position;

                closestIntersection(scene.model, ray, hit, closestIndex);

                // ray escaped, set pixel colour to background colour: assume black;
                if(!hit.isHit) {
                    target.setColor(x, y, scene.backgroundColour);
                }
                else {
                    Triangle tri = scene.model[closestIndex];
                    target.setColor(x, y, tri.colour);
                }
            }
//            loop through triangles
//            find intersection using the equation
//            check intersection distance is closer than before
//            set new intersection
//                    return if any intersection exists
        }
    }

    void closestIntersection(const vector<Triangle> &triangles, const Ray &ray, RayHit& hit, int& closestIndex) {
        RayHit closestHit;
        int closest = -1;
        closestHit.t = MAXFLOAT;
        RayHit hitResult;
        int size = static_cast<int>(triangles.size());
        for(int i = 0; i < size; i++) {
            hitResult = castRay(ray, triangles[i]);
            if(hitResult.isHit && hitResult.t < closestHit.t) {
                closestHit = hitResult;
                closest = i;
            }
        }
        closestIndex = closest;
        hit = closestHit;
    }
}
