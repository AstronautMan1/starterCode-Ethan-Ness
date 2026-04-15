#include "BVH.h"

vec3 bvhNode::computeRayColor(const ray &r, float tmin, float tmax, const Light &light, const vec3 &bgcolor, int depth) {
    if (depth <= 0) return bgcolor;

    hit_record rec;
    float localTmax = tmax;

    if (this->intersect(r, tmin, localTmax, rec)) {
        std::shared_ptr<shader> useShader = rec.getShader();
        return useShader->rayColor(r, rec, light, *this, depth, bgcolor);
    } else {
        return bgcolor;
    }
}

bvhNode::bvhNode(std::vector<std::shared_ptr<Shape>>& objects, size_t start, size_t end)
{

    int axis = rand() % 3;
    auto comparator = [axis](const std::shared_ptr<Shape>& a, const std::shared_ptr<Shape>& b) {
        return a->boundingBox().min[axis] < b->boundingBox().min[axis];
    };

    size_t objectSpan = end - start;

    if(objectSpan == 1){
        leftChild = rightChild = objects[start];
    }
    else if(objectSpan == 2) {
        if(comparator(objects[start], objects[start+1])) {
            leftChild = objects[start];
            rightChild = objects[start+1];
        }
        else {
            leftChild = objects[start+1];
            rightChild = objects[start];
        }
    }
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        size_t mid = start + objectSpan / 2;
        leftChild = std::make_shared<bvhNode>(objects, start, mid);
        rightChild = std::make_shared<bvhNode>(objects, mid, end);
    }

    box = BoundingBox::mergeBoundingBoxes(leftChild->boundingBox(), rightChild->boundingBox());

}


bool bvhNode::intersect(const ray& r, float tmin, float &tmax, hit_record &rec){
    if (!box.hit(r, tmin, tmax)) return false;

    bool hitLeft = leftChild->intersect(r, tmin, tmax, rec);
    float hitTmax = hitLeft ? rec.t : tmax;
    bool hitRight = rightChild->intersect(r, tmin, hitTmax, rec);


    return hitLeft || hitRight;
}