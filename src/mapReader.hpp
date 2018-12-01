#pragma once

#include "common.hpp"
#include "objects/obstacles/block.hpp"
#include "objects/obstacles/coin.hpp"
#include "objects/obstacles/fireball.hpp"
#include "objects/obstacles/hole.hpp"
#include "objects/obstacles/obstacle.hpp"
#include "objects/obstacles/rock.hpp"
#include "objects/obstacles/floor.hpp"
#include "objects/player.hpp"
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

  Obstacle *createObstacle(comm::ObstacleType type, float left, float bottom) {
    Obstacle *obstacle = nullptr;
    switch (type) {
    case comm::ObstacleType::rock:
      obstacle = new Rock(left, bottom);
      obstacle->setVelocity(5.0f);
      break;
    case comm::ObstacleType::block:
      obstacle = new Block(left, bottom);
      obstacle->setVelocity(5.0f);
      break;
    case comm::ObstacleType::hole:
      obstacle = new Hole(left, bottom);
      obstacle->setVelocity(5.0f);
      break;
    case comm::ObstacleType::floor:
      obstacle = new Floor(left, bottom);
      obstacle->setVelocity(5.0f);
      break;
    case comm::ObstacleType::fireBall:
      obstacle = new FireBall(left, bottom);
      obstacle->setVelocity(8.0f);
      break;
    case comm::ObstacleType::box:
      break;
    case comm::ObstacleType::coin:
      obstacle = new Coin(left, bottom);
      obstacle->setVelocity(5.0f);
      break;
    default:
      cout << "Type doesn't recognized: " << char(type) << endl;
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

  void setHoleProps(Hole *hole, float groupLeft, float groupWidth) {
    hole->setGroupLeft(groupLeft);
    hole->setGroupWidth(groupWidth);
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
      int bottom = height - hCount;

      float holeLeft = 0.0f;
      float holeWidth = 0.0f;
      vector<Hole *> holeRow;

      while (true) {
        pos = line.find_first_not_of(' ', pos + 1);
        if (pos == string::npos) {
          break;
        }
        Obstacle *obstacle = createObstacle(comm::ObstacleType(line[pos]),
                                            comm::UNIT_WIDTH + pos, bottom);

        if (comm::ObstacleType(line[pos]) == comm::ObstacleType::hole) {
          holeRow.push_back(dynamic_cast<Hole *>(obstacle));
          if (holeLeft == 0.0f) {
            holeLeft = comm::UNIT_WIDTH + pos;
          }
          holeWidth += 1.0f;
        }

        loadedMap.push_back(obstacle);
      }
      if (!holeRow.empty()) {
        for (auto hole : holeRow) {
          setHoleProps(hole, holeLeft, holeWidth);
        }
      }

      hCount++;
    }
    file.close();
  }

  void updateMap(float dt, const Player &player) {
    auto i = loadedMap.rbegin();
    for (; i < loadedMap.rend(); i++) {
      (*i)->update(dt,player);
    }
  }
};
