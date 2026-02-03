/*
    @author Ethan Ness

    The implementation of the framebuffer class.
*/

/*
    includes section
*/
#include "framebuffer.h" // framebuffer class
#include "png++/png.hpp" // png requirements for making png images
#include <algorithm> // algorithm library

/// @brief basic constructor
Framebuffer::Framebuffer()
    : width(100), height(100), fbstorage(width*height)
{
}

/// @brief contructor with arguments
Framebuffer::Framebuffer(int w, int h)
    : width(w), height(h), fbstorage(width*height)
{
}

/// @brief The seter for height
/// @param h for the height
void Framebuffer::Setheight(int h){

    height = h;
}

/// @brief Setter for the width
/// @param w for the width
void Framebuffer::Setwidth(int w){

    width = w;
}

/// @brief Getter for the height
/// @return returns the height
int Framebuffer::getHeight(){

    return height;
}

/// @brief Getter for the width
/// @return returns the width
int Framebuffer::getWidth(){

    return width;
}

/// @brief Clears the image to a solid color
/// @param c takes in a vec3 color c which is the color of the screen in (r,g,b) format
void Framebuffer::clearToColor(vec3 c){

    std::fill(fbstorage.begin(), fbstorage.end(), c);

}

/// @brief This sets the color of a specific pixel
/// @param i the x value of the pxiel on the screen
/// @param j the y value of the pixel on the screen
/// @param c the color the pixel will be set to
void Framebuffer::setPixelColor(int i, int j, vec3 c){

    if (i >= 0 && i < width && j >= 0 && j < height) {
        int index = j * width + i;
        fbstorage[index] = c;
    }

}

/// @brief This exports the framebuffer to a png image
/// @param filename the name of the png image
void Framebuffer::exportToPNG(std::string filename){

    png::image< png::rgb_pixel > imData(width, height);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int index = j * width + i;
            vec3 c = fbstorage[index];
            png::byte r = static_cast<png::byte>(std::clamp(c.x() * 255.0f, 0.0f, 255.0f));
            png::byte g = static_cast<png::byte>(std::clamp(c.y() * 255.0f, 0.0f, 255.0f));
            png::byte b = static_cast<png::byte>(std::clamp(c.z() * 255.0f, 0.0f, 255.0f));
            imData[j][i] = png::rgb_pixel(r, g, b);
        }
    }
    imData.write(filename);

}