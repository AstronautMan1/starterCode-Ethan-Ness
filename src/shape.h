/*
    @author Ethan Ness

    This is the shape interface class for making different classes
*/
#pragma once

/*
    includes section
*/
#include "ray.h" // ray class
#include "hitRecord.h" // hit record class
#include "Light.h"
#include "BoundingBox.h"

/// @brief The shape interface which will be used for making different shapes
class Shape{

    public:

        Shape() {} // basic constructor

        virtual ~Shape() {} // basic deconstructor

        virtual bool intersect(const ray& r, float tmin, float &tmax, hit_record &rec) = 0; // pure virtual intersect function

        virtual BoundingBox boundingBox() const = 0;

        virtual vec3 computeRayColor(const ray &r, float tmin, float tmax, const Light &light, const vec3 &bgcolor, int depth) {
        // Default: just return background color
        return bgcolor;
        }

    private:

};