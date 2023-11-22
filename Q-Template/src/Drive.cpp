#include "vex.h"


using namespace vex;

Drive::Drive(int L_port, int R_port, gyro Gyro, float wheel_size) : L(L_port, true), R(R_port), Gyro(Gyro), wheel_ratio(wheel_size/360*2) {
 
    wheel_ratio = wheel_size/360;
}

void Drive::DriveWithVoltage(float L_volt, float R_volt){
  L.spin(forward,L_volt, volt);
  R.spin(forward,R_volt, volt);
  
}

void Drive::SetPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout){

   drive_kp = kp;
   drive_ki = ki;
   drive_kd = kd;
   drive_starti = starti;
   drive_settle_error = settle_error;
   drive_settle_time = settle_time;
   drive_timeout = timeout;
   
}


void Drive::SetTurnPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout){
   turn_kp = kp;
   turn_ki = ki;
   turn_kd = kd;
   turn_starti = starti;
   turn_settle_error = settle_error;
   turn_settle_time = settle_time;
   turn_timeout = timeout;
   
}

int Drive::DriveFor(float distance){

  printf("DriveFor Called\n");

  //Create PID objects for turn and drive
  PID drivePID(drive_kp,drive_ki,drive_kd,drive_starti,drive_settle_error,drive_settle_time,drive_timeout);
  PID turnPID(turn_kp,turn_ki,turn_kd,turn_starti,turn_settle_error,turn_settle_time,turn_timeout);
  
  
  avg_wheel_rotation = (L.position(deg)+R.position(deg))/2;
  
  //Set Starting Position to offset code later
  avg_starting_postion = avg_wheel_rotation;
  starting_angle = Gyro.rotation();
  turn_volt = 0;  
  
  //While DrivePID has not met settled criteria
  while(!drivePID.is_settled()){

    avg_wheel_rotation = (L.position(deg)+R.position(deg))/2;
    
    //Re-ad if doesn't work
    //starting_angle = Gyro.rotation();
    


    //Convert distance to rotation
    rotation = distance/wheel_ratio;

    //Find voltage/error for drive
    drive_volt = drivePID.compute((rotation+avg_starting_postion)-avg_wheel_rotation);


    //Course Correct
    if (!turnPID.is_settled()){
    turn_volt = turnPID.compute(starting_angle-Gyro.rotation());
    } else {
      turn_volt = 0;
    }
    
    
    //Calculate Wheel Voltages
    L_volt = drive_volt - turn_volt;

    R_volt = drive_volt + turn_volt;


    
    //Spin wheels
    
    
    printf("%.3f", static_cast<float>(L_volt));
    

    L.spin(forward,L_volt,volt);
    R.spin(forward,R_volt,volt);
    
    


    
    
    
    

  
  }
  return 0;

}

int Drive::TurnTo(float angle){

 //Declare Turn Object
 PID TurnPID(turn_kp,turn_ki,turn_kd,turn_starti,turn_settle_error,turn_settle_time,turn_timeout);

 
 //While TurnPID has not met settled criteria
 while(!TurnPID.is_settled()){

   //Calculate 
   turn_volt = TurnPID.compute(angle-Gyro.rotation(degrees));


   //Apply
   L_volt = -turn_volt; 
   R_volt = turn_volt; 
   L.spin(forward, L_volt,volt);
   R.spin(forward,R_volt,volt);
   

   //Update
   total_desired_rotation = Gyro.angle();
   
   
   wait(10,msec);
   
 } 
 return 0;
}

int Drive::TurnFor(float angle){
  PID TurnPID(turn_kp,turn_ki,turn_kd,turn_starti,turn_settle_error,turn_settle_time,turn_timeout);

  starting_angle = Gyro.angle();

  
  while(!TurnPID.is_settled()){
   turn_volt = TurnPID.compute((angle+starting_angle)-Gyro.angle());
   total_desired_rotation = Gyro.angle();

   L_volt = -turn_volt; 
   
   R_volt = turn_volt; 
   
   L.spin(forward, L_volt,volt);
   
   R.spin(forward,R_volt,volt);
   
   
   
   wait(10,msec);
   
 } 
  return 0;
}

void Drive::clearSensors(bool calibrate_gyro){
  L.setPosition(0, deg);
  R.setPosition(0, deg);
  Gyro.setRotation(0,deg);
}

void Drive::update(enum::drive_method drive_method){

  if (drive_method != NO_DRIVE){

    if (drive_method == TANK){
      L.spin(forward, controller().AxisA.position(), percent);
      R.spin(forward, controller().AxisD.position(), percent);
      
    }
    
    else if (drive_method == ARCADE){
      L.spin(forward, (controller().AxisA.position())-controller().AxisC.position(), percent);
      R.spin(forward, (controller()).AxisA.position()+controller().AxisC.position(), percent);

    }
    
  }
  total_desired_rotation = Gyro.rotation();

}

int Drive::drive_odometry(){
    Odom odom;
    odom_is_enabled = true;
    while(odom_is_enabled){
    current_rot = /*avg_wheel_rotation*wheel_ratio;*/ (L.position(deg)+R.position(deg))/2*wheel_ratio;
    x = x + odom.calculate_x(Gyro.angle(), current_rot-prev_rot);
    y = y + odom.calculate_y(Gyro.angle(), current_rot-prev_rot);
    prev_rot = current_rot;

    //For Debugging only
    //Brain.Screen.clearScreen(); Brain.Screen.setCursor(1, 1); Brain.Screen.newLine(); Brain.Screen.print("X:");  Brain.Screen.print(x); Brain.Screen.print(", Y:"); Brain.Screen.print(y);
    //Brain.Screen.newLine(); Brain.Screen.print(current_rot);
    wait(10,msec);
    }
    return 0;
}

void Drive::stop_odometry(){
  odom_is_enabled = false;
}

