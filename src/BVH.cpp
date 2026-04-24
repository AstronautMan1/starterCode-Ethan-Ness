/*
    @author Ethan Ness

    @details This is the implementation file for the BVH
*/

#include "BVH.h" // include BVH class header

/// @brief This is the compute ray color function that BVH inherits from shape
/// @param r ray r
/// @param tmin tmin value
/// @param tmax tmax value
/// @param light light
/// @param bgcolor background color
/// @param depth depth value
/// @return return the vec3 of the the computed ray color
vec3 bvhNode::computeRayColor(const ray &r, float tmin, float tmax, const Light &light, const vec3 &bgcolor, int depth) {

    if (depth <= 0) return bgcolor; // if the depth is 0 or less return the background color

    hit_record rec; // make a hit record
    float localTmax = tmax; // local tmax

    if (this->intersect(r, tmin, localTmax, rec)) { // if intersect on ray is true
        std::shared_ptr<shader> useShader = rec.getShader(); // make a shader pointer for what shader to use from intersected shape
        return useShader->rayColor(r, rec, light, *this, depth, bgcolor); // return the ray color on that shader
    } else {
        return bgcolor; // else return the bgcolor if no intersect
    }
}

/// @brief this is the BVH node for the BVH tree
/// @param objects objects vector 
/// @param start size for the start of vector
/// @param end size for the end of vector
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