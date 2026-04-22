/*
    @author Ethan Ness

    Diffuse Shader testing inter Diffuse Shading and hard shadows
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
#include <random> // random library

/// @brief this is the random offset for MSAA anti aliasing
/// @return We return the random distribution
float randomOffset() {
    static std::uniform_real_distribution<double> distribution(0.0,1.0);
    static std::mt19937 generator;
    return distribution(generator);
}



/// @brief 
/// @param argc 
/// @param argv 
void interDiffuse(int argc, char *argv[]){

    sivelab::GraphicsArgs arguments;
    arguments.process(argc, argv);

    Framebuffer fb(arguments.width, arguments.height); 
    float aspectRatio = arguments.aspectRatio;
    int depth = arguments.recursionDepth;

    vec3 position(0, 1, 4); 
    vec3 U(1,0,0); 
    vec3 V(0,1,0); 
    vec3 W(0,0,3); 
    float focal = 0.2f; 
    float planeHeight = 0.5f; 
    float planeWidth = planeHeight * aspectRatio; 
    float tmin = 0.001f; 
    
    // total_samples now represents the exact number of rays per pixel
    int total_samples = arguments.rpp; 

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight());

    std::vector<std::shared_ptr<Shape>> objects;
    Light mainlight(point3(5.0, 5.0, 5.0), vec3(1, 1, 1), "pointlight");

    auto SSSSphere = std::make_shared<SubSurfaceShader>(vec3(1.0,0.7,0.6), 1.5f, 0.2f); 
    std::shared_ptr<Shape> SubSurfaceSphere = std::make_shared<Sphere>(point3(1.0f, 0.5, -3.0f), 1.0f, SSSSphere); 

    auto GroundShade = std::make_shared<LambertianShader>(vec3(0.3, 1.0, 0.3)); 
    std::shared_ptr<Shape> ground = std::make_shared<Sphere>(point3(0, -100.5f, -1.0f), 100.0f, GroundShade); 

    // Create a Wall plane for a wall
    auto WallShade = std::make_shared<LambertianShader>(vec3(0.7,0.7,0.7)); // grey lambertian shader
    std::shared_ptr<Shape> wall = std::make_shared<Sphere>(point3(0,0,-15), 10.0f, WallShade); // a sphere with wall shade for a wall

    // Create a red Blinn Phong sphere
    auto RedShade = std::make_shared<BlinnPhongShader>(vec3(1.0, 0.2, 0.2), 32.0f, 0.5f); // red Blinn Phong Shader
    std::shared_ptr<Shape> redSphere = std::make_shared<Sphere>(point3(-1.0f, 0.5, -3.0f), 1.0f, RedShade); // make shared pointer of shape sphere with the red blinn phong shader

    objects.push_back(SubSurfaceSphere);
    objects.push_back(ground);
    objects.push_back(redSphere);
    objects.push_back(wall);

    std::shared_ptr<bvhNode> sceneBVH = std::make_shared<bvhNode>(objects, 0, objects.size());

    #pragma omp parallel for
    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){ 

            vec3 pixel_color(0.0, 0.0, 0.0);

            for (int s = 0; s < total_samples; ++s){
                float tmax = std::numeric_limits<float>::infinity();
                ray r; 

                // Offset rays within the pixel for anti-aliasing
                float u_offset = randomOffset(); 
                float v_offset = randomOffset(); 

                pc.generateRay(x + u_offset, y + v_offset, r); 

                pixel_color += sceneBVH->computeRayColor(r, tmin, tmax, mainlight, vec3(0,0,0), depth);
            }

            // Average the accumulated color by the number of samples
            pixel_color /= static_cast<float>(total_samples);
            fb.setPixelColor(x, y, pixel_color); 
        }
    }

    fb.exportToPNG(arguments.outputFileName);
}

/// @brief The main function that calls MirrorShaderTest function
/// @return just returns 0
int main(int argc, char *argv[]){

    interDiffuse(argc, argv);
    return 0;
}
