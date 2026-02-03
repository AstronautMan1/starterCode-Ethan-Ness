/*
    @author Ethan Ness

    Implementation of the perspective camera class
*/

#include "PerspectiveCamera.h" // perspective camera class


/// @brief This is the generate ray function which makes a u and v and it also makes a vec3 direction which we then set the 
///        direction of the ray based on the u and v values and the inputed direction the camera is looking U,V,W and we set the direction of the
///        ray based on those calculations
/// @param i this is the x position of the ray
/// @param j this is the y position of the ray
/// @param R this is a reference to a ray R that is the ray that we generate
void PerspectiveCamera::generateRay (int i, int j, ray &R){

    R.setOrigin(pos);

    
    float u = leftBound + (rightBound - leftBound) * (i + 0.5f) / (float)nx;

    float v = topBound + (bottomBound - topBound) * (j + 0.5f) / (float)ny;

    vec3 direction = -W * focalLength + u * U + v * V;

    R.setDirection(direction);
}