/*
    @author Ethan Ness

    test file to test the making of multiple shapes in an image space
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
#include "triangle.h" // triangle class
#include "hitList.h" // hit list class
#include <iostream> // iostream library

/// @brief This handles the making of a multiple shape image
void multipleShapeImage(){

    Framebuffer fb(900,600); // framebuffer creation
    hitList listOfObjects; // list of objects
    float aspectRatio = static_cast<float>(fb.getWidth()) / static_cast<float>(fb.getHeight()); // set up aspect ratio calculation


    vec3 position(0,0,15); // position of camera
    vec3 U(1,0,0); // x axis direction camera is looking
    vec3 V(0,1,0); // y axis direction camera is looking
    vec3 W(0,0,1); // z axis direction camera is looking
    float focal = 1.0f; // focal size
    float planeHeight = 0.5f; // plane height
    float planeWidth = planeHeight * aspectRatio; // plane width
    float tmin = 0.001f; // initialize tmin

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // making the perspective camera

    std::shared_ptr<Shape> s1 = std::make_shared<Triangle>(vec3(2.0,4.0,-2.0), vec3(4.0,2.0,-2.0), vec3(0.0,2.0,-2.0)); // shared pointer of the triangle

    std::shared_ptr<Shape> s2 = std::make_shared<Sphere>(point3(4,0,-2.0f), 0.3f); // shared pointer of the sphere with a center location of 0,0,-2 and a radius of 0.6

    listOfObjects.add(s1); // add shape 1 to list
    listOfObjects.add(s2); // add shape 2 to list

    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){

            float tmax = std::numeric_limits<float>::infinity(); // set tmax

            ray r; // ray r
            pc.generateRay(x, y, r); // generate the ray

            if(listOfObjects.intersect(r, tmin, tmax)){
                fb.setPixelColor(x,y, vec3(1.0,0,0)); // if ray intersects the triangle paint red
            }
            else{
                fb.setPixelColor(x,y,vec3(0,0,1.0)); // if ray doesn't intersect the triangle paint blue
            }
        }
    }

    fb.exportToPNG("test_multipleShapes.png"); // export to a png file
    
}


/// @brief This is the main to call multipleShapeImage function
/// @return It just returns 0 when finished
int main(){

    multipleShapeImage();
    return 0;
}