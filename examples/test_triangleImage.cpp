/*
    @author Ethan Ness

    Triangle image tester

*/

/*
    Includes Section
*/
#include "framebuffer.h" // framebuffer class
#include "ray.h" // ray class
#include "vec3.h" // vec3 class
#include "camera.h" // camera class
#include "PerspectiveCamera.h" // perspective camera class
#include "shape.h" // shape class
#include "triangle.h" // triangle class
#include <iostream> // iostream library


/// @brief This handles the making of a triangle image
void triangleImage(){

    Framebuffer fb(500,500); // framebuffer creation
    float aspectRatio = static_cast<float>(fb.getWidth()) / static_cast<float>(fb.getHeight()); // set up aspect ratio calculation

    vec3 position(0,0,-1); // position of camera
    vec3 U(1,0,0); // x axis direction camera is looking
    vec3 V(0,1,0); // y axis direction camera is looking
    vec3 W(0,0,1); // z axis direction camera is looking
    float focal = 0.05f; // focal size
    float planeHeight = 0.5f; // plane height
    float planeWidth = planeHeight * aspectRatio; // plane width
    float tmin = 0.001f; // initialize tmin

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // making the perspective camera

    std::shared_ptr<Shape> s = std::make_shared<Triangle>(vec3(2.0,4.0,-2.0), vec3(4.0,2.0,-2.0), vec3(0.0,2.0,-2.0)); // shared pointer of the triangle

    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){

            float tmax = std::numeric_limits<float>::infinity(); // set tmax

            ray r; // ray r
            pc.generateRay(x, y, r); // generate the ray

            if(s->intersect(r, tmin, tmax)){
                fb.setPixelColor(x,y, vec3(1.0,0,0)); // if ray intersects the triangle paint red
            }
            else{
                fb.setPixelColor(x,y,vec3(0,0,1.0)); // if ray doesn't intersect the triangle paint blue
            }
        }
    }

    fb.exportToPNG("test_triangleimage.png"); // export to a png file

}

/// @brief This is the main that calls the triangle image generator
/// @return just returns 0 when finished
int main(){

    triangleImage();

    return 0;

}