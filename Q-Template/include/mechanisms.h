#pragma once
#include "vex.h"

 enum intake_state{FORWARD, REVERSE, OFF};
 enum outtake_state{UP, DOWN, STOP};

class intake{
    public:
        intake(int port, bool reversed, int speed);
    
        void set_intake(int intake_state);

        vex::motor intake_motor;
        int status = OFF;
    private:
        int speed = 100;
       

};

class outtake{
    public:
        outtake(int port, bool reversed, int speed);
        outtake(int port_1, int port_2, bool reversed, int speed);
    
        void set_outtake(int outtake_state);

        vex::motor outtake_motor;
        vex::motor outtake_motor_2;
        vex::motor_group outtake_motor_group;
        int status;
    private:
        int speed = 100;
       

};

extern intake Intake;

void controllerInit();
void buttonLDOWN_pressed();
void buttonLUP_pressed();
void buttonLUP_released();

void buttonRUP_pressed();
void buttonRDOWN_pressed();
void buttonsR_released();

void buttonFUP_pressed();

void Touchledtest();

