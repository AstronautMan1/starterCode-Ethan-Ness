/*
    @author Ethan Ness

    @details The implementation file for emitter shader
*/
#include "EmitterShader.h" // emitter shader class

/// @brief The ray color return for emitter
/// @param r ray r
/// @param rec hit record
/// @param light light 
/// @param scene shape in scene
/// @param depth depth
/// @param bgcolor background color
/// @return return the emitcolor * intensity
vec3 EmitterShader::rayColor(const ray &r, const hit_record &rec, const Light &light, Shape &scene, int depth, const vec3 &bgcolor) const {

    return emitColor * intensity;

}