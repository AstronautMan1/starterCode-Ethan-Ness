/*
    @author Ethan Ness

    This is the ray class which handles the making of rays
*/

#pragma once

/*
    include section
*/
#include "vec3.h" // vec3 class

/// @brief This is the ray class which handles the making of rays with an origin and a direction
class ray {

    public:

        ray() : orig(0,0,0), dir(0,0,0)  {}

        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        const point3& origin() const {return orig;}
        const vec3& direction() const {return dir;}

        point3 at(double t) const {
            return orig + t*dir;
        }

        void setOrigin(point3 newOrigin) {orig = newOrigin;}

        void setDirection(vec3 newDirection) {dir = newDirection;}

    private:

        point3 orig; // origin of the ray

        vec3 dir; // direction of the ray

};