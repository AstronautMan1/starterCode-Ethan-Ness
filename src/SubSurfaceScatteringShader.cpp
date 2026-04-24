/*
    @author Ethan Ness

    @details This handles the implementation of the SubsurfaceScattering shader and how we handle bouncing of light in an object and exiting
*/

#include "SubSurfaceScatteringShader.h" // include subsurface scattering shader 
#include <cmath> // cmath library
#include <random> // random library 
#include <algorithm> // algorithm library

/// @brief Random double generation from 0 to 1
/// @return returns random distribution
inline float random_double() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

/// @brief Implementation of raycolor for the subsurface scattering shader
/// @param r ray r
/// @param rec hit record
/// @param light light objects
/// @param scene scene shape
/// @param depth depth count
/// @param bgcolor background color
/// @return vec3 pixel color is returned for the ray color
vec3 SubSurfaceShader::rayColor(const ray &r, const hit_record &rec, const Light &light, 
                                 Shape &scene, int depth, const vec3 &bgcolor) const {

    if (depth <= 0) return vec3(0,0,0);// if the depth is 0 or less return black (0,0,0)

    vec3 hitPoint = rec.getPoint(); // point of ray hit on object
    vec3 normal = rec.getNormal(); // normal of hit object
    
    // 1. Direct diffuse silhouette
    vec3 L_surf = unit_vector(light.getPosition() - hitPoint); // the unit vector of the light position - hit point on the object
    float dotNL = std::max(0.0f, (float)dot(normal, L_surf)); // dot NL is the max of the dot product of the normal of the object and the L_surf(unit vector of light pos and hit point)
    vec3 direct = light.getIntensity() * albedo * dotNL; // direct is the light intensity * albedo(color) * dotNL

    // 2. Subsurface Random Walk (Single Sample Version)
    float extinction = sigma_a + sigma_s; // extinction is the combination of the scattering variable and absorbition variable (how much light is scattered and absorbed)
    float s_albedo = sigma_s / extinction; // S_albedo is the division between the scattering variable and the extinction

    // Start slightly inside the surface to avoid self-intersection
    vec3 current_pos = hitPoint - normal * 0.001f; // current position is slightly inside 
    vec3 current_dir = unit_vector(-normal + random_unit_vector()); // take the negative normal vector to move through
    vec3 throughput(1.0, 1.0, 1.0); // throughput is set
    vec3 sss_result(0,0,0); // SSS result is set
    
    // Perform a single random walk path
    for (int bounce = 0; bounce < 12; ++bounce) { // for number of bounces inside the object
        float step_dist = -std::log(std::max(1e-7f, random_double())) / extinction; // step distance is the negative log of the max of 1e-7f, a random 0-1 double divided by the extinction
        current_pos += current_dir * step_dist; // current position is the current direction * step dist
        
        throughput = throughput * (albedo * s_albedo); // throughput is the throughput * (Albedo[color] * and the scattering color)

        // Light Probe
        vec3 L_path = light.getPosition() - current_pos; // L path is the light position - current position
        float dist_to_light = L_path.length(); // distance to the light is the length of the l_path
        ray to_light(current_pos, unit_vector(L_path)); // ray to the light which takes the current position and makes the direction the unit vector of the Lpath
        hit_record light_rec; // make a light hit record

        if (scene.intersect(to_light, 0.0001f, dist_to_light, light_rec)) { // if the intersect point of ray to light with a tmin of 0.0001 tmax of dist to light and light record is true
            float dist_inside = light_rec.getT(); // distance inside is the t of light rec
            float atten = std::exp(-extinction * dist_inside); // atten is the eulers of -extinction * dist_inside)
            vec3 transmission(atten, atten, atten); // transmission is the vec3 of atten
            
            sss_result += light.getIntensity() * throughput * transmission; // result of the SSS is SSS + intenstity * throughput * transmission
        }

        // Scatter to a new random direction
        current_dir = random_unit_vector(); // new random unit vector for a new direction
        
        // Russian Roulette
        float max_v = std::max({throughput.x(), throughput.y(), throughput.z()}); // a max v is the throughput x,y,z values 
        if (max_v < 0.01f) break; // if the max v is less than 0.01 we break out
    }

    // Blend the result of the single path with the direct lighting
    //return (direct * 0.2f) + (sss_result * 0.8f);
    return (direct * 0.2f) + (sss_result * 2.0f); // return the blending of the direct lighting with the SSS results 
}
