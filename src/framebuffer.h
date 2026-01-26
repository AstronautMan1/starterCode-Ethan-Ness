#pragma once

#include "vec3.h"

#include <vector>

class Framebuffer {
    public:
        Framebuffer();

        Framebuffer(int w, int h);

        void Setwidth(int x);

        void Setheight(int x);

        void clearToColor(vec3 c);

        void setPixelColor(int i, int j, vec3 c);

        void exportToPNG(std::string filename);

    private:

        std::vector<vec3> fbstorage;
        int width, height;

};