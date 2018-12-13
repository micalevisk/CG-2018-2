#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED


#include "vec3f.h"

enum Wall
{
  WALL_LEFT,
  WALL_RIGHT,
  WALL_FAR,
  WALL_NEAR,
  WALL_TOP,
  WALL_BOTTOM
};

//Stores information regarding a ball
struct Ball
{
  Vec3f v;   //Velocity
  Vec3f pos; //Position
  float r;   //Radius
  Vec3f color;
};

//Stores a pair of balls
struct BallPair
{
  Ball *ball1;
  Ball *ball2;
};

//Stores a ball and a wall
struct BallWallPair
{
  Ball *ball;
  Wall wall;
};


#endif
