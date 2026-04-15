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
#include "BoundingBox.h"

/// @brief This is the triangle class which inherits from shape
class Triangle : public Shape{

    public:

        Triangle() : vertex_a(0.0,0.0,0.0), vertex_b(1.0,0.0,0.0), vertex_c(0.0,1.0,0.0) {} // base constructor

        Triangle(const vec3 &v0, const vec3 &v1, const vec3 &v2) : vertex_a(v0), vertex_b(v1), vertex_c(v2) {} // parameter pass in constructor

        Triangle(const vec3 &v0, const vec3 &v1, const vec3 &v2, std::shared_ptr<shader> triangleShader) : vertex_a(v0), vertex_b(v1), vertex_c(v2), shaderPtr(triangleShader) {}

        bool intersect(const ray &r, float tmin, float &tmax, hit_record &rec) override; // overridden intersect function which is from the Shape interface

        void setShader(std::shared_ptr<shader> newShader) {shaderPtr = newShader;}

        BoundingBox boundingBox() const override {
            vec3 min(
                std::min({vertex_a.x(), vertex_b.x(), vertex_c.x()}),
                std::min({vertex_a.y(), vertex_b.y(), vertex_c.y()}),
                std::min({vertex_a.z(), vertex_b.z(), vertex_c.z()})
            );
            vec3 max(
                std::max({vertex_a.x(), vertex_b.x(), vertex_c.x()}),
                std::max({vertex_a.y(), vertex_b.y(), vertex_c.y()}),
                std::max({vertex_a.z(), vertex_b.z(), vertex_c.z()})
            );

            return BoundingBox(min, max);
        }

    private:

        vec3 vertex_a, vertex_b, vertex_c; // the three vertices of the triangle

        std::shared_ptr<shader> shaderPtr; // shader pointer


};