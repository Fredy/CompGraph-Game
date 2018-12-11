#pragma once

#include <array>
#include <random>
#include <vector>
using namespace std;

namespace comm {
const float UNIT_WIDTH = 32.0f, UNIT_HEIGHT = 18.0f;

enum class ObstacleType {
  rock = 'R',
  block = 'B', // its the same as wall
  fireBall = 'F',
  hole = 'H',
  box = 'b',
  floor = 'f',
  coin = 'C',
  goal = 'G',
};

namespace color {
const float LIGHT_BLUE[] = {0.298f, 0.686f, 1.0f};
const float ORANGE[] = {1.0f, 0.67f, 0.0f};
const float RED[] = {0.81f, 0.02f, 0.0f};
const float BLACK[] = {0.0f, 0.0f, 0.0f};
const float WHITE[] = {1.0f, 1.0f, 1.0f};
const float GREEN[] = {0.1f, 1.0f, 0.2f};
const float GREY[] = {0.22, 0.22, 0.22};
} // namespace color

namespace rndTex {
default_random_engine generator; // It doesn't matter if this doesn't
                                 // change in each execution.
uniform_int_distribution<int> randomDist(0, 3);

const vector<vector<array<float, 2>>> texPositions = {
    {{0, 0}, {0, 1}, {1, 1}, {1, 0}},
    {{0, 1}, {1, 1}, {1, 0}, {0, 0}},
    {{1, 1}, {1, 0}, {0, 0}, {0, 1}},
    {{1, 0}, {0, 0}, {0, 1}, {1, 1}}};

vector<vector<array<float, 2>>> genTexPositions(float w, float h) {
  return {{{0, 0}, {0, h}, {w, h}, {w, 0}},
          {{0, h}, {w, h}, {w, 0}, {0, 0}},
          {{w, h}, {w, 0}, {0, 0}, {0, h}},
          {{w, 0}, {0, 0}, {0, h}, {w, h}}};
}
} // namespace rndTex

} // namespace comm
