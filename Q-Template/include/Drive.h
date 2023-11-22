#pragma once
#include "vex.h"

enum drive_method{NO_DRIVE, TANK, TANK_MECHANUM, ARCADE, ARCADE_MECHANUM};



class Drive
{
 public:

  
  Drive(int L_port, int R_port, vex::gyro Gyro, float wheel_size);


  
  void SetPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);
  void SetTurnPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

  void DriveWithVoltage(float L_volt, float R_volt);

  /*
  * @brief Drive Specified Distance
  * @param Distance in inches
  * */
  int DriveFor(float distance);

  /*
  * @brief Turn to Specified Angle
  * @param Angle in degrees
  * */
  int TurnTo(float angle);

  /*
  * @brief Turn for Specified Angle
  * @param Angle in degrees
  * */
  int TurnFor(float angle);

  /*
  * @brief Update drive. Updates motor speed and controll method as well
  * @param Drive_Method Tank or Arcade*/
  void update(enum::drive_method drive_method);

  int drive_odometry();
  void stop_odometry();

  void clearSensors(bool calibrate_gyro);

  void thisisatest();

  vex::motor L;
  //vex::motor LB;

  vex::motor R;
  //vex::motor RB;

  vex::gyro Gyro;


  float x = 0;
  float y = 0;

  bool drive_error = false;
  bool gyro_error = false;

  
  

  

private:
  float L_volt;
  float R_volt;
  
  float drive_kp;
  float drive_ki;
  float drive_kd;
  float drive_starti;
  float drive_settle_error;
  float drive_settle_time;
  float drive_timeout;
  

  float turn_kp;
  float turn_ki;
  float turn_kd;
  float turn_starti;
  float turn_settle_time;
  float turn_timeout;
  float turn_settle_error;

  
  float avg_left_wheel_rotation;
  float avg_right_wheel_rotation;

  float wheel_ratio;

  float rotation;

  float drive_volt = 0;
  float turn_volt;

  float total_desired_rotation = 0;
  float starting_angle;

  float avg_starting_postion;
  float avg_wheel_rotation;
  
  
  float current_rot;
  float prev_rot = 0;
  
  bool odom_is_enabled = true;

  


  int drive_motors_installed = 0;


  


  

  

  

  

};