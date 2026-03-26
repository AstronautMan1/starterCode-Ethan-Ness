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

        PerspectiveCamera() : Camera() {} // base constructor

        PerspectiveCamera(vec3 position, vec3 valueU, vec3 valueV, vec3 valueW, float focal, float planeWidth, float planeLength, int imageWidth, int imageHeight) 
        : pos(position), U(valueU), V(valueV), W(valueW), focalLength(focal), imagePlane_Width(planeWidth), imagePlane_Length(planeLength), nx(imageWidth), ny(imageHeight) {
            //leftBound = -planeWidth / 2.0f;
            //rightBound = planeWidth / 2.0f;
            //bottomBound = -planeLength / 2.0f;
            //topBound = planeLength / 2.0f;
            updateBounds();
        } // pass in constructor

        void generateRay(float i, float j, ray &r) override; // generate ray override

        void setNX(int width) {nx = width; updateBounds();} // set the width

        void setNY(int height) {ny = height; updateBounds();} // set the height

        int getNX() {return nx;};

        int getNY() {return ny;};

        vec3 getPos() {return pos;};

        vec3 getU() {return U;};

        vec3 getV() {return V;};

        vec3 getW() {return W;};

        float getFocalLength() {return focalLength;};

        float getImagePlane_Width() {return imagePlane_Width;};

        float getImagePlane_Length() {return imagePlane_Length;};

        float getLeftBound() {return leftBound;};

        float getRightBound() {return rightBound;};

        float getBottomBound() {return bottomBound;};

        float getTopBound() {return topBound;};


    private:

        vec3 pos; // position of camera

        vec3 U,V,W; // direction camera is looking U is x axis, V is y axis, and W is the z axis

        float focalLength; // focal length is the field of view

        float imagePlane_Width; // width of the image plane

        float imagePlane_Length; // length of the image plane

        int nx;  // x size of the image

        int ny;  // y size of the image

        float leftBound, rightBound, bottomBound, topBound;  // the left, right, top, and bottom bound of the frame buffer

        void updateBounds() {
            float aspect = (float)nx / (float)ny;

            imagePlane_Length = imagePlane_Width / aspect;

            leftBound = -imagePlane_Width / 2.0f;
            rightBound = imagePlane_Width / 2.0f;
            bottomBound = -imagePlane_Length / 2.0f;
            topBound = imagePlane_Length / 2.0f;
        }
};