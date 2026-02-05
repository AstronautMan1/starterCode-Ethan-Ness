/*
    @author Ethan Ness

    test file to test the making of spheres in an image space
*/


/*
    Includes Section
*/
#include "framebuffer.h" // Framebuffer class
#include "ray.h" // Ray Class
#include "vec3.h" // Vec3 Class
#include "camera.h" // Camera Class
#include "PerspectiveCamera.h" // Perspective Camera
#include "Shape.h" // shape class
#include "Sphere.h" // sphere class
#include <iostream> // iostream library


/*
    nx / ny = image plane width / image plane height for right aspect ratio
*/


/// @brief This is the function that handles the making of a framebuffer and making a camera and a sphere than creating the image into a png
void sphereimage(){

    Framebuffer fb(500,500); // framebuffer creation

    vec3 position(0,0,-1); // position of camera
    vec3 U(1,0,0); // x axis direction camera is looking
    vec3 V(0,1,0); // y axis direction camera is looking
    vec3 W(0,0,1); // z axis direction camera is looking
    float focal = 0.1f; // focal size
    float planeWidth = 0.5f; // plane width
    float planeHeight = 0.5f; // plane height

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // making the perspective camera

    std::shared_ptr<Shape> s = std::make_shared<Sphere>(point3(0,0,-2.0f), 0.6f); // shared pointer of the sphere with a center location of 0,0,-2 and a radius of 0.6

    // for loop to go through the whole framebuffer
    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){

            ray r; // ray r
            pc.generateRay(x, y, r); // generate the ray

            if(s->intersect(r)){
                fb.setPixelColor(x,y, vec3(1.0,0,0)); // if ray intersects the sphere paint red
            }
            else{
                fb.setPixelColor(x,y,vec3(0,0,1.0)); // if ray doesn't intersect the sphere paint blue
            }
        }
    }

    fb.exportToPNG("test_sphereimage.png"); // export to a png file

}


/// @brief the main function to run the sphere image function
/// @return just returns 0
int main(){

    sphereimage();

    return 0;

}