/*
    @author Ethan Ness

    Light class which just is a single point light
*/

#pragma once

/*
    Includes Section
*/
#include "vec3.h" // vec3 class

/// @brief The Light class which handles lights in the scene
class Light{

    public:

        Light(const point3 &pos, const vec3 &color, const std::string lighttype) : position(pos), intensity(color), type(lighttype) {} // light construtor which takes a position and color

        vec3 getPosition() const {return position;} // getter for position

        vec3 getIntensity() const {return intensity;} // getter for intensity
        
        std::string type;

    private:

        point3 position; // position of the light 

        vec3 intensity; // intensity / color of the light

};