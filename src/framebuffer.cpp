#include "framebuffer.h"
#include "png++/png.hpp"
#include <algorithm>

Framebuffer::Framebuffer()
    : width(100), height(100), fbstorage(width*height)
{
}

Framebuffer::Framebuffer(int w, int h)
    : width(w), height(h), fbstorage(width*height)
{
}

void Framebuffer::Setheight(int h){

    height = h;
}

void Framebuffer::Setwidth(int w){

    width = w;
}

void Framebuffer::clearToColor(vec3 c){

    std::fill(fbstorage.begin(), fbstorage.end(), c);

}

void Framebuffer::setPixelColor(int i, int j, vec3 c){

    if (i >= 0 && i < width && j >= 0 && j < height) {
        int index = j * width + i;
        fbstorage[index] = c;
    }

}

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