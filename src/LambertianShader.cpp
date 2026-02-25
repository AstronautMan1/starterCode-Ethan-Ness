/*
    @author Ethan Ness

    Lambertian Shader implementation
*/

/*
    includes section
*/
#include "LambertianShader.h" // lambertian shader class
#include "hitList.h"

/// @brief This handles the ray color in the lambertian shading style
/// @param r ray passed in
/// @param rec the hit record for the object
/// @param light the lights in the scene
/// @param scene the hit list for recursive ray tracing
/// @param depth the recursion depth for ray tracing reflections (not used here just needed for interface override compliance)
/// @return we return a vec3 which is the color of that pixel
vec3 LambertianShader::rayColor(const ray &r, const hit_record &rec, const Light &light, hitList &scene, int depth) const {

    if (depth <= 0){ // if depth is equal or less then 0 we return black
        return vec3(0,0,0);
    }

    vec3 normal = rec.getNormal(); // normal
    vec3 lightVector = light.getPosition() - rec.getPoint(); // light vector is the position of light - point of intersect
    float distanceToLight = lightVector.length(); // distance to the light is the length of the lightVector
    vec3 L = unit_vector(lightVector); // L is the unit vector of the light vector
    float tmin = 0.001f; // tmin
    float tmax = std::numeric_limits<float>::infinity(); // tmax
    bool inShadow = false; // in shadow boolean 
    vec3 directLighting(0,0,0); // direct lighting setup

    // shadow section
    ray shadow_ray(rec.getPoint() + (normal * 0.001f), L); // shadow ray setup
    hit_record shadowRecord; // hit record for the shadow

    if (scene.intersect(shadow_ray, tmin, distanceToLight, shadowRecord)){
        inShadow = true; // if intersect we in shadow
    }

    // lambertian section
    if (!inShadow){
        float cosine_theta = std::max(0.0f, (float)dot(normal, L)); // cosine theta calculation
        directLighting = light.getIntensity() * cosine_theta; // direct lighting is light intensity (color) * cosine theta
    }

    vec3 bounce_direction = normal + random_unit_vector(); // bounce direction for scattered ray is normal + random unit vector
    ray scattered_ray(rec.getPoint() + (normal * 0.001f), bounce_direction); // scattered ray setup

    vec3 indirectLight = scene.computeRayColor(scattered_ray, tmin, tmax, light, vec3(0,0,0), depth - 1); // recursive call for indirect lighting

    return albedo * (directLighting + indirectLight); // return albedo * (directLighting + indirectLight)
}