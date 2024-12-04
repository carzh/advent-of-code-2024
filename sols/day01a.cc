#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

// run g++ -o day01a day01a.cc
// then run the executable

int main(int argc, char* argv[]) {
    std::string filePath = "../inputs/day01a";

    std::ifstream file(filePath);

    std::vector<int> list1;
    std::vector<int> list2;

    std::string line;
    while(std::getline(file, line)) {
        std::istringstream lineStream(line);

        int num1, num2;

        if (lineStream >> num1 >> num2) {
            list1.push_back(num1);
            list2.push_back(num2);
        }
    }

    file.close();

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    int diff = 0;

    for (int i = 0; i < list1.size(); i++) {
        diff += std::abs(list1[i] - list2[i]);
    }

    std::cout << "CALCULATED DIFFERENCE: " << diff << std::endl;

    return 0;
}