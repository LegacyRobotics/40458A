#include "vex.h"



Odom odom;
void no_auton(){
  chassis.clearSensors(false);

}

int auton_odom(){
  chassis.drive_odometry();
  return 0;
}

void left_auton(){
  printf("Left Auton Called\n");
  
  chassis.clearSensors(false);

  //Hack Solution, run thread in auton_odom
  vex::task odometry(auton_odom);
  printf("Calling Drivefor\n");
  chassis.DriveFor(2);

  //chassis.TurnTo(-90);
  
  

}
