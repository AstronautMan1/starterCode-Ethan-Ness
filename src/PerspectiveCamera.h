#pragma once

#include "camera.h"

class PerspectiveCamera : public Camera {

    public:

        PerspectiveCamera() : Camera() {}

        PerspectiveCamera(vec3 position, vec3 valueU, vec3 valueV, vec3 valueW, float focal, float planeWidth, float planeLength) 
        : pos(position), U(valueU), V(valueV), W(valueW), focalLength(focal), imagePlane_Width(planeWidth), imagePlane_Length(planeLength) {}

        void generateRay(int i, int j, ray &r) override;


    private:

        vec3 pos;

        vec3 U,V,W;

        float focalLength;

        float imagePlane_Width;

        float imagePlane_Length;
};