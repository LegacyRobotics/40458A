/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Quinn                                                     */
/*    Created:      4/13/2023, 2:33:52 PM                                     */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"


using namespace vex;


//Declare Drive Chassis, L, R, Gyro, Wheel Travel(inches)
Drive chassis(PORT4,PORT11,PORT1,7.874);

int main() {

    chassis.SetPID(1,0,0,0,2,5000,10000);
	
    Brain.Screen.print("Quinn's Code V1.1\n");
    Brain.Screen.print("Battery: ");
    Brain.Screen.print("%i",Brain.Battery.capacity());
    Brain.Screen.print("%\n");

    printf("Quinn's Code V1.1\n");
    printf("Battery: %i Percent\n\n", Brain.Battery.capacity());
    
    
    
    controllerInit();
    //vex::thread thread1 = thread(Touchledtest);
    this_thread::sleep_for(100);
    left_auton();

    
    while(1) {
        if (drivemethod == ARCADE){chassis.update(ARCADE);}
        if (drivemethod == TANK){chassis.update(TANK);}
        
        this_thread::sleep_for(10);
    }
}