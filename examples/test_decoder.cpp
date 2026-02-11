/*
    @author Ethan Ness 

    Decoder main for running the decoder for the steganography implementation

*/


/*
    Includes section
*/
#include "framebuffer.h" // framebuffer class
#include <iostream> // iostream library


/// @brief This is the main for the decoder program to decode the image for the message
/// @param argc number of arguments passed into the decoder
/// @param argv vector for the arguments passed into decoder
/// @return int return which is either 1 if less then 3 arguments passed in and 0 otherwise
int main(int argc, char* argv[]) {

    // if the number of argumets passed in is less then 3 we output clarrification text and return 1
    if (argc < 3) {
        std::cout << "Usage: ./decode <input_image.png> <output_file_name>" << std::endl;
        return 1;
    }

    std::string inputImage = argv[1]; // png file with the payload
    std::string outputFile = argv[2]; // name of file for the extracted payload

    Framebuffer fb; // framebuffer object

    std::cout << "Loading image..." << std::endl;
    fb.loadFromPNG(inputImage); // loads the png image in for decoding
    
    std::cout << "Extracting secret data..." << std::endl;
    fb.decodeMessage(outputFile); // we decode the image to get message

    std::cout << "Success! Data saved to " << outputFile << std::endl;
    return 0;
}