#include "framebuffer.h"

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

    for (auto idx=0u; idx<fbstorage.size(); ++idx){
        fbstorage[idx] = c;
    }

}

void Framebuffer::setPixelColor(int i, int j){


}

void Framebuffer::exportToPNG(std::string filename){


}