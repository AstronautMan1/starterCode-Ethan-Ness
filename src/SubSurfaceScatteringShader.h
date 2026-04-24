/*
    @author Ethan Ness

    @details This is the class header file for the subsurface scattering shader
*/
#pragma once

#include "Shader.h" // shader class
#include <random> // random library


/// @brief This is the sub surface shader class
class SubSurfaceShader : public shader{

    public:

        SubSurfaceShader(const vec3 &a, float scattering, float absorption) : albedo(a), sigma_s(scattering), sigma_a(absorption) {} // constructor

        virtual vec3 rayColor(const ray &r, const hit_record &rec, const Light &light, Shape &scene, int depth, const vec3 &bgcolor) const override; // ray color override

    private:

        vec3 albedo; // albedo (color)
        float sigma_s; // sigma_s or scattering variable (how much we scatter)
        float sigma_a; // Sigma_a or absorption variable (how much light is absorbed in each bounce)

        /// @brief Random unit vector function
        /// @return returns random vec3 unit vector
        vec3 random_unit_vector() const{
            static std::uniform_real_distribution<float> dist(-1.0, 1.0); // random float distribution from -1 to 1
            static std::mt19937 gen; // RNG
            while(true){ // while true
                vec3 p(dist(gen), dist(gen), dist(gen)); // make a vec3 with random floats
                if (p.length_squared() >= 1) continue; // if the length squared of the vec3 is greater or equal to 1 we continue
                return unit_vector(p); // return the unit vector otherwise
            }
        }
};