#pragma once

#include "vec3.h"

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

        point3 orig;

        vec3 dir;

};