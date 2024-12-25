#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
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
      for (int dependency : protocols[page]) {
        if (contained.count(dependency) > 0 &&
            encountered.count(dependency) == 0) {
          return false;
        }
      }
    }
    encountered.insert(page);
  }

  return true;
}

std::vector<int> sortIncorrectUpdate(
    std::unordered_map<int, std::vector<int>> protocols,
    std::vector<int> update) {
  std::unordered_set<int> contained(update.begin(), update.end());
  std::unordered_map<int, int> indegrees;
  std::unordered_map<int, std::unordered_set<int>> outdegrees;
  std::queue<int> zeroIndegrees;
  std::vector<int> sorted;

  for (int page : contained) {
    indegrees[page] = 0;
    if (protocols.find(page) != protocols.end()) {
      // iterate through dependencies
      for (int dependency : protocols[page]) {
        if (contained.count(dependency) > 0) {
          indegrees[page] += 1;
          if (outdegrees.find(dependency) != outdegrees.end()) {
            outdegrees[dependency].insert(page);
          } else {
            outdegrees[dependency] = {page};
          }
        }
        // if we don't see the dependency in this update, then don't add to the
        // indegrees or outdegrees
      }
    }
    if (indegrees[page] == 0) {
      zeroIndegrees.push(page);
    }
  }

  while (!zeroIndegrees.empty()) {
    int page = zeroIndegrees.front();
    sorted.push_back(page);
    zeroIndegrees.pop();

    if (outdegrees.find(page) != outdegrees.end()) {
      for (int outdegree : outdegrees[page]) {
        indegrees[outdegree] -= 1;
        if (indegrees[outdegree] <= 0) {
          zeroIndegrees.push(outdegree);
        }
      }
    }
  }

  std::cout << "BEFORE SORTING: ";
  printVector(update);
  std::cout << "AFTER SORTING: ";
  printVector(sorted);
  return sorted;
}

int calcMiddleNumSum(std::unordered_map<int, std::vector<int>> protocols,
                     std::vector<std::vector<int>> updates) {
  int sum = 0;
  int countOfInvalidUpdates = 0;
  for (std::vector<int> update : updates) {
    if (!isValidUpdate(protocols, update)) {
      std::vector<int> sorted = sortIncorrectUpdate(protocols, update);
      sum += sorted[update.size() / 2];
      countOfInvalidUpdates++;
    }
  }
  std::cout << "COUNT OF INVALID UPDATES: " << countOfInvalidUpdates
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
