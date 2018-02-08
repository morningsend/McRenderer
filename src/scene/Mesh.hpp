//
// Created by Zaiyang Li on 25/01/2018.
//

#ifndef RENDERER_MESH_HPP
#define RENDERER_MESH_HPP

#include <vector>
#include "Transform.hpp"
#include "Vertex.hpp"
#include "../tree/BoundingBox.hpp"
#include "Material.hpp"

namespace McRenderer {
    using namespace std;
    struct Mesh {
        vec4 pivotPoint;
        Transform transform;
        vector<Vertex> vertices;
        BoundingBox boundingBox;
        Material material;
    };
}


#endif //RENDERER_MESH_HPP
