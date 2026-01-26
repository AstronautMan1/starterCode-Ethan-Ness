#include "framebuffer.h"
#include <iostream>

int main() {
    Framebuffer fb(100, 100);
    vec3 red(1.0f, 0.0f, 0.0f);
    fb.clearToColor(red);
    fb.setPixelColor(50, 50, vec3(0.0f, 1.0f, 0.0f)); // green pixel
    fb.exportToPNG("test_framebuffer.png");
    std::cout << "Framebuffer exported to test_framebuffer.png" << std::endl;
    return 0;
}