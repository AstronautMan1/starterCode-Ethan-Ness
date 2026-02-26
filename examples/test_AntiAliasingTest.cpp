/*
    @author Ethan Ness

    An implementation of a anti aliasing for the image generation
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
#include "handleGraphicsArgs.h" // graphics argument handling
#include <random> // random library

/// @brief This is a random offset funtion which gives a random offset for our pixels for anti aliasing generation
/// @return We return the float random distribution
float randomOffset() {

    static std::uniform_real_distribution<double> distribution(0.0,1.0); // random distribution from 0.0 - 1.0
    static std::mt19937 generator; // mt19937 generator 
    return distribution(generator); // return the distribution range with that generator
}


/// @brief This is the lambert shader image maker function which makes the image with anti aliasing
void LambertianAntiAliasing(int argc, char *argv[]){

    sivelab::GraphicsArgs arguments;
    arguments.process(argc, argv);

    Framebuffer fb(arguments.width, arguments.height); // framebuffer creation
    float aspectRatio = arguments.aspectRatio;
    std::string outputNameFile = arguments.outputFileName;
    int depth = arguments.recursionDepth;
    hitList listOfObjects; // list of objects


    vec3 position(0,0,5); // position of camera
    vec3 U(1,0,0); // x axis direction camera is looking
    vec3 V(0,1,0); // y axis direction camera is looking
    vec3 W(0,0,1); // z axis direction camera is looking
    float focal = 1.0f; // focal size
    float planeHeight = 0.5f; // plane height
    float planeWidth = planeHeight * aspectRatio; // plane width
    float tmin = 0.001f; // initialize tmin
    int rpp_NSquare = arguments.rpp; // rpp NSquare breaking pixel into 4x4 subsections

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // making the perspective camera

    hitList scene; // make the hitlist for objects

    Light mainlight(point3(1,0,-1), vec3(1,1,1)); // light object at a position of 5,5,5 (x,y,z) and an intensity of 1,1,1 (white light)

    auto BlueShade = std::make_shared<LambertianShader>(vec3(0.2,0.2,1.0)); // LambertianShader blueshade it is a blue shader of Lambertian

    std::shared_ptr<Shape> s1 = std::make_shared<Sphere>(point3(0,0,-1.0f), 0.5f, BlueShade); // shared pointer of the sphere with a center location of 0,0,-1 and a radius of 0.5

    scene.add(s1); // added the shape to the scene hit list

    // for loop going through pixels with another for loop for antialiasing
    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){ 

            vec3 color(0.0,0.0,0.0); // reset the color for the anti aliasing handling

            for (int p = 0; p < rpp_NSquare; ++p){
                for (int q = 0; q < rpp_NSquare; ++q){

                    float tmax = std::numeric_limits<float>::infinity(); // set tmax as infinity
                    ray r; // ray r

                    float pOffset = (p + randomOffset() / rpp_NSquare); // the offset for p
                    float qOffset = (q + randomOffset() / rpp_NSquare); // the offset for q

                    pc.generateRay(x+p, y+q, r); // generate a ray with p adn q offset added to the pixel

                    color += scene.computeRayColor(r, tmin, tmax, mainlight, vec3(0.5,0.5,0.5), depth); // compute the ray color with that anti aliasing
                }
            }

            color = color / (rpp_NSquare * rpp_NSquare); // color of the pixel is color divided by NSquare * NSquare

            fb.setPixelColor(x,y,color); // set the pixel color
        }
    }


    fb.exportToPNG(arguments.outputFileName); // png image output of shaderlambert with anti aliasing
}

/// @brief The main function that calls LambertShadeImage function
/// @return just returns 0
int main(int argc, char *argv[]){

    LambertianAntiAliasing(argc, argv);
    return 0;
}