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

bool areTwoLevelsSafe(int a, int b, bool inc) {
    int diff = std::abs(a - b);

    if (!(1 <= diff && diff <=3)) {
        return false;
    }

    if (!inc && b - a > 0) {
        return false;
    }

    if (inc && (b - a < 0)) {
        return false;
    }

    return true;
}

bool isLevelSafeWithSkip(std::vector<int> level, int skipIndex) {
    bool inc = level[1] - level[0] > 0;
    if (skipIndex == 1) {
        inc = level[2] - level[0] > 0;
    } else if (skipIndex == 0) {
        inc = level[2] - level[1] > 0;
    }

    for (int i = 1; i < level.size(); i++) {
        if (i - 1 == skipIndex && i - 2 < 0) {
            // std::cout << "the correct if statement is triggered for skippnig 0 ind" << std::endl;
            continue;
        }
        if (i == skipIndex && i + 1 == level.size()) {
            continue;
        }

        int a = i - 1 == skipIndex ? level[i - 2] : level[i - 1];
        int b = i == skipIndex ? level[i + 1] : level[i];
        if (!(areTwoLevelsSafe(a, b, inc))) {
            // std::cout << "determined not possible with skip for a " << a << " and b " << b << std::endl;
            return false;
        }
    }
    return true;

}

bool isLevelSafe(std::vector<int> level) {
    // increasing if diff is positive
    bool inc = level[1] - level[0] > 0;
    bool skipped = false;

    // std::cout << "processing level: ";
    // printVector(level);

    for (int i = 1; i < level.size(); i++) {
        if (!(areTwoLevelsSafe(level[i - 1], level[i], inc))) {
            // std::cout << "level determined unsafe for i - 1 " << i - 1 << " and i " << i << std::endl;
            if (skipped) {
                // std::cout << "in skipped if statement" << std::endl;
                // 2 levels are unsafe and we've already skipped an
                return false;
            }
            // if two levels aren't safe, can we skip either the first
            // num or the second num
            skipped = true;

            if (isLevelSafeWithSkip(level, i - 1)) {
                // std::cout << "returning true for this level because can skip i " << i - 1 << std::endl << std::endl;
                return true;
            }

            if (isLevelSafeWithSkip(level, i)) {
                // std::cout << "returning true for this level because can skip i: " << i << std::endl << std::endl;
                return true;
            }

            if (isLevelSafeWithSkip(level, 0)) {
                // std::cout << "returning true for this level because can skip i " << 0 << std::endl << std::endl;
                return true;
            }

            // std::cout << "determined cannot skip" << std::endl << std::endl;

            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::string filePath = "../inputs/day02a";

    if (argc > 1) {
        filePath = argv[1];
    }

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
        numSafe += isLevelSafe(level) ? 1 : 0;
    }

    std::cout << "NUMBER SAFE: " << numSafe << std::endl;

    return 0;
}
