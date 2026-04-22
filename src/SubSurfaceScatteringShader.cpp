#include "SubSurfaceScatteringShader.h"
#include <cmath>
#include <random>
#include <algorithm>

inline float random_double() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}


vec3 SubSurfaceShader::rayColor(const ray &r, const hit_record &rec, const Light &light, 
                                 Shape &scene, int depth, const vec3 &bgcolor) const {
    if (depth <= 0) return vec3(0,0,0);

    vec3 hitPoint = rec.getPoint();
    vec3 normal = rec.getNormal();
    
    // 1. Direct diffuse silhouette
    vec3 L_surf = unit_vector(light.getPosition() - hitPoint);
    float dotNL = std::max(0.0f, (float)dot(normal, L_surf));
    vec3 direct = light.getIntensity() * albedo * dotNL;

    // 2. Subsurface Random Walk (Single Sample Version)
    float extinction = sigma_a + sigma_s;
    float s_albedo = sigma_s / extinction;

    // Start slightly inside the surface to avoid self-intersection
    vec3 current_pos = hitPoint - normal * 0.001f;
    vec3 current_dir = unit_vector(-normal + random_unit_vector());
    vec3 throughput(1.0, 1.0, 1.0);
    vec3 sss_result(0,0,0);
    
    // Perform a single random walk path
    for (int bounce = 0; bounce < 12; ++bounce) {
        float step_dist = -std::log(std::max(1e-7f, random_double())) / extinction;
        current_pos += current_dir * step_dist;
        
        throughput = throughput * (albedo * s_albedo);

        // Light Probe
        vec3 L_path = light.getPosition() - current_pos;
        float dist_to_light = L_path.length();
        ray to_light(current_pos, unit_vector(L_path));
        hit_record light_rec;

        if (scene.intersect(to_light, 0.0001f, dist_to_light, light_rec)) {
            float dist_inside = light_rec.getT();
            float atten = std::exp(-extinction * dist_inside);
            vec3 transmission(atten, atten, atten);
            
            sss_result += light.getIntensity() * throughput * transmission;
        }

        // Scatter to a new random direction
        current_dir = random_unit_vector();
        
        // Russian Roulette
        float max_v = std::max({throughput.x(), throughput.y(), throughput.z()});
        if (max_v < 0.01f) break;
    }

    // Blend the result of the single path with the direct lighting
    return (direct * 0.2f) + (sss_result * 0.8f);
}
