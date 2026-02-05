/*
    @author Ethan Ness


    The Sphere class that handles making of spheres which is an inheritance of the Shape interface
*/

#pragma once


/*
    Includes section
*/
#include "shape.h" // shape class

/// @brief The Sphere class which inherits the shape classes public functions and implements the pure virtual intersect function
class Sphere : public Shape{

    public:

        Sphere() : center(0,0,0), radius(1.0f) {} // base constructor

        Sphere(point3 centerOfSphere, float radiusOfSphere) : center(centerOfSphere), radius(radiusOfSphere) {} // pass in constructor

        bool intersect(const ray& r) override; // override the pure virtual intersect from shape interface

        point3 getCenter(); // getter for the center

        float getRadius(); // getter for the radius

        void setCenter(point3 newCenter); // setter for a new center

        void setRadius(float newRadius); // setter for a new radius

    private:

        point3 center; // center of the sphere

        float radius; // radius of the sphere

};