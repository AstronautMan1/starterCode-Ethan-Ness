/*
    @author Ethan Ness

    basic shader interface for other shaders to use as a parent for the ray color function
*/

#pragma once

/*
    Includes section
*/
#include "vec3.h" // vec3 class
#include "ray.h" // ray class
#include "hitRecord.h" // hit record class
#include "Light.h" // light class
#include "shape.h"

class hitList; // forward declaration

/// @brief Shader interface
class shader {

    public:

        shader(){} // default shader constructor

        virtual ~shader() {} // default destructor

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light, Shape &scene, int depth, const vec3 &bgcolor) const = 0; // pure virtual function rayColor for other shaders to implemement
    

    private:

};