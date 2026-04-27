/*
    @author Ethan Ness


    The Sphere class that handles making of spheres which is an inheritance of the Shape interface
*/

#pragma once


/*
    Includes section
*/
#include "shape.h" // shape class
#include "BoundingBox.h"

/// @brief The Sphere class which inherits the shape classes public functions and implements the pure virtual intersect function
class Sphere : public Shape{

    public:

        Sphere() : center(0,0,0), radius(1.0f) {} // base constructor

        Sphere(point3 centerOfSphere, float radiusOfSphere) : center(centerOfSphere), radius(radiusOfSphere) {} // pass in constructor

        Sphere(point3 centerOfSphere, float radiusOfSphere, std::shared_ptr<shader> sphereShader) : center(centerOfSphere), radius(radiusOfSphere), shaderPtr(sphereShader) {}

        bool intersect(const ray& r, float tmin, float &tmax, hit_record &rec) override; // override the pure virtual intersect from shape interface

        point3 getCenter(); // getter for the center

        float getRadius(); // getter for the radius

        void setCenter(point3 newCenter); // setter for a new center

        void setRadius(float newRadius); // setter for a new radius

        void setShader(std::shared_ptr<shader> newShader) {shaderPtr = newShader;}

        BoundingBox boundingBox() const override{ // bounding box for sphere
            vec3 min = center - vec3(radius, radius, radius);
            vec3 max = center + vec3(radius, radius, radius);
            return BoundingBox(min, max);
        }

    private:

        point3 center; // center of the sphere

        float radius; // radius of the sphere

        std::shared_ptr<shader> shaderPtr; // shader pointer

};