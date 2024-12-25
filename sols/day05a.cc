#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void printMap(const std::unordered_map<int, std::vector<int>>& myMap) {
  for (const auto& pair : myMap) {
    std::cout << pair.first << ": [";
    for (size_t i = 0; i < pair.second.size(); ++i) {
      std::cout << pair.second[i];
      if (i < pair.second.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]" << std::endl;
  }
}

void printVector(std::vector<int> v) {
  for (const int num : v) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

bool isValidUpdate(std::unordered_map<int, std::vector<int>> protocols,
                   std::vector<int> update) {
  std::unordered_set<int> encountered;
  std::unordered_set<int> contained(update.begin(), update.end());

  for (int page : update) {
    if (protocols.find(page) != protocols.end()) {
      // check that all dependencies have been seen
      for (int dependency : protocols[page]) {
        if (contained.count(dependency) > 0 && encountered.count(dependency) == 0) {
        //   std::cout << "For update: ";
        //   printVector(update);
        //   std::cout
        //       << "We've determined that it is out of order when at the page "
        //       << page << " with unfulfilled dependency: " << dependency
        //       << std::endl;
          return false;
        }
      }
    }

    encountered.insert(page);
  }

  return true;
}

int calcMiddleNumSum(std::unordered_map<int, std::vector<int>> protocols,
                     std::vector<std::vector<int>> updates) {
  int sum = 0;
  int debugCountOfValidUpdates = 0;
  for (std::vector<int> update : updates) {
    if (isValidUpdate(protocols, update)) {
      sum += update[update.size() / 2];
      debugCountOfValidUpdates++;
    }
  }
  std::cout << "COUNT OF VALID UPDATES: " << debugCountOfValidUpdates
            << std::endl;
  return sum;
}

int main(int argc, char* argv[]) {
  std::string filePath = "../inputs/day05sample";

  if (argc > 1) {
    filePath = argv[1];
  }

  std::ifstream file(filePath);
  std::string line;

  std::unordered_map<int, std::vector<int>> protocols;

  while (std::getline(file, line) && !line.empty()) {
    std::stringstream ss(line);
    int a, b;
    char delimiter;
    if (ss >> a >> delimiter >> b && delimiter == '|') {
      if (protocols.find(b) != protocols.end()) {
        // num b is already in protocols
        protocols[b].push_back(a);
      } else {
        protocols[b] = {a};
      }
    }
  }
  std::cout << "PROTOCOLS: " << std::endl;
//   printMap(protocols);

  std::vector<std::vector<int>> updates;
  while (std::getline(file, line)) {
    std::vector<int> row;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
      row.push_back(std::stoi(token));
    }
    updates.push_back(row);
  }
  file.close();

  int middleSum = calcMiddleNumSum(protocols, updates);

  std::cout << "SUM OF MIDDLE OF CORRECT UPDATES: " << middleSum << std::endl;

  return 0;
}
