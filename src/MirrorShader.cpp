/*
    @author Ethan Ness

    Mirror Shader implementation with recursive ray tracing using depth
*/

/*
    includes section
*/
#include "MirrorShader.h" // mirror shader class
#include "hitList.h" // hitlist class for recursive tracing

/// @brief This handles the ray color in the mirror shading style using depth for recursion
/// @param r ray passed in
/// @param rec the hit record for the object
/// @param light the lights in the scene
/// @param scene the hit list for recursive ray tracing
/// @param depth the recursion depth - controls how many reflections to trace
/// @return we return a vec3 which is the color of the reflected rays
vec3 MirrorShader::rayColor(const ray &r, const hit_record &rec, const Light &light, hitList &scene, int depth) const {

    if (depth <= 0) {
        return vec3(0.0f, 0.0f, 0.0f); // stop recursion if depth is 0
    }

    // Calculate the reflected ray direction
    vec3 incident = unit_vector(r.direction()); // normalize the incident ray direction
    vec3 normal = rec.getNormal(); // get the surface normal
    vec3 reflected_dir = reflect(incident, normal); // reflect the incident direction about the normal

    // Create a reflected ray starting from the hit point
    ray reflected_ray(rec.getPoint() + normal * 0.001f, reflected_dir); // slightly offset to avoid self-intersection

    float tmin = 0.001f; // minimum t value for ray intersection
    float tmax = std::numeric_limits<float>::infinity(); // maximum t value

    // Recursively trace the reflected ray and blend with reflectance
    vec3 reflected_color = scene.computeRayColor(reflected_ray, tmin, tmax, light, vec3(0.0f, 0.0f, 0.0f), depth - 1);

    // Return the reflected color scaled by reflectance and albedo
    return reflected_color * reflectance * albedo + albedo * (1.0f - reflectance);
}
