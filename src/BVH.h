/*
    @author Ethan Ness

    @details This is the BVH class for implementing the BVH
*/

#include "shape.h" // shape class 
#include <vector> // vector library
#include "BoundingBox.h" // bounding box class
#include "Light.h" // light class
#include "Shader.h" // shader class

/// @brief  The BVH node class which inherits from shape
class bvhNode : public Shape{

    public:

        bvhNode(std::vector<std::shared_ptr<Shape>>& objects, size_t start, size_t end); // constructor

        bool intersect(const ray& r, float tmin, float &tmax, hit_record &rec); // intersect function

        vec3 computeRayColor(const ray &r, float tmin, float tmax, const Light &light, const vec3 &bgcolor, int depth) override; // overridden compute ray color

        BoundingBox boundingBox() const override {return box;} // bounding box getter

private:

    std::shared_ptr<Shape> leftChild; // left child
    std::shared_ptr<Shape> rightChild; // right child
    BoundingBox box; // bounding box object

};