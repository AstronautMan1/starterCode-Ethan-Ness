/*
    @author Ethan Ness

    The Lambertian Shader class which gets the rayColor via the Lambertian shader method.
*/

#pragma once


/*
    Includes Section
*/
#include "Shader.h" // shader class
#include <algorithm> // algorithm library 

class hitList; // forward declaration

/// @brief Lambertian Shader implements the Lambertian shading technique and this class inherits from shader interface
class LambertianShader : public shader{

    public:

        LambertianShader(const vec3 &color) : albedo(color) {} // constructor takes vec3 color to set the base color

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light, hitList &scene, int depth) const override; // rayColor function which it inherited from shader


    private:

        
        vec3 albedo; // base color which is a vec3

};