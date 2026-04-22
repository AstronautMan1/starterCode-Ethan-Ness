/*
    @author Ethan Ness

    A basic setup for a emitter shader to implement area lights
*/

#pragma once

#include "Shader.h"

class EmitterShader : public shader{


    public:

        EmitterShader(vec3 albedo, float inten) : emitColor(albedo), intensity(inten) {}; // constructor

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light, Shape &scene, int depth, const vec3 &bgcolor) const override; // rayColor


    private:

        vec3 emitColor;

        float intensity;


};