#include "BlinnPhongShader.h"

vec3 BlinnPhongShader::rayColor(const ray &r, const hit_record &rec, const Light &light) const {

    vec3 normal = rec.getNormal();
    vec3 L = unit_vector(light.getPosition() - rec.getPoint());
    vec3 V = unit_vector(r.origin() - rec.getPoint());
    vec3 H = unit_vector(L + V);

    float dotNL = std::max(0.0f, (float)dot(normal, L));
    vec3 diffuse = dotNL * base * light.getIntensity();

    float spec = std::pow(std::max(0.0f, (float)dot(normal,H)), shininess);
    vec3 specular = specularStrength * spec * light.getIntensity();

    vec3 ambient = 0.1f * base;

    return ambient + diffuse + specular;

}