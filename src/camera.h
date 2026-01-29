#pragma once

#include "vec3.h"
#include "ray.h"

class Camera {

    public:

        Camera() : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focalLength(1.0f), imagePlane_Length(0.25f), imagePlane_Width(0.25f), nx(100), ny(100) {}

        Camera(vec3 position, vec3 valueU, vec3 valueV, vec3 valueW, float focal, float planeWidth, float planeLength, int imageWidth, int imageHeight) 
        : pos(position), U(valueU), V(valueV), W(valueW), focalLength(focal), imagePlane_Width(planeWidth), imagePlane_Length(planeLength), nx(imageWidth), ny(imageHeight) {}

        virtual ~Camera() {}

        virtual void generateRay(int i, int j, ray &r) = 0;


    private:

        vec3 pos;

        vec3 U, V, W;

        int nx, ny;

        float focalLength;

        float imagePlane_Width, imagePlane_Length;

};