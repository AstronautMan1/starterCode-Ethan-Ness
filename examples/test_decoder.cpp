#include "framebuffer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: ./decode <input_image.png> <output_file_name>" << std::endl;
        return 1;
    }

    std::string inputImage = argv[1];
    std::string outputFile = argv[2];

    Framebuffer fb;
    std::cout << "Loading image..." << std::endl;
    fb.loadFromPNG(inputImage);
    
    std::cout << "Extracting secret data..." << std::endl;
    fb.decodeMessage(outputFile);

    std::cout << "Success! Data saved to " << outputFile << std::endl;
    return 0;
}