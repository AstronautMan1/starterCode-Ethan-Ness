/*
    @author Ethan Ness

    BlinnPhongShader Implementation with ray color
*/

/*
    Includes section
*/
#include "BlinnPhongShader.h" // blinn phong shader
#include "hitList.h"


/// @brief This is the ray color function in blinnphong
/// @param r ray object
/// @param rec hit record object
/// @param light light object
/// @param scene the hit list for recursive ray tracing for reflections
/// @param depth the recursion depth for ray tracing reflections
/// @return we return the ambient + diffuse + specular
vec3 BlinnPhongShader::rayColor(const ray &r, const hit_record &rec, const Light &light, Shape &scene, int depth, const vec3 &bgcolor) const {

    // if depth is less then or equal to 0 we return black
    if (depth <= 0){
        return vec3(0,0,0);
    }

    // data declaration 
    float tmin = 0.001f; // tmin
    float tmax = std::numeric_limits<float>::infinity(); // tmax
    bool inShadow = false; // in shadow boolean
    vec3 normal = rec.getNormal(); // normal from the hit record
    vec3 L = unit_vector(light.getPosition() - rec.getPoint()); // L is the unit vector of the light position - point of ray intersect
    vec3 V = unit_vector(r.origin() - rec.getPoint()); // V is the unit vector f ray origin - point of ray intersect
    vec3 H = unit_vector(L + V); // H is unit vector of L + V
    vec3 diffuse(0,0,0); // make diffuse
    vec3 specular(0,0,0); // make specular


    // Shadows
    ray shadow_ray(rec.getPoint() + (normal * 0.001f), L); // shadow ray from point to the light
    float distance_to_light = (light.getPosition() - rec.getPoint()).length(); // float distance to the light
    hit_record shadowRecord; // hit record for the shadow

    if (scene.intersect(shadow_ray, tmin, distance_to_light, shadowRecord)){
        inShadow = true; // if intersect on an object to the light in shadow
    }

    if (!inShadow){ // if not in shadow do the diffuse and specular calculation

        float dotNL = std::max(0.0f, (float)dot(normal, L)); // dot of N and L is the max value from 0 to dot of normal and L
        diffuse = dotNL * albedo * light.getIntensity(); // diffuse is the dot of N and L * albedo * light intensity(color)

        float spec = std::pow(std::max(0.0f, (float)dot(normal,H)), shininess); // spec is the max value of dot product of normal and H to the power of shininess
        specular = specularStrength * spec * light.getIntensity(); // specular is specularStrength * spec * light intensity(color)

    }

    vec3 bounceDirection = normal + random_unit_vector(); // get the direction of the bounce
    ray scattered_ray(rec.getPoint() + (normal * 0.001f), bounceDirection); // scattered ray

    vec3 indirectDiffuse = scene.computeRayColor(scattered_ray, tmin, tmax, light, bgcolor, depth - 1); // indirect diffuse is the recursion of compute ray color with depth - 1

    return (albedo * indirectDiffuse) + diffuse + specular; // return the albedo * indirectDiffuse + diffuse + specular

}