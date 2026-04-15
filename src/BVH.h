/*
    @author Ethan Ness

    @details This is the BVH class for implementing the BVH
*/

#include "shape.h"
#include <vector>
#include "BoundingBox.h"
#include "Light.h"
#include "Shader.h"

class bvhNode : public Shape{

    public:

        bvhNode(std::vector<std::shared_ptr<Shape>>& objects, size_t start, size_t end);

        bool intersect(const ray& r, float tmin, float &tmax, hit_record &rec);

        vec3 computeRayColor(const ray &r, float tmin, float tmax, const Light &light, const vec3 &bgcolor, int depth) override;

        BoundingBox boundingBox() const override {return box;}

private:

    std::shared_ptr<Shape> leftChild;
    std::shared_ptr<Shape> rightChild;
    BoundingBox box;

    //BoundingBox mergeBoundingBoxes(const BoundingBox &b0, const BoundingBox &b1);

};