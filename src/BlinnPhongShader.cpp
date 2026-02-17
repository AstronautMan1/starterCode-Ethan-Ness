/*
    @author Ethan Ness

    BlinnPhongShader Implementation with ray color
*/

/*
    Includes section
*/
#include "BlinnPhongShader.h" // blinn phong shader


/// @brief This is the ray color function in blinnphong
/// @param r ray object
/// @param rec hit record object
/// @param light light object
/// @return we return the ambient + diffuse + specular
vec3 BlinnPhongShader::rayColor(const ray &r, const hit_record &rec, const Light &light) const {

    vec3 normal = rec.getNormal(); // normal from the hit record
    vec3 L = unit_vector(light.getPosition() - rec.getPoint()); // L is the unit vector of the light position - point of ray intersect
    vec3 V = unit_vector(r.origin() - rec.getPoint()); // V is the unit vector f ray origin - point of ray intersect
    vec3 H = unit_vector(L + V); // H is unit vector of L + V

    float dotNL = std::max(0.0f, (float)dot(normal, L)); // dot of N and L is the max value from 0 to dot of normal and L
    vec3 diffuse = dotNL * albedo * light.getIntensity(); // diffuse is the dot of N and L * albedo * light intensity(color)

    float spec = std::pow(std::max(0.0f, (float)dot(normal,H)), shininess); // spec is the max value of dot product of normal and H to the power of shininess
    vec3 specular = specularStrength * spec * light.getIntensity(); // specular is specularStrength * spec * light intensity(color)

    vec3 ambient = 0.1f * albedo; // ambient is 0.1 * albedo

    return ambient + diffuse + specular; // return the ambient + diffuse + specular

}