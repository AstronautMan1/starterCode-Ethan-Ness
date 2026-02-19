/*
    @author Ethan Ness

    This handles having multiple objects in a scene with a vector of objects in the scene and if a ray hits an object in the list we then return true in intersect function
    This class inherits from shape
*/

#pragma once

/*
    includes section
*/
#include "shape.h" // shape class
#include "hitRecord.h" // hit record class
#include "Shader.h" // shader class
#include "Light.h" // light class
#include <vector> // vector library

/// @brief The hitList class is a class which has a vector of shared pointers to shape objects and inherits the public of the shape class and has its own intersect 
///        implementation also an add and clear function as well and a basic constructor
class hitList : public Shape{

    public:

        hitList() {} // constructor

        void add(std::shared_ptr<Shape> object) {objects.push_back(object);} // add to vector list

        void clear() {objects.clear();} // clear vector list

        bool intersect(const ray &r, float tmin, float &tmax, hit_record &rec) override; // pure virtual intersect overriden from Shape class

        vec3 computeRayColor(const ray &r, float tmin, float tmax, const Light &light, const vec3 &bgcolor, int depth); // compute ray color function

    private:

        std::vector<std::shared_ptr<Shape>> objects; // vector list of shared pointer shapes

};