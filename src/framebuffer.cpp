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

            // Use round() to prevent 254.99 becoming 254
            png::byte r = static_cast<png::byte>(std::round(std::clamp(c.x() * 255.0f, 0.0f, 255.0f)));
            png::byte g = static_cast<png::byte>(std::round(std::clamp(c.y() * 255.0f, 0.0f, 255.0f)));
            png::byte b = static_cast<png::byte>(std::round(std::clamp(c.z() * 255.0f, 0.0f, 255.0f)));
            
            imData[j][i] = png::rgb_pixel(r, g, b);
        }
    }
    imData.write(filename);
}


void Framebuffer::encodeMessage(const std::string &messageFile) {
    std::ifstream file(messageFile, std::ios::binary);
    if (!file) return; // Add error check
    std::vector<unsigned char> data((std::istreambuf_iterator<char>(file)), {});
    file.close();

    uint32_t fileSize = static_cast<uint32_t>(data.size());
    int pixelIdx = 0;
    int channelIdx = 0;

    // Helper to embed 1 bit
    auto embedBit = [&](int bit) {
        if (pixelIdx >= fbstorage.size()) return;
        
        // Fix typo: static_cast and added rounding for precision
        int val = static_cast<int>(std::round(fbstorage[pixelIdx][channelIdx] * 255.0f));
        
        val = (val & ~1) | bit;
        fbstorage[pixelIdx][channelIdx] = val / 255.0f; // Missing semicolon fixed

        if (++channelIdx > 2) {
            channelIdx = 0;
            pixelIdx++;
        }
    };

    // --- STEP 1: Embed 32-bit Header ---
    for (int i = 31; i >= 0; --i) {
        embedBit((fileSize >> i) & 1);
    }

    // --- STEP 2: Embed Payload ---
    for (unsigned char byte : data) {
        for (int i = 7; i >= 0; --i) {
            embedBit((byte >> i) & 1);
        }
    }
}

void Framebuffer::decodeMessage(const std::string &outputFile) {
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) return;

    uint32_t fileSize = 0;
    int pixelIdx = 0;
    int channelIdx = 0;

    // 1. Extract 32-bit header
    for (int i = 31; i >= 0; --i) {
        int val = static_cast<int>(std::round(fbstorage[pixelIdx][channelIdx] * 255.0f));
    
    // Logic change: Use |= and bit shifting to match the encoder's order
        if (val & 1) {
            fileSize |= (1U << i);
        }

        if (++channelIdx > 2) { channelIdx = 0; pixelIdx++; }
    }

    // 2. Extract payload with safety bounds
    unsigned char currentByte = 0;
    int bitCount = 0;
    
    // Safety check: Don't try to extract more data than the image could possibly hold
    uint32_t maxPossibleBytes = (uint32_t)((fbstorage.size() * 3 - 32) / 8);
    if (fileSize > maxPossibleBytes) {
        std::cerr << "Error: Decoded file size (" << fileSize << ") exceeds image capacity!" << std::endl;
        return;
    }

    for (uint32_t i = 0; i < fileSize * 8; ++i) {
        if (pixelIdx >= fbstorage.size()) break;

        int val = static_cast<int>(std::round(fbstorage[pixelIdx][channelIdx] * 255.0f));
        currentByte = (currentByte << 1) | (val & 1);
        bitCount++;

        if (bitCount == 8) {
            outFile.put(currentByte);
            currentByte = 0;
            bitCount = 0;
        }

        if (++channelIdx > 2) { channelIdx = 0; pixelIdx++; }
    }
    outFile.close();
}

void Framebuffer::loadFromPNG(std::string filename) {
    png::image<png::rgb_pixel> image(filename);
    
    // Update dimensions to match the loaded file
    width = image.get_width();
    height = image.get_height();
    
    // assign() is good because it resizes AND clears the old data
    fbstorage.assign(width * height, vec3(0, 0, 0));

    for (int y = 0; y < height; ++y) {
        // Access the row once for better performance
        png::image<png::rgb_pixel>::pixbuf::row_type row = image.get_row(y);
        for (int x = 0; x < width; ++x) {
            png::rgb_pixel pixel = row[x];

            // Linear index calculation: (row * width) + column
            fbstorage[y * width + x] = vec3(
                pixel.red / 255.0f,
                pixel.green / 255.0f,
                pixel.blue / 255.0f
            );
        }
    }
}