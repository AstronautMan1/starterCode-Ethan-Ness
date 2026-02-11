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
#include "BlinnPhongShader.h" // blinn phong class
#include "Light.h" // light class


/// @brief This is the lambert shader image maker function which makes the image
void BlinnPhongShadeImage(){

    Framebuffer fb(900,600); // framebuffer creation
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

    hitList scene; // make the hitlist for objects

    std::shared_ptr<Shape> s1 = std::make_shared<Sphere>(point3(0,0,-1.0f), 0.5f); // shared pointer of the sphere with a center location of 0,0,-1 and a radius of 0.5

    scene.add(s1); // added the shape to the scene hit list

    Light mainlight(point3(5,5,5), vec3(1,1,1)); // light object at a position of 5,5,5 (x,y,z) and an intensity of 1,1,1 (white light)

    BlinnPhongShader BlueShade(vec3(0.2,0.2,1.0), 150.0f, 0.6); // LambertianShader blueshade it is a blue shader of Lambertian

    // for loop going through pixels
    for (int x = 0; x < fb.getWidth(); ++x){
        for(int y = 0; y < fb.getHeight(); ++y){ 

            float tmax = std::numeric_limits<float>::infinity(); // set tmax as infinity

            ray r; // ray r
            pc.generateRay(x, y, r); // generate the ray at pixel

            hit_record rec; // hit record 

            if(scene.intersect(r, tmin, tmax, rec)){ // if the intersect function returns true 
                vec3 color = BlueShade.rayColor(r,rec,mainlight); // color is equal to rayColor function
                fb.setPixelColor(x,y,color); // set the pixel
            }
            else{ 
                fb.setPixelColor(x,y,vec3(0.5,0.5,0.5)); // if ray doesn't intersect the triangle paint gray
            }
        }
    }


    fb.exportToPNG("ShaderBlinnPhongTest.png"); // png image output of shaderlambert
}

/// @brief The main function that calls LambertShadeImage function
/// @return just returns 0
int main(){

    BlinnPhongShadeImage();
    return 0;
}