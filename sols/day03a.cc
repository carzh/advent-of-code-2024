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

int parseLine(std::string line) {
    std::vector<std::pair<size_t, size_t>> results;
    std::regex pattern(R"(mul\((\d+),\s*(\d+)\))");
    
    std::sregex_iterator it(line.begin(), line.end(), pattern);
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

int main(int argc, char* argv[]) {
    std::string filePath = "../inputs/day03";

    if (argc > 1) {
        filePath = argv[1];
    }

    std::ifstream file(filePath);

    std::string line;
    int sol = 0;

    while(std::getline(file, line)) {
        sol += parseLine(line);
    }
    file.close();

    std::cout << "SOL: " << sol << std::endl;

    return 0;
}
