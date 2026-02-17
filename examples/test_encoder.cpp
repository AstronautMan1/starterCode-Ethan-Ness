/*

    @author Ethan Ness

    This is the encoder.cpp which is a tester the encoding of messages in a LSB context for a form of steganography. The most of it is the same as the rayTracer tester.
    however it adds the elements needed for steganography adding.

*/

/*
Includes
*/
#include "framebuffer.h" // framebuffer class
#include "ray.h" // ray class
#include "vec3.h" // vec3 class
#include "camera.h" // camera class
#include "PerspectiveCamera.h" // perspective camera
#include <iostream> // iostream library
#include <string> // string library



/// @brief directionToColor returns the color of the ray by normalizing the ray direction with unit_vector to scope it to -1 to 1 then 
///        we rescope it from 0 - 1 for the color calculation later
/// @param direction vec3 reference which is the direction of the ray
/// @return colorOfRay vec3 is returned the color of the ray
vec3 directionToColor(const vec3 &direction){

    vec3 normalized = unit_vector(direction);

    vec3 colorOfRay = (normalized + vec3(1.0f,1.0f,1.0f) ) * 0.5f;

    return colorOfRay;

}

/// @brief 
/// @param secretFile 
/// @param outputFile 
void steg_tester(const std::string &secretFile, const std::string &outputFile, int width, int height){

    Framebuffer fb(width,height); // size of the framebuffer screen

    vec3 position(0,0,-1); // position of the camera
    vec3 U(1,0,0); // direction on the x axis the camera is looking
    vec3 V(0,1,0); // direction on the y axis the camera is looking
    vec3 W(0,0,1); // direction on the z axis the camera is looking
    float focal = 0.0325f; // the field of view of the camera
    float planeWidth = 0.5f; // width of the plane
    float planeHeight = 0.5f; // length of the plane

    PerspectiveCamera pc(position, U, V, W, focal, planeWidth, planeHeight, fb.getWidth(), fb.getHeight()); // build the perspective camera

    // for loop to get the color for every pixel in the image
    for(int x(0); x < fb.getWidth(); ++x){
        for(int y(0); y < fb.getHeight(); ++y){

            ray R;

            pc.generateRay(x,y,R);

            vec3 color = directionToColor(R.direction());

            fb.setPixelColor(x, y, color);
        }
    }

    std::cout << "Embedding the following file: " << secretFile << std::endl; 
    fb.encodeMessage(secretFile); // we encode our message with the file to be used as payload passed in


    std::cout << "Exporting Stegonagraphy image to: " << outputFile << std::endl;
    fb.exportToPNG(outputFile); // We export the image as a png with the name of the png being the name received in

}

/// @brief main function which runs the steg_tester function for steganography
/// @param argc the count of the number of arguments passed
/// @param argv the vector of the arguments passed in
/// @return we return 1 if less then 3 args return 0 otherwise
int main(int argc, char* argv[]){

    if (argc < 5){ // if less then 5 arguments passed in we throw errors
        std::cout << "Usage: ./test_encoder <file_to_hide> <output_png_name> <image_width> <image_height>" << std::endl;
        std::cout << "Example: ./test_encoder secret.zip encoded_image.png 400 400" << std::endl;
        return 1;
    }

    std::string secret = argv[1]; // our secret file to use as payload is the first argument
    std::string output = argv[2]; // the output file name is the second argument
    int width = std::stoi(argv[3]); // width of the image
    int height = std::stoi(argv[4]); // height of the image

    steg_tester(secret, output, width, height); // call steg_tester passing in the secret file and output file
    return 0;
}