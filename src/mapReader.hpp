#pragma once

#include "objects/obstacle.hpp"
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "common.hpp"
using namespace std;
int j = 1;
class MapReader {
private:
  vector<string> fileNames;
  vector<Obstacle *> loadedMap;

  Obstacle *createObstacle(comm::ObstacleType type, float left, float bottom) {
    Obstacle *obstacle = nullptr;    
    switch (type) {
      case comm::ObstacleType::rock :
        break;
      case comm::ObstacleType::block :
        obstacle = new Obstacle(left, bottom);// TODO: this is temporal
        obstacle->setVelocity(5.0f);
        break;
      case comm::ObstacleType::hole :
        break;
      case comm::ObstacleType::fireBall :
        break;
      case comm::ObstacleType::wall :
        break;
      case comm::ObstacleType::box :
        break;
      default:
        break;
    }
    return obstacle;
  }

  void clearLoaderMap() {
    for (int i = 0; i < loadedMap.size(); i++) {
      delete loadedMap[i];
    }
    loadedMap.clear();
  }


public:
  MapReader(vector<string> fileNames) { this->fileNames = fileNames; }
  ~MapReader() { clearLoaderMap(); }

  void load(int fileIndex) {
    ifstream file(fileNames.at(fileIndex));
    if (!file.is_open()) {
      throw invalid_argument("File " + fileNames.at(fileIndex) +
                             " doesn't exists.");
    }

    clearLoaderMap();

    string line;
    const int height = int(comm::UNIT_HEIGHT);
    int hCount = 0;

    while (getline(file, line)) {
      auto pos = string::npos;
      int bottom =  height - hCount;
      while (true) {
        pos = line.find_first_not_of(' ', pos + 1);
        if (pos == string::npos) {
          break;
        }
        Obstacle *obstacle = createObstacle(comm::ObstacleType(line[pos]), comm::UNIT_WIDTH + pos, bottom);
        loadedMap.push_back(obstacle);
      }

      hCount++;
    }
    file.close();
  }

  void updateMap(float dt, const Player &player) {
    for (const auto &i : loadedMap) {
      i->draw(dt);
      i->checkCollision(player.getLeft(), player.getBottom(),
                           player.getRight(), player.getUp()) ;
    }
  }
  
};
