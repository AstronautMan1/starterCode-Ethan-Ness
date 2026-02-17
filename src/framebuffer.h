/*
    @author Ethan Ness

    This is the framebuffer class which handles the the height and width of the image and exporting to a png image 
    needs to be updated for any image file type.
*/

#pragma once

/*
    Includes section
*/
#include "vec3.h" // vec3 class
#include <vector> // vector library

/// @brief The framebuffer class which has seters and geters for the width and height of the image. It also has a setpixelcolor function
///        for setting the color of an individual pixel and a clear to color function to clear to a single color and a export to PNG to 
///        export the image as a png file.
class Framebuffer {
    public:
        Framebuffer(); // constructor

        Framebuffer(int w, int h); // input constructor

        void Setwidth(int x); // set width

        void Setheight(int y); // set height

        int getWidth(); // get width

        int getHeight(); // get height

        void clearToColor(vec3 c); // clear to a color

        void setPixelColor(int i, int j, vec3 c); // set the pixel at (i,j) to a color

        void exportToPNG(std::string filename); // export to a png

    private:

        std::vector<vec3> fbstorage; // storage of the framebuffer
        int width, height; // width and height of the framebuffer

};