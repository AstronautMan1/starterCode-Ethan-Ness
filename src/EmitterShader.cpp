/*
    @author Ethan Ness

    A basic setup for a emitter shader to implement area lights
*/

#pragma once

#include "Shader.h"

class EmitterShader : public shader{


    public:

        EmitterShader() {} // constructor

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light, hitList &scene, int depth, vec3 &bgcolor) const override; // rayColor


    private:


};