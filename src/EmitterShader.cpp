#include "EmitterShader.h"

vec3 EmitterShader::rayColor(const ray &r, const hit_record &rec, const Light &light, Shape &scene, int depth, const vec3 &bgcolor) const {

    return emitColor * intensity;

}