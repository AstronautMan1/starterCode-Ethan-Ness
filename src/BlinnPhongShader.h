/*
    @author Ethan Ness

    This is the BlinnPhongShader class 
*/

#pragma once


/*
    Includes Section
*/
#include "Shader.h" // shader class

/// @brief 
class BlinnPhongShader : public shader {

    public:

        BlinnPhongShader(vec3 b, float shine, float spec) : albedo(b), shininess(shine), specularStrength(spec) {}

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light) const override;
        

    private:

        vec3 albedo;

        float shininess;

        float specularStrength;

};