#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <regex>
#include <utility>

void printVector(std::vector<int> v) {
    for (const int num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int parseLine(std::string line, size_t startI, size_t endI) {
    std::regex pattern(R"(mul\((\d+),\s*(\d+)\))");
    
    std::string substring = std::string(line.begin() + startI, line.begin() + endI);
    std::cout << "Iterating through: " << substring << std::endl;

    std::sregex_iterator it(line.begin() + startI, line.begin() + endI, pattern);
    std::sregex_iterator end;
    
    int sol = 0;
    while (it != end) {
        std::cout << "Match found: " << it->str() << std::endl;
        std::smatch match = *it;
        int first_int = std::stoi(match[1]);
        int second_int = std::stoi(match[2]);
        sol += first_int * second_int;
        ++it;
    }
    return sol;
}

int parseLineDo(std::string line) {
    std::cout << "IN PARSE LINE DO" << std::endl;
    int sol = 0;
    std::regex pattern(R"(^.*?don't\(\)|do\(\).*?don't\(\)|do\(\).*$)");
    
    std::sregex_iterator it(line.begin(), line.end(), pattern);
    std::sregex_iterator end;
    
    while (it != end) {
        std::smatch match = *it;
        size_t start = match.position();
        size_t end = start + match.length();
        sol += parseLine(line, start, end);
        ++it;
    }

    return sol;

}

int main(int argc, char* argv[]) {
    std::string filePath = "../inputs/day03sampleb";

    if (argc > 1) {
        filePath = argv[1];
    }

    std::ifstream file(filePath);

    std::string line;
    int sol = 0;

    while(std::getline(file, line)) {
        sol += parseLineDo(line);
    }
    file.close();

    std::cout << "SOL: " << sol << std::endl;

    return 0;
}
