#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

bool isInteger(const std::string& s) {
    std::regex integerPattern("^-?\\d+$");
    return std::regex_match(s, integerPattern);
}

bool isDecimal(const std::string& s) {
    std::regex decimalPattern("^-?\\d*\\.\\d+$");
    return std::regex_match(s, decimalPattern);
}

void countNumbers(const std::string& filename, int& integerCount, int& decimalCount) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    std::string line;
    integerCount = 0;
    decimalCount = 0;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            if (isInteger(word)) {
                integerCount++;
                // std::cout << "Integer found: " << word << std::endl;  // Debug output
            } else if (isDecimal(word)) {
                decimalCount++;
                // std::cout << "Decimal found: " << word << std::endl;  // Debug output
            }
        }
    }

    infile.close();
}

int main() {
    const std::string filename = "/Users/Shihan/Desktop/test.dat"; // 替换为实际文件名
    int integerCount, decimalCount;

    countNumbers(filename, integerCount, decimalCount);

    std::cout << "Number of integers: " << integerCount << std::endl;
    std::cout << "Number of decimals: " << decimalCount << std::endl;

    return 0;
}
