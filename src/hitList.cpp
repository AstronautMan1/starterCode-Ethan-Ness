/*
    @author Ethan Ness 

    Implementation of the hit list class
*/
#include "hitList.h"

/// @brief This is the implementation of the intersect function of hitlist inherited by shape
/// @param r ray that we pass in
/// @param tmin the min t value
/// @param tmax the max t value
/// @param rec the record of the hit list
/// @return returns a boolean if the object was hit
bool hitList::intersect(const ray &r, float tmin, float &tmax, hit_record &rec) {

    bool hit_object = false; // hit object boolean
    float closest_object = tmax; // closest object so far is tmax

    for(const auto &object : objects){ // for every Shape pointer in the objects list

        if (object->intersect(r, tmin, closest_object, rec)) { // if the ray intersects the object in the list then...
            hit_object = true; // set the hit object variable true
            tmax = closest_object; // set tmax = to closest object
        }
    }

    return hit_object; // return the hit object boolean

}

/// @brief this is the compute color for a ray
/// @param r ray object
/// @param tmin the tmin value
/// @param tmax the tmax value
/// @param light the light object which says where the light is
/// @param bgcolor the bg color for the space
/// @return we return either the color of the ray if intersect otherwise return background color
vec3 hitList::computeRayColor(const ray &r, float tmin, float tmax, const Light &light, const vec3 &bgcolor){

    hit_record rec; // make a hit record

    float localTmax = tmax; // local tmax is tmax

    bool hitShape = false; // set hitshape to false

    for (int index = 0; index < objects.size(); ++index){ // for every object in the scene run intersect if there is an intersect on the ray r set hitshape to true if intersect happens
        if(objects[index]->intersect(r,tmin,localTmax,rec)){
            hitShape = true;
        }
    }

    if(hitShape){ // if we hit a shape we set get the shader for the object
        std::shared_ptr<shader> useShader = rec.getShader(); // get the shader for the object of the ray we hit
        vec3 color = useShader->rayColor(r,rec,light); // get the ray color based on that ray r
        return color; // return color
    }
    else { // otherwise return background color
        return bgcolor;
    }
}