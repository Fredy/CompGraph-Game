#pragma once

namespace comm {
const float UNIT_WIDTH = 32.0f, UNIT_HEIGHT = 18.0f;

enum class ObstacleType {
  rock = 'R',
  block = 'B', // its the same as wall
  hole = 'H',
  fireBall = 'F',
  box = 'b',
};

namespace color {
const float LIGHT_BLUE[] = {0.298f, 0.686f, 1.0f};
const float ORANGE[] = {1.0f, 0.67f, 0.0f};
const float RED[] = {0.81f, 0.02f, 0.0f};
const float BLACK[] = {0.0f, 0.0f, 0.0f};
const float WHITE[] = {1.0f, 1.0f, 1.0f};
const float GREEN[] = {0.1f, 1.0f, 0.2f};
} // namespace color

} // namespace comm
