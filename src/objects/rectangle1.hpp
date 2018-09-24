#pragma once
class Rectangle : public Object {
private:
  using Object::setMode;
  using Object::setVerticesData;
  float left , bottom , width , height , depth;

public:
  /* Draws the rectangle with it bottom left corner at (left, bottom) */
  Rectangle(float left, float bottom, float width, float height, float depth) {
    setVerticesData(4);
    setMode(GL_QUADS);
  }

  /* Draws the rectangle at (0, 0) */
  Rectangle(float width, float height, float depth) {
    float left = -width / 2.0f;
    float bottom = -height / 2.0f;
    Rectangle(left, bottom, width, height, depth);
  }

  void draw(float left, float bottom ,float width, float height, float depth) //TODO: extraerlo del Object
  {
    glBegin(GL_QUADS);
    glVertex3f(left, bottom,-depth);
    glVertex3f(left+width, bottom,-depth);
    glVertex3f(left+width, bottom+height,-depth);
    glVertex3f(left, bottom+height,-depth);
    glEnd();
  }

};
