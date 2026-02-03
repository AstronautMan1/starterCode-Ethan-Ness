/*

    @author Ethan Ness

    This is the rayTracer.cpp which is a tester for the ray tracer that is implemented inside it has its own function directionToColor
    which takes in a vec3 direction reference and takes a normalized version (scopeing to -1 - 1) then we do the color of the ray
    calculation which takes the normalized and adds 1 to each and then divides by 2 to give a 0 - 1 scope then it is returned.

    Then there is the rayTester function which actually tests the ray tracer with different parameters and exports the image as a png

    then a main function which calls the rayTester function and then returns 0

*/

/*
Includes
*/
#include "framebuffer.h" // framebuffer class
#include "ray.h" // ray class
#include "vec3.h" // vec3 class
#include "camera.h" // camera class
#include "PerspectiveCamera.h" // perspective camera
#include <iostream> // iostream library



/// @brief directionToColor returns the color of the ray by normalizing the ray direction with unit_vector to scope it to -1 to 1 then 
///        we rescope it from 0 - 1 for the color calculation later
/// @param direction vec3 reference which is the direction of the ray
/// @return colorOfRay vec3 is returned the color of the ray
vec3 directionToColor(const vec3 &direction){

    vec3 normalized = unit_vector(direction);

    vec3 colorOfRay = (normalized + vec3(1.0f,1.0f,1.0f) ) * 0.5f;

    return colorOfRay;

}

/// @brief Ray Tester is the actual tester of the ray tracer
void rayTester(){

    Framebuffer fb(200,200); // size of the framebuffer screen

    vec3 position(0,0,-1); // position of the camera
    vec3 U(-15,0,0); // direction on the x axis the camera is looking
    vec3 V(0,1.2,0); // direction on the y axis the camera is looking
    vec3 W(0,0,3.14159); // direction on the z axis the camera is looking
    float focal = 0.0325f; // the field of view of the camera
    float planeWidth = 0.5f; // width of the plane
    float planeHeight = 0.5f; // length of the plane

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // build the perspective camera

    // for loop to get the color for every pixel in the image
    for(int x(0); x < fb.getWidth(); ++x){
        for(int y(0); y < fb.getHeight(); ++y){

            ray R;

            pc.generateRay(x,y,R);

            vec3 color = directionToColor(R.direction());

            fb.setPixelColor(x, y, color);
        }
    }

    fb.exportToPNG("raytracetester.png"); // export to a png

}

/// @brief Main function that just runs the rayTester function
/// @return standard 0 return
int main(){

    rayTester();
    return 0;
}