/*
    @author Ethan Ness

    This is the framebuffer tester which tests the framebuffer class by just creating some basic images

*/


/*
    Includes Section
*/
#include "framebuffer.h" // framebuffer class
#include <iostream> // iostream library

/// @brief This just creates a red image with the center pixel being green
void redWithCenterGreen(){
    Framebuffer fb(100, 100);
    vec3 red(1.0f, 0.0f, 0.0f);
    fb.clearToColor(red);
    fb.setPixelColor(50, 50, vec3(0.0f, 1.0f, 0.0f)); // green pixel
    fb.exportToPNG("test_framebuffer.png");
    std::cout << "Framebuffer exported to test_framebuffer.png" << std::endl;
}

/// @brief This makes an image with a blue background and a white smiley face
void blueWithWhiteSmile(){

    Framebuffer fb(100,100);
    vec3 blue(0.0f,0.0f,1.0f);
    fb.clearToColor(blue);
    fb.setPixelColor(45,50,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(55,50,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(40,60,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(41,61,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(42,62,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(43,63,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(44,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(45,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(46,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(47,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(48,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(49,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(50,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(51,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(52,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(53,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(54,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(55,64,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(56,63,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(57,62,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(58,61,vec3(1.0f,1.0f,1.0f));
    fb.setPixelColor(59,60,vec3(1.0f,1.0f,1.0f));

    fb.exportToPNG("test_smileFramebuffer.png");
    std::cout << "output smile png file" << std::endl;


}

/// @brief This does a mock US flag image
void USFlag() {

    Framebuffer fb(600,600);
    vec3 Red(1.0f,0.0f,0.0f);
    fb.clearToColor(Red);

    for(int x = 0; x <= 300; ++x){
        for(int y = 0; y <= 300; ++y){
            fb.setPixelColor(x,y,vec3(0.0f,0.0f,1.0f));

        }
    }

    fb.exportToPNG("test_USFlag.png");
    std::cout << "US Flag Output" << std::endl;
}

/// @brief Calls the image functions to make images
/// @return standard 0 return
int main() {

    redWithCenterGreen();
    blueWithWhiteSmile();
    USFlag();
    return 0;
}