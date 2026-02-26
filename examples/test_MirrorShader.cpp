/*
    @author Ethan Ness

    Mirror shade tester which tests the new mirror shader
*/

/*
    Includes section
*/
#include "PerspectiveCamera.h" // perspective camera class
#include "framebuffer.h" // framebuffer class
#include "hitList.h" // hit list class
#include "Sphere.h" // sphere class
#include "triangle.h" // triangle class
#include "MirrorShader.h" // mirror shader class
#include "LambertianShader.h" // lambertian shader class
#include "BlinnPhongShader.h" // blinn phong shader class
#include "Light.h" // light class
#include "handleGraphicsArgs.h" // graphics handling
#include <random> // random library

/// @brief this is the random offset for MSAA anti aliasing
/// @return We return the random distribution
float randomOffset() {
    static std::uniform_real_distribution<double> distribution(0.0,1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

/// @brief Create an image with mirror reflection using depth-based recursion
void MirrorShaderTest(int argc, char *argv[]){

    sivelab::GraphicsArgs arguments;
    arguments.process(argc, argv);

    Framebuffer fb(arguments.width, arguments.height); // framebuffer creation
    float aspectRatio = arguments.aspectRatio;
    std::string outputNameFile = arguments.outputFileName;
    int depth = arguments.recursionDepth;

    vec3 position(0, 1, 4); // position of camera
    vec3 U(1,0,0); // x axis direction camera is looking
    vec3 V(0,1,0); // y axis direction camera is looking
    vec3 W(0,0,3); // z axis direction camera is looking
    float focal = 0.3f; // focal size
    float planeHeight = 0.5f; // plane height
    float planeWidth = planeHeight * aspectRatio; // plane width
    float tmin = 0.001f; // initialize tmin
    int rpp_NSquare = arguments.rpp; // rpp NSquare - 4x4 antialiasing

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // make the persepective camera

    hitList scene; // make the hitlist for objects

    Light mainlight(point3(2, 2, 0), vec3(1, 1, 1)); // light object at position 5,5,5 with white light color


    // Create a red Blinn Phong sphere
    auto RedShade = std::make_shared<BlinnPhongShader>(vec3(1.0, 0.2, 0.2), 32.0f, 0.5f); // red Blinn Phong Shader
    std::shared_ptr<Shape> redSphere = std::make_shared<Sphere>(point3(-1.2f, 1.0, -3.0f), 1.0f, RedShade); // make shared pointer of shape sphere with the red blinn phong shader
    scene.add(redSphere); // add the red sphere to hit list scene

    // Create a perfect mirror shader sphere
    auto mirrorShade = std::make_shared<MirrorShader>(vec3(1.0,1.0,1.0), 1.0f); // mirror shader with a color of white and a 1.0 intensity perfect mirror
    std::shared_ptr<Shape> mirrorSphere = std::make_shared<Sphere>(point3(1.2f, 1.1, -4.0f), 1.1f, mirrorShade); // a mirror sphere with the mirror shader
    scene.add(mirrorSphere); // add mirror sphere

    // Create a ground plane just a sphere that is green
    auto GroundShade = std::make_shared<LambertianShader>(vec3(0.2, 1.0, 0.2)); // lambertian green shader for ground
    std::shared_ptr<Shape> ground = std::make_shared<Sphere>(point3(0, -100.5f, -1.0f), 100.0f, GroundShade); // green ground sphere
    scene.add(ground); // add the sphere to the hitlist

    /*
    // creating a sky plane which is also just a sphere and is blue
    auto SkyShade = std::make_shared<LambertianShader>(vec3(0.4,0.4,1.0)); // blue lambertian shader for sky
    std::shared_ptr<Shape> sky = std::make_shared<Sphere>(point3(0,80.5f,-3.0f), 90.0f, SkyShade); // blue sphere for sky
    scene.add(sky); // add sky sphere
    */

    // for loop going through pixels
    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){ 

            vec3 color(0.0, 0.0, 0.0); // reset color

            // for loop for MSAA anti aliasing
            for (int p = 0; p < rpp_NSquare; ++p){
                for (int q = 0; q < rpp_NSquare; ++q){

                    float tmax = std::numeric_limits<float>::infinity(); // set tmax as infinity
                    ray r; // ray r

                    float pOffset = (p + randomOffset() / rpp_NSquare); // p offset
                    float qOffset = (q + randomOffset() / rpp_NSquare); // q offset

                    pc.generateRay(x + pOffset, y + qOffset, r); // generate ray with p and q offset

                    // Use max depth of 5 for mirror recursion and background color of black (blue sphere and green sphere handle background already)
                    color += scene.computeRayColor(r, tmin, tmax, mainlight, vec3(0.5,0.7,1.0), depth);
                }
            }

            color = color / (rpp_NSquare * rpp_NSquare); // color is color / rpp_NSquare * itself

            fb.setPixelColor(x, y, color); // set pixel color
        }
    }

    fb.exportToPNG(arguments.outputFileName); // png image output
}

/// @brief The main function that calls MirrorShaderTest function
/// @return just returns 0
int main(int argc, char *argv[]){

    MirrorShaderTest(argc, argv);
    return 0;
}
