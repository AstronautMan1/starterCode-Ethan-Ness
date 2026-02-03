/*
    @author Ethan Ness

    The perspective camera which implements the camera interface for a specific perspective camera
*/

#pragma once

/*
    includes section
*/
#include "camera.h" // camera interface

/// @brief Perspective camera which inherits the public section of the camera interface
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

        vec3 pos; // position of camera

        vec3 U,V,W; // direction camera is looking U is x axis, V is y axis, and W is the z axis

        float focalLength; // focal length is the field of view

        float imagePlane_Width; // width of the image plane

        float imagePlane_Length; // length of the image plane

        int nx;  // x size of the image

        int ny;  // y size of the image

        float leftBound, rightBound, bottomBound, topBound;  // the left, right, top, and bottom bound of the frame buffer
};