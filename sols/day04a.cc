#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

const char* SEARCH_STR = "XMAS";

bool checkGridForChar(std::vector<const char*> lines, std::vector<size_t> lineLengths, size_t row, size_t col, char goal) {
    // std::cout << "in check grid for char! " << row << " " << col << " " << goal << std::endl;
    if (row > lineLengths.size()) {
        return false;
    }
    if (!(0 <= row < lines.size()) || !(0 <= col <= lineLengths[row])) {
        // std::cout << "if statement trig" << std::endl;
        // return false bc out of bounds
        return false;
    }
    return lines[row][col] == goal;
}

int findSearchStrFromStart(std::vector<const char*> lines, std::vector<size_t> lineLengths, size_t row, size_t col) {
    // 0 = +col (right), 1 = -col (left)
    // 2 = +row (down), 3 = -row (up), 
    // 4 = -r -c (left up diag), 5 = -r +c (right up diag)
    // 6 = +r -c (left down diag), 7 = +r +c (right down diag)
    // assume true in all directions first because we matched on the starting character
    bool dir[8] = {true, true, true, true, true, true, true, true};

    for (size_t searchStrI = 0; SEARCH_STR[searchStrI] != '\0'; ++searchStrI) {
        // std::cout << "We are at searchStrI " << searchStrI;
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
        // for (int i = 0; i < 8; ++i) {
        //     std::cout << std::boolalpha << dir[i] << " ";
        // }
        // std::cout << std::endl;
    }
    // std::cout << "We have counted this many at r " << row << " col " << col << ": " << std::count(dir, dir + 8, true);
    // std::cout << std::endl << std::endl;
    return std::count(dir, dir + 8, true);
}

int countSearchStr(std::vector<const char*> lines, std::vector<size_t> lineLengths) {
    int count = 0;
    for (size_t row = 0; row < lines.size(); ++row) {
        const char* line = lines[row];

        for (size_t col = 0; line[col] != '\0'; ++col) {
            // if starting character detected, search in all directions
            if (line[col] == SEARCH_STR[0]) {
                // std::cout << "STARTING CHARACTER DETECTED AT INDEX " << col << " in row: " << line << std::endl;
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
