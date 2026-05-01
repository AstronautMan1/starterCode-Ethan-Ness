/*
    @author Ethan Ness

    Diffuse Shader testing Diffuse and SubSurface Scattering
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
#include "handleGraphicsArgs.h" // graphics argument handling
#include "BVH.h"
#include "SubSurfaceScatteringShader.h"
#include "EmitterShader.h"
#include <random> // random library

/// @brief this is the random offset for MSAA anti aliasing
/// @return We return the random distribution
float randomOffset() {
    static std::uniform_real_distribution<double> distribution(0.0,1.0); // uniform real distribution of doubles from 0 to 1
    static std::mt19937 generator; // mt19937 RNG
    return distribution(generator); // return the distribution
}



/// @brief This is the interdiffuse function which runs the scene and creates the framebuffer and objects adds them to the scene list and then displays out to a png file
/// @param argc count of passed in arguments from main
/// @param argv array of arguments passed in
void interDiffuse(int argc, char *argv[]){

    sivelab::GraphicsArgs arguments; // make an arguments variable for handling argv arguments
    arguments.process(argc, argv); // run the process function on the arguments passed in

    Framebuffer fb(arguments.width, arguments.height); // make a framebuffer of size width and height
    float aspectRatio = arguments.aspectRatio; // aspect ratio
    int depth = arguments.recursionDepth; // depth 

    vec3 position(0, 1, 4); // camera position
    vec3 U(1,0,0); // Looking U direction 
    vec3 V(0,1,0); // Looking V direction
    vec3 W(0,0,3); // looking W direction
    float focal = 0.2f; // focal size
    float planeHeight = 0.5f; // plane height
    float planeWidth = planeHeight * aspectRatio; // plane width calculation
    float tmin = 0.001f; // set tmin
    
    // total_samples now represents the exact number of rays per pixel
    int total_samples = arguments.rpp; // total samples (rays per pixel)

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // make a perspective camera

    std::vector<std::shared_ptr<Shape>> objects;
    Light mainlight(point3(1.0,0.5,-3), vec3(1,1,1), "pointlight"); // Main Light inside the SSS sphere
    Light secondLight(point3(5,5,5), vec3(0.3,0.3,0.3), "pointlight"); // secondary light for ambient
    Light GreenSSSLight(point3(-1.0f, 3.0f, -3.0f), vec3(1,1,1), "pointlight"); // green light in sphere
    Light BlueSSSLight(point3(-3.0f, 0.5f, -3.0f), vec3(1,1,1), "pointlight"); // blue light in sphere

    // Subsurface Scattered sphere 
    auto SSSSphere = std::make_shared<SubSurfaceShader>(vec3(1.0,0.25,0.25), 5.0f, 0.2f); // parameters are color(albedo), Scattering(sigma_s), Absorption(sigma_a) 
    std::shared_ptr<Shape> SubSurfaceSphere = std::make_shared<Sphere>(point3(1.0f, 0.5, -3.0f), 1.0f, SSSSphere); // position of sphere, radius, shader

    // Ground lambertian shader for the ground sphere
    auto GroundShade = std::make_shared<LambertianShader>(vec3(0.3, 1.0, 0.3));  // albedo color
    std::shared_ptr<Shape> ground = std::make_shared<Sphere>(point3(0, -100.5f, -1.0f), 100.0f, GroundShade); // position, radius, shader

    // Create a Wall plane for a wall
    auto WallShade = std::make_shared<LambertianShader>(vec3(0.7,0.7,0.7)); // grey lambertian shader
    std::shared_ptr<Shape> wall = std::make_shared<Sphere>(point3(0,0,-15), 10.0f, WallShade); // a sphere with wall shade for a wall

    // Create a red Blinn Phong sphere
    auto RedShade = std::make_shared<LambertianShader>(vec3(1.0, 0.2, 0.2)); // red Blinn Phong Shader
    std::shared_ptr<Shape> redSphere = std::make_shared<Sphere>(point3(-1.0f, 0.5, -3.0f), 1.0f, RedShade); // make shared pointer of shape sphere with the red blinn phong shader

    auto SSSBlue = std::make_shared<SubSurfaceShader>(vec3(0.25, 0.25, 1.0), 5.0f, 0.2f);
    std::shared_ptr<Shape> SubSurfaceBlue = std::make_shared<Sphere>(point3(-3.05f, 0.5f, -2.25f), 1.0f, SSSBlue);

    auto SSSGreen = std::make_shared<SubSurfaceShader>(vec3(0.25, 1.0, 0.25), 5.0f, 0.2f);
    std::shared_ptr<Shape> SubsurfaceGreen = std::make_shared<Sphere>(point3(-1.0f, 2.5f, -2.5f), 1.0f, SSSGreen);

    auto mirrorshade = std::make_shared<MirrorShader>(vec3(1,1,1), 1.0f); // color is white for mirror and 1.0 reflectance for perfect mirror
    std::shared_ptr<Shape> mirrorsphere = std::make_shared<Sphere>(point3(1.0f, 2.5f, -2.5f), 1.0f, mirrorshade);

    /*
     Add objects to the objects shape list
    */
    objects.push_back(SubSurfaceSphere); 
    objects.push_back(ground);
    objects.push_back(redSphere);
    objects.push_back(SubSurfaceBlue);
    objects.push_back(SubsurfaceGreen);
    objects.push_back(wall);
    objects.push_back(mirrorsphere);

    std::shared_ptr<bvhNode> sceneBVH = std::make_shared<bvhNode>(objects, 0, objects.size()); // make a scene bvh with the objects passed in

    // For loop using OMP parallel for paralization across all x and y pixels
    #pragma omp parallel for
    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){ 

            vec3 pixel_color(0.0, 0.0, 0.0); // set pixel color to be black

            for (int s = 0; s < total_samples; ++s){ // for samples (rays per pixel count)
                float tmax = std::numeric_limits<float>::infinity(); // set tmax
                ray r;  // make ray r

                // Offset rays within the pixel for anti-aliasing
                float u_offset = randomOffset(); 
                float v_offset = randomOffset(); 

                pc.generateRay(x + u_offset, y + v_offset, r); // generate ray with offsets

                pixel_color += sceneBVH->computeRayColor(r, tmin, tmax, mainlight, vec3(0,0,0), depth); // compute ray color for main light
                pixel_color += sceneBVH->computeRayColor(r, tmin, tmax, secondLight, vec3(0,0,0), depth); // compute ray color for second light
                pixel_color += sceneBVH->computeRayColor(r, tmin, tmax, BlueSSSLight, vec3(0,0,0), depth); // compute ray color for blue light light
                pixel_color += sceneBVH->computeRayColor(r, tmin, tmax, GreenSSSLight, vec3(0,0,0), depth); // compute ray color for green light light

            }

            // Average the accumulated color by the number of samples
            pixel_color /= static_cast<float>(total_samples);
            fb.setPixelColor(x, y, pixel_color);  // set pixel color
        }
    }

    fb.exportToPNG(arguments.outputFileName); // export to png file
}

/// @brief The main function that calls MirrorShaderTest function
/// @return just returns 0
int main(int argc, char *argv[]){

    interDiffuse(argc, argv); // call interdiffuse passing in argc and argv
    return 0; // return 0
}
