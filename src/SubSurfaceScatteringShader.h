#pragma once

#include "Shader.h"
#include <random>

class SubSurfaceShader : public shader{

    public:

        SubSurfaceShader(const vec3 &a, float scattering, float absorption) : albedo(a), sigma_s(scattering), sigma_a(absorption) {}

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light, Shape &scene, int depth, const vec3 &bgcolor) const override;

    private:

        vec3 albedo;
        float sigma_s;
        float sigma_a;

        vec3 random_unit_vector() const{
            static std::uniform_real_distribution<float> dist(-1.0, 1.0);
            static std::mt19937 gen;
            while(true){
                vec3 p(dist(gen), dist(gen), dist(gen));
                if (p.length_squared() >= 1) continue;
                return unit_vector(p);
            }
        }
};