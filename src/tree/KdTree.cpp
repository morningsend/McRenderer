//
// Created by Zaiyang Li on 06/02/2018.
//

#include "KdTree.hpp"

namespace McRenderFace {

    KdTree::KdTree(const Mesh* mesh) {

    }

    KdTree::~KdTree() {
        if(rootNode != nullptr) {
            rootNode->freeChildren();
            delete rootNode;
        }
    }

    KdTreeNode* KdTree::ceateTree(const Mesh &mesh) {
        return nullptr;
    }

    KdTreeNode *KdTree::createTree(vector<Triangle>& trianges, vector<Triangle>& right) {
        return nullptr;
    }

    void KdTreeNode::freeChildren() {
        if(left != nullptr) {
            left->freeChildren();
            delete left;
        }
        if(right != nullptr){
            right -> freeChildren();
            delete right;
        }
    }

    KdTreeNode::KdTreeNode()
            :  KdTreeNode(nullptr, nullptr, BoundingBox{}){

    }

    KdTreeNode::KdTreeNode(KdTreeNode *leftIn, KdTreeNode *rightIn, BoundingBox box)
            : left{leftIn},
              right{rightIn},
              boundingBox{box},
              plane{}
    {

    }
}