//
// Created by Zaiyang Li on 31/01/2018.
//
#include <cmath>
#include "RayTracer.hpp"
#include "../scene/Ray.hpp"


namespace McRenderFace {

    void RayTracer::render(const McRenderFace::Scene &scene, McRenderFace::RenderTarget &target) {
        // convert from screen space coordinate to camera coordinate.

        const int width = target.getWidth();
        const int height = target.getHeight();

        float focalLength = scene.camera.focalLength;
        const Camera& camera = scene.camera;
        Light light = scene.lights[0];
        Ray ray{camera.position, vec3(0, 0, 0)};
        RayHit hit;
        int closestIndex = 0;
        float fovLength = tan(0.5f * camera.fieldOfViewDegrees / 180.0f * (float) M_PI);
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                float screenX = (float(x) / float(width - 1) - 0.5f) * 2.0f * fovLength;
                float screenY = -(float(y) / float(height - 1) - 0.5f) * 2.0f * fovLength;
                vec3 direction = vec3(screenX, screenY, camera.focalLength);
                vec3 worldCoord = camera.toWorldCoordinate(screenX, screenY);

                ray.forward = glm::normalize(worldCoord - camera.position);

                closestIntersection(scene.model, ray, hit, closestIndex);

                // ray escaped, set pixel colour to background colour: assume black;
                if(!hit.isHit) {
                    target.setColor(x, y, scene.backgroundColour);
                }
                else {
                    Triangle tri = scene.model[closestIndex];
                    target.setColor(x, y, tri.colour);
                    vec3 toLight = light.position - hit.position;
                    float distance2 = glm::dot(toLight, toLight);
                    float distance = sqrt(distance2);
                    toLight /= distance;
                    //ray position needs a bias to avoid shadow acne.
                    //https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows
                    Ray shadowRay{hit.position + tri.normal * 0.001f, toLight};
                        // material: (diffuse, specular, ambient)
                        // light: (diffuse, specular, ambient, distance)

                    float cosine = glm::dot(toLight, tri.normal) / distance;
                    cosine = cosine > 0 ? cosine : 0;
                    vec3 lightColour = light.diffuseColour * cosine / (distance2) * INVERSE2PI * light.intensity;
                    vec3 colour = lightColour * tri.colour;

                    if(traceShadow(scene, distance, shadowRay)) {
                        colour *= 0.2;
                    }
                    target.setColor(x, y, colour);

                }
            }
//            loop through triangles
//            find intersection using the equation
//            check intersection distance is closer than before
//            set new intersection
//                    return if any intersection exists
        }
        // hard shadow
    }

    bool RayTracer::traceShadow(const Scene &scene, float lightDistance, const Ray &ray) {
        RayHit hit;
        int index = -1;
        closestIntersection(scene.model, ray, hit, index);
        return hit.isHit && (hit.t < lightDistance);
    }

    void closestIntersection(const vector<Triangle> &triangles, const Ray &ray, RayHit& hit, int& closestIndex) {
        RayHit closestHit;
        int closest = -1;
        closestHit.t = MAXFLOAT;
        RayHit hitResult;
        int size = static_cast<int>(triangles.size());
        for(int i = 0; i < size; i++) {
            hitResult = castRay(ray, triangles[i]);
            if(hitResult.isHit && hitResult.t > 0.0f && hitResult.t < closestHit.t) {
                closestHit = hitResult;
                closest = i;
            }
        }
        closestIndex = closest;
        hit = closestHit;
    }
}
