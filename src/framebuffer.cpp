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


/*
    Summary of the LSB encoding and decoding

    encoding: message bytes -> extracts bits --> embed the buts in LSB of sequential color channels

    header ecoding: first 32 channels are for storing the message file size (header) later for decoding

    Decoding: we read first 32 channels for file size -> read file size in bits -> then reconstruct the bytes from the bits

    Storage: we use floating point (0.0-1.0) for normalized colors but have to convert them to 0-255 for png color handling and bit manipulation
*/


/// @brief This encodes a message to an image for steganography hiding
/// @param messageFile the name of the message file we are using as payload
void Framebuffer::encodeMessage(const std::string &messageFile) {

    std::ifstream file(messageFile, std::ios::binary); // loads the message file in binary form
    if (!file) return; // if we can't make a file in binary exit

    std::vector<unsigned char> data((std::istreambuf_iterator<char>(file)), {}); // load the entire file into a vector of 8 bit bytes each element in vector represents 8 bits 
    file.close(); // close file 

    uint32_t fileSize = static_cast<uint32_t>(data.size()); // the number of bytes in the message file
    int pixelIdx = 0; // pixel index
    int channelIdx = 0; // channel index

    // embedbit function in encodeMessage function which adds the LSB to the next color channel
    auto embedBit = [&](int bit) {

        if (pixelIdx >= fbstorage.size()) return; // if the idex is greater then framebuffer size exit
        

        int val = static_cast<int>(std::round(fbstorage[pixelIdx][channelIdx] * 255.0f)); // go from floating point 0 - 1 to 0 - 255 and round up so we don't lose our LSB 
        
        val = (val & ~1) | bit; // makes the last bit of the color channel a 0 bit then we plug in the message bit of 0 or 1 in its place with the | bit (example if val from that pixels color channel is 173 10101101 and the bit for message is 0 it turns to 172 10101100)
        fbstorage[pixelIdx][channelIdx] = val / 255.0f; // turns modified color back to floating point and saves it in the framebuffer

        if (++channelIdx > 2) { // if we are outside the color channel 
            channelIdx = 0; // reset channel index
            pixelIdx++; // add 1 to the pixel index
        }
    };

    for (int i = 31; i >= 0; --i) { // encode the header
        embedBit((fileSize >> i) & 1); // we loop from 31 down to 0 and shift the file size right by i then extract the bit at position i and each but goes into the next color channel (32 channels total ~11 pixels) (example if file size is 5 then binary 00000101 is embeded)
    }

    
    for (unsigned char byte : data) {
        for (int i = 7; i >= 0; --i) { 
            embedBit((byte >> i) & 1); // loop from bit 7 to bit 0 and extract each bit and embed it sequentially
        }
    }
}

/// @brief This decodes the message from the image and we output that to a new filename for the output
/// @param outputFile the name of the new file from the decoded payload
void Framebuffer::decodeMessage(const std::string &outputFile) {

    std::ofstream outFile(outputFile, std::ios::binary); // creates our output file and tells the data written to it should be binary not text
    if (!outFile) return; // if the file isn't created properly return

    uint32_t fileSize = 0; // file size tracker
    int pixelIdx = 0; // pixelindex for which pixel we are looking at
    int channelIdx = 0; // channel index to show if we are looking at the red, blue, or green channel

    // We extract the 32 bit header from the encoded image going from 32 down to 0 big endian 
    for (int i = 31; i >= 0; --i) {
        int val = static_cast<int>(std::round(fbstorage[pixelIdx][channelIdx] * 255.0f)); // converts from floating point 0-1 to integer color 0-255 and we round up so we don't lose our least significant bit
    
    // this extracts the LSB and if it is 1 we set the bit at position i in fileSize 
        if (val & 1) {
            fileSize |= (1U << i); // adds the bit at position i (example if header LSBs are 0,0,0,0,0,1,0,1 we get filesize = 5)
        }

        if (++channelIdx > 2) { channelIdx = 0; pixelIdx++; } // this moves us through the image we check red,green, and blue then we reset the channel and go to the next pixel
    }

    unsigned char currentByte = 0; // current byte we are on
    int bitCount = 0; // bit count
    
    // We check if the size of the data is within bound of our image
    uint32_t maxPossibleBytes = (uint32_t)((fbstorage.size() * 3 - 32) / 8); // calculates the max amount of data the image can have which is width * height of pixels * 3 for color channels - 32 for header / 8 to get the bytes
    if (fileSize > maxPossibleBytes) { // if the file size is greater then max we return and print out an error
        std::cerr << "Error: Decoded file size (" << fileSize << ") exceeds image capacity!" << std::endl;
        return;
    }

    for (uint32_t i = 0; i < fileSize * 8; ++i) { // loop through every bit of the file (byte * 8)
        if (pixelIdx >= fbstorage.size()) break; // the pixel index is greater then the size of the framebuffer storage we break

        int val = static_cast<int>(std::round(fbstorage[pixelIdx][channelIdx] * 255.0f)); // cast from floating point 0-1 to 0 - 255 the pixel and channel we are at and get that bit 
        currentByte = (currentByte << 1) | (val & 1); // shift the existing bits left to add the new bit to the right of our output 
        bitCount++; // add to bit count
        // example outupt current byte = 00000000
        // after bit 0 (LSB = 0) = 00000000
        // after bit 1 (LSB = 1) = 00000001
        // after bit 2 (LSB = 0) = 00000010 and so on...

        if (bitCount == 8) { // when we reach bitCount 8 that is one character so we add it to the output file and reset the current byte and bitcount for the next character
            outFile.put(currentByte); // we add the byte to the output file which is one character
            currentByte = 0; // reset current byte for next byte
            bitCount = 0; // reset bit count
        }

        if (++channelIdx > 2) { channelIdx = 0; pixelIdx++; } // updates our channel index and pixel index in the image
    }
    outFile.close(); // close file when loop ends for the secret message
}

/// @brief This loads in the png image into a framebuffer for future handling
/// @param filename name of the png file
void Framebuffer::loadFromPNG(std::string filename) {

    png::image<png::rgb_pixel> image(filename); // load png image
    
    // Update dimensions to match the loaded file
    width = image.get_width(); // set the width from the image
    height = image.get_height(); // set the height from the image
    
    // we assign to the fbstorage the width * height for the size of the image and then set the pixels to black 0,0,0
    fbstorage.assign(width * height, vec3(0, 0, 0));

    for (int y = 0; y < height; ++y) {
        png::image<png::rgb_pixel>::pixbuf::row_type row = image.get_row(y); // pull the entire row of pixels
        for (int x = 0; x < width; ++x) {
            png::rgb_pixel pixel = row[x]; // pull the x from the row of pixels

            // Linear index calculation: (row * width) + column
            fbstorage[y * width + x] = vec3( // map the x,y to the fbstorage and then do floating point conversion from 0.0 - 1.0 to 0 - 255 for RGB handling
                pixel.red / 255.0f,
                pixel.green / 255.0f,
                pixel.blue / 255.0f
            );
        }
    }
}