#pragma once

#include "camera.h"

class PerspectiveCamera : public Camera {

    public:

        PerspectiveCamera() : Camera() {}

        PerspectiveCamera(vec3 position, vec3 valueU, vec3 valueV, vec3 valueW, float focal, float planeWidth, float planeLength, int imageWidth, int imageHeight) 
        : pos(position), U(valueU), V(valueV), W(valueW), focalLength(focal), imagePlane_Width(planeWidth), imagePlane_Length(planeLength), nx(imageWidth), ny(imageHeight) {
            leftBound = -planeWidth / 2.0f;
            rightBound = planeWidth / 2.0f;
            bottomBound = -planeLength / 2.0f;
            topBound = planeLength / 2.0f;
        }

        void generateRay(int i, int j, ray &r) override;

        void setNX(int width) {nx = width;}

        void setNY(int height) {ny = height;}


    private:

        vec3 pos;

        vec3 U,V,W;

        float focalLength;

        float imagePlane_Width;

        float imagePlane_Length;

        int nx;  

        int ny;  

        float leftBound, rightBound, bottomBound, topBound;  
};