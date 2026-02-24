/*
    @author Ethan Ness

    This is a tester for lambertian shading

*/

/*
    Includes section
*/
#include "PerspectiveCamera.h" // perspective camera class
#include "framebuffer.h" // framebuffer class
#include "hitList.h" // hit list class
#include "Sphere.h" // sphere class
#include "triangle.h" // triangle class
#include "LambertianShader.h" // lambertianShader Class
#include "Light.h" // light class
#include "handleGraphicsArgs.h" // graphics arguments class


/// @brief This is the lambert shader image maker function which makes the image
void LambertShadeImage(int argc, char *argv[]){

    sivelab::GraphicsArgs arguments;
    arguments.process(argc, argv);

    Framebuffer fb(arguments.width,arguments.height); // framebuffer creation
    hitList listOfObjects; // list of objects
    float aspectRatio = arguments.aspectRatio;
    std::string outputNameFile = arguments.outputFileName;
    int depth = arguments.recursionDepth;

    vec3 position(0,0,5); // position of camera
    vec3 U(1,0,0); // x axis direction camera is looking
    vec3 V(0,1,0); // y axis direction camera is looking
    vec3 W(0,0,1); // z axis direction camera is looking
    float focal = 1.0f; // focal size
    float planeHeight = 0.5f; // plane height
    float planeWidth = planeHeight * aspectRatio; // plane width
    float tmin = 0.001f; // initialize tmin

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // making the perspective camera

    hitList scene; // make the hitlist for objects

    Light mainlight(point3(5,5,5), vec3(1,1,1)); // light object at a position of 5,5,5 (x,y,z) and an intensity of 1,1,1 (white light)

    auto BlueShade = std::make_shared<LambertianShader>(vec3(0.2,0.2,1.0)); // LambertianShader blueshade it is a blue shader of Lambertian

    std::shared_ptr<Shape> s1 = std::make_shared<Sphere>(point3(0,0,-1.0f), 0.5f, BlueShade); // shared pointer of the sphere with a center location of 0,0,-1 and a radius of 0.5

    scene.add(s1); // added the shape to the scene hit list

    // for loop going through pixels
    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){ 

            float tmax = std::numeric_limits<float>::infinity(); // set tmax as infinity
            ray r; // ray r
            pc.generateRay(x, y, r); // generate the ray at pixel

            vec3 color = scene.computeRayColor(r,tmin, tmax, mainlight, vec3(0.5,0.5,0.5), depth);
            fb.setPixelColor(x,y,color);
        }
    }


    fb.exportToPNG(outputNameFile); // png image output of shaderlambert
}

/// @brief The main function that calls LambertShadeImage function
/// @return just returns 0
int main(int argc, char *argv[]){

    LambertShadeImage(argc, argv);
    return 0;
}