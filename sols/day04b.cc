#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const char *SEARCH_STR = "A";

bool checkGridForChar(std::vector<const char *> lines,
                      std::vector<size_t> lineLengths, size_t row, size_t col,
                      char goal) {
  // std::cout << "in check grid for char! " << row << " " << col << " " << goal
  // << std::endl;
  if (row > lineLengths.size()) {
    return false;
  }
  if (row >= lines.size() || col >= lineLengths[row]) {
    // std::cout << "if statement trig" << std::endl;
    // return false bc out of bounds
    return false;
  }
  return lines[row][col] == goal;
}

int findSearchStrFromStart(std::vector<const char *> lines,
                           std::vector<size_t> lineLengths, size_t row,
                           size_t col) {
  // check diag from upper left to lower right
  if (!((checkGridForChar(lines, lineLengths, row - 1, col - 1, 'S') &&
         checkGridForChar(lines, lineLengths, row + 1, col + 1, 'M')) ||
        (checkGridForChar(lines, lineLengths, row - 1, col - 1, 'M') &&
         checkGridForChar(lines, lineLengths, row + 1, col + 1, 'S')))) {
    return false;
  } 
  // then check diag from upper right to lower left
  if (!((checkGridForChar(lines, lineLengths, row - 1, col + 1, 'S') &&
         checkGridForChar(lines, lineLengths, row + 1, col - 1, 'M')) ||
        (checkGridForChar(lines, lineLengths, row - 1, col + 1, 'M') &&
         checkGridForChar(lines, lineLengths, row + 1, col - 1, 'S')))) {
    return false;
  } 
  return true;
}

int countSearchStr(std::vector<const char *> lines,
                   std::vector<size_t> lineLengths) {
  int count = 0;
  for (size_t row = 0; row < lines.size(); ++row) {
    const char *line = lines[row];

    for (size_t col = 0; line[col] != '\0'; ++col) {
      // if starting character detected, search in all directions
      if (line[col] == SEARCH_STR[0]) {
        // std::cout << "STARTING CHARACTER DETECTED AT INDEX " << col << " in
        // row: " << line << std::endl;
        count += findSearchStrFromStart(lines, lineLengths, row, col);
      }
    }
  }
  return count;
}

int main(int argc, char *argv[]) {
  std::string filePath = "../inputs/day04";

  std::ifstream file(filePath);

  std::vector<const char *> lines;
  std::vector<size_t> lineLengths;

  std::string line;
  while (std::getline(file, line)) {
    lineLengths.push_back(line.length());
    lines.push_back(strdup(line.c_str()));
  }

  file.close();

  int sol = countSearchStr(lines, lineLengths);

  std::cout << "NUMBER OF TIMES " << SEARCH_STR << " HAS APPEARED: ";
  std::cout << sol << std::endl;

  return 0;
}
