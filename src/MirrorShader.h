/*
    @author Ethan Ness

    The Mirror Shader class which is a shader for mirrors which inherits from the shader class
*/

#pragma once

/*
    Includes Section
*/
#include "Shader.h" // shader class

class hitList; // forward declaration to avoid double inclusion

/// @brief Mirror Shader implements perfect mirror reflections with recursive ray tracing
class MirrorShader : public shader {

    public:
    
    MirrorShader(const vec3& Passcolor, float Passreflectance) : reflectance(Passreflectance), albedo(Passcolor) {} // mirrorshader constructor

    virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light, hitList &scene, int depth, vec3 &bgcolor) const override; // rayColor function which it inherited from shader

    private:
        
        float reflectance; // how reflective the mirror is (1.0 = perfect mirror)

        vec3 albedo; // color

};
