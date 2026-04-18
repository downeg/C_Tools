#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>

bool isPrintable(unsigned char c) {
    return std::isprint(c);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <binary_file> [min_length]\n";
        return 1;
    }

    const char* filename = argv[1];
    size_t minLength = 4; // default minimum string length

    if (argc >= 3) {
        minLength = std::stoul(argv[2]);
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file.\n";
        return 1;
    }

    std::vector<char> buffer;
    char byte;

    while (file.get(byte)) {
        unsigned char ubyte = static_cast<unsigned char>(byte);

        if (isPrintable(ubyte)) {
            buffer.push_back(byte);
        }
        else {
            if (buffer.size() >= minLength) {
                std::cout.write(buffer.data(), buffer.size());
                std::cout << "\n";
            }
            buffer.clear();
        }
    }

    // Handle trailing buffer
    if (buffer.size() >= minLength) {
        std::cout.write(buffer.data(), buffer.size());
        std::cout << "\n";
    }

    return 0;
}