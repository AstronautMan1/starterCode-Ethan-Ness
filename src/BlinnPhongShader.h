#pragma once

#include "Shader.h"

class BlinnPhongShader : public shader {

    public:

        BlinnPhongShader(vec3 b, float shine, float spec) : base(b), shininess(shine), specularStrength(spec) {}

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light) const override;
        

    private:

        vec3 base;

        float shininess;

        float specularStrength;

};