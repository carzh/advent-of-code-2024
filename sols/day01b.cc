#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

// run g++ -o day01b day01b.cc
// then run the executable

int main(int argc, char* argv[]) {
    std::string filePath = "../inputs/day01a";

    std::ifstream file(filePath);

    std::vector<int> list1;
    std::unordered_map<int, int> list2Counts;

    std::string line;
    while(std::getline(file, line)) {
        std::istringstream lineStream(line);

        int num1, num2;

        if (lineStream >> num1 >> num2) {
            list1.push_back(num1);
            if (list2Counts.find(num2) != list2Counts.end()) {
                list2Counts[num2] += 1;
            } else {
                list2Counts[num2] = 1;
            }
        }
    }

    file.close();

    int similarity = 0;

    for (const int list1num : list1) {
        if (list2Counts.find(list1num) != list2Counts.end()) {
            similarity += (list1num * list2Counts[list1num]);
        }
    }

    std::cout << "CALCULATED SIMILARITY: " << similarity << std::endl;

    return 0;
}