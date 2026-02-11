/*
    @author Ethan Ness

    the Hitrecord implementation file for set_face_normal
*/

/*
    includes section
*/
#include "hitRecord.h" // hit record class

/// @brief this finds which side of the surface does the ray hit
/// @param r the ray 
/// @param outward_normal the outward normal is the outward direction from center of the object
void hit_record::set_face_normal(const ray &r, const vec3 &outward_normal){

    front_face = dot(r.direction(), outward_normal) < 0; // dot product gives the angle from the ray and outward normal

    normal = front_face ? outward_normal : -outward_normal; // if it is the front face keep the normal otherwise flip it if negative it is hitting the front if positive it is hitting the back.
    
}