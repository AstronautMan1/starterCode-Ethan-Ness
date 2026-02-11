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
