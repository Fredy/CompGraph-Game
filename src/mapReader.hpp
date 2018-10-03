#pragma once

#include "objects/obstacle.hpp"
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class MapReader {
private:
  vector<string> fileNames;
  vector<Obstacle *> loadedMap;

public:
  MapReader(vector<string> fileNames) { this->fileNames = fileNames; }

  void load(int fileIndex) {
    ifstream file(fileNames.at(fileIndex));
    if (!file.is_open()) {
      throw invalid_argument("File " + fileNames.at(fileIndex) +
                             " doesn't exists.");
    }
    string line;

    vector<string> rawMap;

    while (getline(file, line)) {
      rawMap.push_back(line);

    }

    file.close();
  }
};