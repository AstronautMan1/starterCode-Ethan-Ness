#pragma once

#include "vec3.h"

class Camera {

    public:

        Camera() : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focalLength(1.0), imagePlane_Length(0.25), imagePlane_Width(0.25) {}

        virtual ~Camera() {}


    private:

        vec3 pos;

        vec3 U, V, W;

        float focalLength;

        float imagePlane_Width, imagePlane_Length;

};