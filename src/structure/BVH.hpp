//
// Created by Zaiyang Li on 26/04/2018.
//

#ifndef RENDERER_BVH_HPP
#define RENDERER_BVH_HPP

#include <vector>
#include <memory>
#include "../scene/AxisAlignedBoundingBox.hpp"

namespace McRenderFace {
    using namespace std;

    enum BVHNodeType {
        Default, Leaf
    };
    template<class T>
    struct BVHLeafNode {
        AxisAlignedBoundingBox bounds{};
        vector<T> objects{};
    };

    template<class T>
    struct BVHNode {
        union {
            struct {
                BVHNode<T> *left{nullptr};
                BVHNode<T> *right{nullptr};
            };
            BVHLeafNode<T>* leafNode{nullptr};
        };
        AxisAlignedBoundingBox bounds{};
        BVHNodeType type{BVHNodeType::Default};
    };


    template<class T>
    class BVH : public RayIntersecting {
        BVHNode<T>* root{nullptr};
    public:
        typedef T type;
        template<class TT>
        static BVH<TT> build(vector<TT> objects) {
            BVH bvh;
            bvh.root = new BVHNode{};
        }

        ~BVH(){
            delete root;
            root = nullptr;
        }

        void castRay(const Ray& ray, RayHit& hit) {

        }
    };
}


#endif //RENDERER_BVH_HPP
