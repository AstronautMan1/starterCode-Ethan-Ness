/*
    @author Ethan Ness

    This is the camera interface which is for different camera types it uses the vec3 and ray class for handling rays and vec3 for camera
    positioning
*/

#pragma once

/*
    includes section
*/
#include "vec3.h" // vec3 class
#include "ray.h" // ray class

/// @brief Camera class that is an interface which has two constructors and a default deconstructor and a generateRay function to 
///        make rays which is a pure virtual function to be implemented in other camera types.
class Camera {

    public:

        Camera() : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focalLength(1.0f), imagePlane_Length(0.25f), imagePlane_Width(0.25f), nx(100), ny(100) {}

        Camera(vec3 position, vec3 valueU, vec3 valueV, vec3 valueW, float focal, float planeWidth, float planeLength, int imageWidth, int imageHeight) 
        : pos(position), U(valueU), V(valueV), W(valueW), focalLength(focal), imagePlane_Width(planeWidth), imagePlane_Length(planeLength), nx(imageWidth), ny(imageHeight) {}

        virtual ~Camera() {}

        virtual void generateRay(int i, int j, ray &r) = 0;


    private:

        vec3 pos; // the position of the camera

        vec3 U, V, W; // the direction the camera is looking u is x axis, v is y axis, and w is z axis

        int nx, ny; // the size of the image with nx being x number of pixels and ny being y number of pixels

        float focalLength; // focal length which is like the field of view of the camera

        float imagePlane_Width, imagePlane_Length; // the width and length of the image plane

};