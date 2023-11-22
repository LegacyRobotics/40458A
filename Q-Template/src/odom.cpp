#include "vex.h"

float Odom::calculate_x(float angle, float pos){
  return cos(to_rad(angle))*pos;
};

float Odom::calculate_y(float angle, float pos){
  return sin(to_rad(angle))*pos;
};

