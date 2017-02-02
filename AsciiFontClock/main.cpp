//===============================================//
//
//	@Author:	Samuel Lewis
//	@Github:	http://github.com/Samuel-Lewis/Experiments
//
//	@Project:	Ascii Font Clock
//
//	@Created:   2017-02-02
//
//===============================================//


#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>

class Font {
private:
    // Stored symbols for the font
    std::vector<std::vector<std::string> > symbols;

    // Loads characters from a file
    void loadFont(std::string fileName) {
        fileName = "fonts/"+fileName;
        std::ifstream file(fileName);

        // Check if font file is actually there
        if (!file.good()) {
            std::cerr << "FONT NOT FOUND" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::string line;

        // Read height
        std::getline(file,line);
        sscanf(line.c_str(), "[height=%i]", &height);

        for (int i = 0; i < 11; i++) {
            // Ignore dividing line
            std::getline(file,line);
            symbols.push_back(std::vector<std::string>());
            // Read line by line, and store to vector (makes printing easier)
            for (int h = 0; h < height; h++) {
                std::getline(file,line);
                symbols[i].push_back(line);
            }
        }

        // Always close your files kids.
        file.close();
    }

    void normalise() {
        // Find max width of each char, and pad with spaces to fill out
        for (int i = 0; i < 11; i++) {
            int maxW = symbols[i][0].size();
            // Get max width
            for (size_t h = 1; h < height; h++) {
                maxW = maxW < symbols[i][h].size() ? symbols[i][h].size() : maxW;
            }

            // Pad char with trailing spaces (for printing)
            for (size_t h = 0; h < height; h++) {
                symbols[i][h].insert(symbols[i][h].end(), maxW-symbols[i][h].size(), ' ');
            }
        }
    }

public:
    int height;
    Font(std::string name) {
        loadFont(name);
        normalise();
    }

    // Find and validate font in font symbols
    std::vector<std::string> get(char c) {
        // 0 1 2 3 4 5 6 7 8 9 :
        // Thankfully these are in order
        if (c >= '0' && c <= ':') {
            return symbols[c - '0'];
        } else {
            std::cerr << "Could not find symbol '"<<c<<"' Something really went wrong... ";
            std::exit(EXIT_FAILURE);
        }
    }
};

std::string getTime(std::string format) {
    // Get time and date now
    auto now = std::chrono::system_clock::now();
    auto nowTime = std::chrono::system_clock::to_time_t(now);

    // Strip to wanted format
    std::stringstream ss;
    ss << std::put_time(std::localtime(&nowTime),format.c_str());
    return ss.str();
}

std::string pretty(std::string t, Font font) {
    // All symbols to print
    std::vector<std::vector<std::string> > art;

    // Work out which symbols
    for (size_t i = 0; i < t.size(); i++) {
        art.push_back(font.get(t[i]));
    }

    std::stringstream ss;
    // Add them line by line (as they are multi line chars)
    for (size_t h = 0; h < font.height; h++) {
        for (size_t i = 0; i < art.size(); i++) {
            ss << art[i][h] << " ";
        }
        ss << "\n";
    }

    return ss.str();
}

int main(int argc, char* argv[]) {

    // Default font
    std::string fontName = "doh";

    // Choose custom font (if specified)
    if (argc > 1) {
        fontName = (std::string)argv[1];
    }

    // Load font now
    Font font(fontName);

    std::string dateNow = getTime("%A, %B %d %Y");
    std::string timeNow = getTime("%X");

    std::cout << std::endl;
    // Print time in ascii art
    std::cout << pretty(timeNow, font) << std::endl;
    std::cout << dateNow << "\n" << std::endl;

    return EXIT_SUCCESS;
}
