/*
    @author Ethan Ness
    @author Peter Willemsen

    Triangle class which inherits from the shape class
*/
#pragma once

/*
    includes section
*/
#include "vec3.h" // vec3 class
#include "shape.h" // Shape class

/// @brief This is the triangle class which inherits from shape
class Triangle : public Shape{

    public:

        Triangle() : vertex_a(0.0,0.0,0.0), vertex_b(1.0,0.0,0.0), vertex_c(0.0,1.0,0.0) {} // base constructor

        Triangle(const vec3 &v0, const vec3 &v1, const vec3 &v2) : vertex_a(v0), vertex_b(v1), vertex_c(v2) {} // parameter pass in constructor

        bool intersect(const ray &r, float tmin, float &tmax, hit_record &rec) override; // overridden intersect function which is from the Shape interface

    private:

        vec3 vertex_a, vertex_b, vertex_c; // the three vertices of the triangle


};