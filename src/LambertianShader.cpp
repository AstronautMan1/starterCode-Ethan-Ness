/*
    @author Ethan Ness

    Lambertian Shader implementation
*/

/*
    includes section
*/
#include "LambertianShader.h" // lambertian shader class


/// @brief This handles the ray color in the lambertian shading style
/// @param r ray passed in
/// @param rec the hit record for the object
/// @param light the lights in the scene
/// @return we return a vec3 which is the color of that pixel
vec3 LambertianShader::rayColor(const ray &r, const hit_record &rec, const Light &light) const {

    vec3 light_direction = unit_vector(light.getPosition() - rec.getPoint()); // we get the direction of the color by the unit vector of the lights position and the point of the shape in hit_record

    float cosine_theta = std::max(0.0f, (float)dot(rec.getNormal(), light_direction)); // this does dot product between surface normal and light direction which gives the cosine of the two

    return albedo * light.getIntensity() * cosine_theta; // then we return the base color * lights color * cosine theta
}