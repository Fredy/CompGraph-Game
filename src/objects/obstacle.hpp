#pragma once

#include "rectangle.hpp"
#include "common.hpp"
#include <math.h>

class Obstacle : public Rectangle {
  // TODO: check if every obstacle is an rectangle, this is important for
  // collisions.
private:
  using Rectangle::draw;

  const float orange[3] = {1.0f, 0.67f, 0.0f};
  const float red[3] = {1.0f, 0.0f, 0.0f};
  float velocityX;
  float positionX = 0.0f;
  float borders[4]; //left,bottom,right,up 
  bool colliders[4];  
  bool onCollision = false;

public:
  
  Obstacle(float left, float bottom, float depth = 5.0f)
      : Rectangle(left, bottom, 1, 1, depth) {
        borders[0] = left ;
        borders[1] = bottom;
        borders[2] = bottom+1.f;
        borders[3] = left+1.0f;
      }

  void setVelocity(float velocity) {
    velocityX = velocity;
  }
  
  void checkObsCollision(float otherLeft, float otherBottom, float otherRight,
                   float otherUp){
    for(int i = 0; i<4;i++){colliders[i] = false;}
    //for debugging           
    //cout<<onCollision<<" "<<"b: "<<borders[1] <<" U: "<<borders[2] <<" oU: "<<otherUp<<" oB: "<<otherBottom<<" l: "<<borders[0] <<" r: "<<borders[3] <<" oL: "<<otherLeft<<" oR: "<<otherRight<<"\n";  
    if( borders[0]<=otherRight){colliders[0] = true;} // rightCollision
    if( borders[1]<otherUp){colliders[1] = true;}  //upCollision
    if( borders[2]>=otherBottom){colliders[2] = true;}  //downCollision
    if( borders[3]>otherLeft){colliders[3] = true;} // leftCollision
    if (colliders[0] && colliders[1] && colliders[2]&& colliders[3] ){onCollision=true;}  
  }
  
  void action(){
    if(onCollision){
      glColor3fv(red);
    }else{
      glColor3fv(orange);
    }
  }

  void draw(float dt) override {
    positionX -= velocityX * dt;
    borders[0] -= velocityX * dt;
    borders[3] -= velocityX * dt;
    glPushMatrix();
    //fixPosition();
    glTranslatef(positionX, 0.0f, 0.0f);

    action();   
    draw();

    glPopMatrix();
  }

};
