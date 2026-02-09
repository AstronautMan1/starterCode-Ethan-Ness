/*
    @author Ethan Ness

    test file to test the making of multiple triangles in an image space
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



void multipleTriangles(){

    Framebuffer fb(200,200); // framebuffer creation
    hitList listOfObjects; // list of objects
    float aspectRatio = static_cast<float>(fb.getWidth()) / static_cast<float>(fb.getHeight()); // set up aspect ratio calculation


    vec3 position(0,0,5); // position of camera
    vec3 U(1,0,0); // x axis direction camera is looking
    vec3 V(0,1,0); // y axis direction camera is looking
    vec3 W(0,0,1); // z axis direction camera is looking
    float focal = 1.0f; // focal size
    float planeHeight = 0.5f; // plane height
    float planeWidth = planeHeight * aspectRatio; // plane width
    float tmin = 0.001f; // initialize tmin

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // making the perspective camera

    std::shared_ptr<Shape> t1 = std::make_shared<Triangle>(vec3(-1.2,-0.2,-7), vec3(0.8,-0.5,-5), vec3(0.9,0,-5)); // shared pointer of the triangle 1

    std::shared_ptr<Shape> t2 = std::make_shared<Triangle>(vec3(0.773205,-0.93923, -7), vec3(0.0330127,0.94282,-5), vec3(-0.45,0.779423,-5)); // shared pointer of the triangle 2

    std::shared_ptr<Shape> t3 = std::make_shared<Triangle>(vec3(0.426795,1.13923,-7), vec3(-0.833013,-0.44282,-5), vec3(-0.45,-0.779423,-5)); // shared pointer of the triangle 3

    listOfObjects.add(t1);
    listOfObjects.add(t2);
    listOfObjects.add(t3);

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

    fb.exportToPNG("test_multipleTriangles.png"); // export to a png file
}

int main(){

    multipleTriangles();

    return 0;
}