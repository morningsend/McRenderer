//
// Created by Zaiyang Li on 06/02/2018.
//

#ifndef RENDERER_KDTREE_HPP
#define RENDERER_KDTREE_HPP

#include "../scene/Mesh.hpp"
#include "../scene/Plane.hpp"
#include "../scene/AxisAlignedPlane.hpp"

namespace McRenderFace {

    struct KdTreeNode {
        KdTreeNode* left {nullptr};
        KdTreeNode* right {nullptr};
        BoundingBox boundingBox;
        AxisAlignedPlane plane;

        KdTreeNode(KdTreeNode* leftIn, KdTreeNode* rightIn, BoundingBox box);
        KdTreeNode();

        void freeChildren();
    };

    /**
     * Kd tree provides fast traversal time for finding closest intersection of ray against triangular mesh.
     * Havran Thesis
     * Chapter 4 - Construction of Kd-Trees
     * http://dcgi.felk.cvut.cz/home/havran/DISSVH/dissvh.pdf
     * KD tree used here have Axis-oriented splitting planes
     */
    class KdTree {
    private:
        Mesh* mesh;
        KdTreeNode* rootNode;

        KdTreeNode* ceateTree(const Mesh& mesh);

        KdTreeNode*
    public:
        KdTree(const Mesh* mesh);
        ~KdTree();
    };
}


#endif //RENDERER_KDTREE_HPP
