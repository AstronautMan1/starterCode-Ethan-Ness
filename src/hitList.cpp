/*
    @author Ethan Ness 

    Implementation of the hit list class
*/
#include "hitList.h"

/// @brief This is the intersect function overridden by the hitList class from the Shape class it inheretied
/// @param r This is a ray object that is constant and reference 
/// @param tmin this is the tmin for the ray
/// @param tmax This is the tmax for the ray
/// @return we return either true or false if a object in the list was hit
bool hitList::intersect(const ray &r, float tmin, float &tmax) {

    bool hit_object = false; // hit object boolean
    float closest_object = tmax; // closest object is tmax

    for(const auto &object : objects){ // for every Shape pointer in the objects list

        if (object->intersect(r, tmin, closest_object)) { // if the ray intersects the object in the list then...
            hit_object = true; // set the hit object variable true
            tmax = closest_object; // set tmax = to closest object
        }
    }

    return hit_object; // return the hit object boolean

}