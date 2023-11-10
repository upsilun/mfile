#include <iostream>
#include <fstream>
#include <string>

// ANSI escape codes for text color
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\033[0m"

bool createFile(const std::string& filename, bool enforceFileExtension) {
    if (enforceFileExtension) {
        // Check if the file already exists
        std::ifstream fileExists(filename.c_str());
        if (fileExists.good()) {
            std::cerr << RED_TEXT << "Error: File \"" << filename << "\" already exists." << RESET_TEXT << "\n";
            return false;
        }

        // Check if the filename contains a file extension
        size_t lastDotPosition = filename.find_last_of(".");
        if (lastDotPosition == std::string::npos || lastDotPosition == 0 || lastDotPosition == filename.length() - 1) {
            std::cerr << RED_TEXT << "Error: Invalid filename \"" << filename << "\". Please provide a valid file name with an extension." << RESET_TEXT << "\n";
            return false;
        }
    }

    // Create a new file
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile.close();
        std::cout << GREEN_TEXT << "File \"" << filename << "\" created successfully." << RESET_TEXT << "\n";
        return true;
    } else {
        std::cerr << RED_TEXT << "Error creating the file \"" << filename << "\"" << RESET_TEXT << "\n";
        return false;
    }
}

int main(int argc, char* argv[]) {
    bool enforceFileExtension = true;

    if (argc == 2 && std::string(argv[1]) == "--help") {
        // Display help message
        std::cerr << YELLOW_TEXT << "Usage: " << argv[0] << " <filename> [--no-check]\n\n"
                  << "Creates a file with the specified filename.\n"
                  << "Options:\n"
                  << "  --no-check   Disable filename validation (enforce file extension).\n" << RESET_TEXT;
        return 0;
    } else 
    if (argc == 3 && std::string(argv[2]) == "--no-check") {
        enforceFileExtension = false;
    } else 
    if (argc != 2) {
        std::cerr << YELLOW_TEXT << "Usage: " << argv[0] << " <filename> [--no-check]\n\n"
                  << "Use --help for more information." << RESET_TEXT << "\n";
        return 1;
    }

    std::string filename = argv[1];

    if (createFile(filename, enforceFileExtension)) {
        //std::cout << GREEN_TEXT << "Program completed successfully." << RESET_TEXT << "\n";
        return 0;
    } else {
        //std::cerr << RED_TEXT << "Program terminated with errors." << RESET_TEXT << "\n";
        return 2;
    }
}
