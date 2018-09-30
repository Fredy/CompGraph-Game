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

    while (getline(file, line)) {
      // `OBSTACLE_TYPE LEFT BOTTOM WIDTH HEIGHT`
      // `OBSTACLE_TYPE LEFT BOTTOM `
      istringstream stringstrm(line);
      vector<string> params((istream_iterator<string>(stringstrm)),
                            istream_iterator<string>());
      // TODO: read params from vector params
    }

    file.close();
  }
};