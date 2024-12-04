#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iostream>

void printVector(std::vector<int> v) {
    for (const int num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filePath = "../inputs/day02sample";

    std::ifstream file(filePath);

    std::vector<std::vector<int>> levels;

    std::string line;
    while(std::getline(file, line)) {
        std::istringstream lineStream(line);

        int num;
        std::vector<int> level;

        while (lineStream >> num) {
            level.push_back(num);
        }

        levels.push_back(level);
    }

    file.close();

    int numSafe = 0;

    for (auto& level : levels) {
        // increasing if diff is positive
        bool inc = level[1] - level[0] > 0;
        bool safe = true;

        printVector(level);
        for (int i = 1; i < level.size(); i++) {
            int diff = std::abs(level[i] - level[i - 1]);
            std::cout << "absolute difference at i " << i << " is " << std::abs(level[i] - level[i - 1]) << std::endl;
            if (1 <= diff && diff <= 3) {
                if (!inc && (level[i] - level[i - 1]) > 0) {
                    std::cout << "not decreasing at i " << i << std::endl;
                    printVector(level);
                    safe = false;
                    break;
                } else if (inc && level[i] - level[i - 1] < 0) {
                    // if diff is neg then its decreasing
                    std::cout << "not increasing at i " << i << std::endl;
                    printVector(level);
                    safe = false;
                    break;
                }
            } else {
                std::cout << "not valid difference at i " << i << std::endl;
                printVector(level);
                safe = false;
                break;
            }
        }
        std::cout << "END OF VEC" << std::endl;
        
        numSafe += safe ? 1 : 0;
    }

    std::cout << "NUMBER SAFE: " << numSafe << std::endl;

    return 0;
}
