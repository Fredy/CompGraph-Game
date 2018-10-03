#pragma once

namespace comm {
  const float UNIT_WIDTH = 32.0f, UNIT_HEIGHT = 18.0f;

  enum class ObstacleType{
    rock = 'R',
    block = 'B',
    hole = 'H',
    fireBall = 'F',
    wall = 'W',
    box = 'b',
  };
}