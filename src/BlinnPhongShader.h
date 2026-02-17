/*
    @author Ethan Ness

    This is the BlinnPhongShader class 
*/

#pragma once


/*
    Includes Section
*/
#include "Shader.h" // shader class

/// @brief This is the blinnphongshader which uses the shader interface for the implementation
class BlinnPhongShader : public shader {

    public:

        BlinnPhongShader(vec3 b, float shine, float spec) : albedo(b), shininess(shine), specularStrength(spec) {} // constructor

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light) const override; // override of ray color
        

    private:

        vec3 albedo; // albedo for the basic ray color

        float shininess; // the shininess for the blinn phong calculation

        float specularStrength; // strength of the specular reflection

};