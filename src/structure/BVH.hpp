//
// Created by Zaiyang Li on 26/04/2018.
//

#ifndef RENDERER_BVH_HPP
#define RENDERER_BVH_HPP

#include <vector>
#include <memory>
#include <numeric>
#include "../scene/AxisAlignedBoundingBox.hpp"

namespace McRenderFace {
    using namespace std;

    enum BVHNodeType {
        Internal, Leaf
    };
    template<class T>
    struct BVHLeafNode {
        AxisAlignedBoundingBox bounds{};
        int objectIndex{-1};
    };

    template<class T>
    struct BVHNode {
        BVHNodeType type{BVHNodeType::Internal};
        AxisAlignedBoundingBox bounds{};
        union {
            struct {
                BVHNode<T> *left;
                BVHNode<T> *right;
                int objectCount;
            };
            struct {
                int objectIndex;
            };
        };

        bool isRayIntersecting(const Ray& ray) {

        }
    };

    template<class T>
    class BVH : public RayIntersecting {
        BVHNode<T>* root{nullptr};

        template<class TT>
        static BVHNode<T>* build (vector<TT>& objects, vector<int> objectIndices) {
            return nullptr;
        }

        template<typename TT>
        static void maximumBoundingBox(vector<TT>& objects, AxisAlignedBoundingBox& bbox) {
            AxisAlignedBoundingBox maxBBox;
            if(objects.size() < 1) {
                bbox = maxBBox;
            }
            maxBBox = objects[0].getBoundingBox();
            const int size = objects.size();
            for(int i = 1; i < size; i++){
                maxBBox.unionWith(objects[i].getBoundingBox());
            };
            bbox = maxBBox;
        };
    public:
        typedef T type;
        template<class TT>
        static BVH<TT> build(vector<TT>& objects) {
            BVH bvh;
            AxisAlignedBoundingBox bbox;
            bvh.root = new BVHNode<TT>{};
            bvh.root->objectCount = static_cast<int>(objects.size());
            maximumBoundingBox(objects, bvh.root->bounds);
            if(objects.size() == 0) {
                bvh.root->type = BVHNodeType::Leaf;
                return std::move(bvh);
            } else if(objects.size() == 1) {
                bvh.root->type = BVHNodeType::Leaf;
                bvh.root->objectIndex = 0;
                return std::move(bvh);
            }

            const int size = static_cast<const int>(objects.size());
            int splittingAxis = 0;
            int splittingValue;
            // choose optimal splitting axis.
            vector<vec3> centers(objects.size());
            vector<int> indices(objects.size());

            for(int i = 0; i < size; i++) {
                indices[i] = i;
                centers[i] = objects[i].getCenter();
            }
            BVHNode<TT>* currentNode = bvh.root;
            float minCost = bvh.root->bounds.surfaceArea();
            for(int axis = 0; axis < 3; axis++ ) {
                sort(indices.begin(), indices.end(), [axis, &centers](int id1, int id2){
                    return centers[id1][axis] < centers[id2][axis];
                });

            }
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
