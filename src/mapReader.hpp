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
#include "objects/obstacles/goal.hpp"
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
  size_t goalPos; 
  float progression;

  GLuint barTextureId = texture::load(config::progresBarTexturePath);

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
    case comm::ObstacleType::goal:
      obstacle = new Goal(left, bottom);
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
    goalPos = string::npos;
    progression = 0.0f;

    string line;
    const int height = int(comm::UNIT_HEIGHT);
    int hCount = 0;

    while (getline(file, line)) {
      auto pos = string::npos;
      int bottom = height - hCount;

      float holeLeft = 0.0f;
      float holeWidth = 0.0f;
      vector<Hole *> holeRow;

      comm::ObstacleType lastInserted = comm::ObstacleType::floor;

      // Set goal position:
      if (goalPos == string::npos) {
        size_t goalPosTmp = line.find_first_of('G');
        if (goalPosTmp != string::npos) {
          goalPos = size_t(comm::UNIT_WIDTH) + goalPosTmp;
        }
      }

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

        if (!holeRow.empty() and lastInserted == comm::ObstacleType::hole and
            comm::ObstacleType(line[pos]) != comm::ObstacleType::hole) {
          for (auto hole : holeRow) {
            setHoleProps(hole, holeLeft, holeWidth);
          }
          holeRow.clear();
          holeLeft = 0;
          holeWidth = 0;
        }
        lastInserted = comm::ObstacleType(line[pos]);
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

  void gameOver(){
    const float left = comm::UNIT_WIDTH /2;
    const float width = 8.0;
    const float bottom = comm::UNIT_HEIGHT /2;
    const float height = 5.0f;
  }

  void drawProgressBar(float dt) {
    const float left = 23.5f;
    const float width = 8;
    const float bottom = 17.5f;
    const float height = 0.2f;
    const float barMargin = 1.0f/16.0f;

    progression += 5.0f * dt / (goalPos / width);
    glDisable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    glBindTexture(GL_TEXTURE_2D, barTextureId);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);


    glColor3fv(comm::color::WHITE);
    glVertex3f(left, bottom, -2);
    glVertex3f(left, bottom + height, -2);
    glVertex3f(left + width, bottom + height, -2);
    glVertex3f(left + width , bottom, -2);   

    glColor3fv(comm::color::GREEN);
    glVertex3f(left, bottom, -1);
    glVertex3f(left, bottom + height, -1);
    glVertex3f(left + progression, bottom + height, -1);
    glVertex3f(left + progression , bottom, -1);
    glEnd();

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor3fv(comm::color::WHITE);
    glTexCoord2f(0,0);
    glVertex3f(left - barMargin, bottom, 0);
    glTexCoord2f(0,1);
    glVertex3f(left - barMargin, bottom + height, 0);
    glTexCoord2f(1,1);
    glVertex3f(left + width + barMargin, bottom + height, 0);
    glTexCoord2f(1,0);
    glVertex3f(left + width + barMargin , bottom, 0);   
    glEnd();

    glEnable(GL_LIGHTING);
  }
};
