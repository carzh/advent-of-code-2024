#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

const char* SEARCH_STR = "XMAS";

bool checkGridForChar(std::vector<const char*> lines, std::vector<size_t> lineLengths, size_t row, size_t col, char goal) {
    if (row > lineLengths.size()) {
        return false;
    }
    if (row >= lines.size() || col >= lineLengths[row]) {
        return false;
    }
    return lines[row][col] == goal;
}

int findSearchStrFromStart(std::vector<const char*> lines, std::vector<size_t> lineLengths, size_t row, size_t col) {
    bool dir[8] = {true, true, true, true, true, true, true, true};

    for (size_t searchStrI = 0; SEARCH_STR[searchStrI] != '\0'; ++searchStrI) {
        if (dir[0]) {
            dir[0] = checkGridForChar(lines, lineLengths, row, col + searchStrI, SEARCH_STR[searchStrI]);
        }
        if (dir[1]) {
            dir[1] = checkGridForChar(lines, lineLengths, row, col - searchStrI, SEARCH_STR[searchStrI]);
        }
        if (dir[2]) {
            dir[2] = checkGridForChar(lines, lineLengths, row + searchStrI, col, SEARCH_STR[searchStrI]);
        }
        if (dir[3]) {
            dir[3] = checkGridForChar(lines, lineLengths, row - searchStrI, col, SEARCH_STR[searchStrI]);
        }
        if (dir[4]) {
            dir[4] = checkGridForChar(lines, lineLengths, row - searchStrI, col - searchStrI, SEARCH_STR[searchStrI]);
        }
        if (dir[5]) {
            dir[5] = checkGridForChar(lines, lineLengths, row - searchStrI, col + searchStrI, SEARCH_STR[searchStrI]);
        }
        if (dir[6]) {
            dir[6] = checkGridForChar(lines, lineLengths, row + searchStrI, col - searchStrI, SEARCH_STR[searchStrI]);
        }
        if (dir[7]) {
            dir[7] = checkGridForChar(lines, lineLengths, row + searchStrI, col + searchStrI, SEARCH_STR[searchStrI]);
        }
    }
    return std::count(dir, dir + 8, true);
}

int countSearchStr(std::vector<const char*> lines, std::vector<size_t> lineLengths) {
    int count = 0;
    for (size_t row = 0; row < lines.size(); ++row) {
        const char* line = lines[row];

        for (size_t col = 0; line[col] != '\0'; ++col) {
            if (line[col] == SEARCH_STR[0]) {
                count += findSearchStrFromStart(lines, lineLengths, row, col);
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    std::string filePath = "../inputs/day04";

    std::ifstream file(filePath);

    std::vector<const char*> lines;
    std::vector<size_t> lineLengths;

    std::string line;
    while(std::getline(file, line)) {
        lineLengths.push_back(line.length());
        lines.push_back(strdup(line.c_str()));
    }

    file.close();

    int sol = countSearchStr(lines, lineLengths);

    std::cout << "NUMBER OF TIMES " << SEARCH_STR << " HAS APPEARED: ";
    std::cout << sol << std::endl;

    return 0;
}
