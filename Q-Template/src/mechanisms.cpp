#include "vex.h"

controller Controller = controller();

intake::intake(int port, bool reversed, int speed) : intake_motor(port,reversed){
    intake_motor.setVelocity(speed,percent);
}
/*outtake::outtake(int port, bool reversed, int speed) : outtake_motor(port,reversed){
    outtake_motor.setVelocity(speed,percent);
}*/
outtake::outtake(int port_1, int port_2, bool reversed, int speed) : outtake_motor(port_1,reversed), outtake_motor_2(port_2, !reversed), outtake_motor_group(outtake_motor, outtake_motor_2){
    outtake_motor_group.setVelocity(speed,percent);
}

void intake::set_intake(int intake_state){
    if (intake_state == OFF){
        printf("Intake Stopped\n");
        intake_motor.stop(coast);
        status = OFF;

    }
    if (intake_state == FORWARD){
        printf("Intake Started\n");
        intake_motor.spin(forward);
        status = FORWARD;
    }
    if (intake_state == REVERSE){
        printf("Intake Reversed\n");
        intake_motor.spin(reverse);
        status = REVERSE;
    }
}
void outtake::set_outtake(int outtake_state){
    switch(outtake_state){
        case UP:
            printf("Outtake Raising UP\n");
            outtake_motor_group.spin(forward);
            break;
        case DOWN:
            printf("Outtake Lowering DOWN\n");
            outtake_motor_group.spin(reverse);
            break;
        case STOP:
            printf("Outtake Stopped\n");
            outtake_motor_group.stop(hold);
            break;
    }
}
intake Intake(PORT5,true,100);
//touchled TouchLED = touchled(PORT9);
vex::optical Optical1 = vex::optical(vex::PORT9);


void Touchledtest(){
    Optical1.setLight(vex::ledState::on);
    
    
    
    
    while (1){

        
        
    }
}




outtake Outtake(PORT6, PORT12, false, 100);



void controllerInit(){
    Controller.ButtonLUp.pressed(buttonLUP_pressed);
    Controller.ButtonLDown.pressed(buttonLDOWN_pressed); 
    Controller.ButtonRUp.pressed(buttonRUP_pressed);
    Controller.ButtonRDown.pressed(buttonRDOWN_pressed);

    Controller.ButtonLUp.released(buttonLUP_released);
    Controller.ButtonRUp.released(buttonsR_released);
    Controller.ButtonRDown.released(buttonsR_released);

    Controller.ButtonFUp.pressed(buttonFUP_pressed);



}

void buttonLUP_pressed(){
    
    if (Intake.status == OFF || Intake.status == REVERSE){
        printf("Turning Intake On\n");
        Intake.set_intake(FORWARD);
    } else if (Intake.status == FORWARD){
        printf("Reversing Intake\n");
        Intake.set_intake(REVERSE);
    }
}

void buttonLUP_released(){
    Intake.set_intake(FORWARD);
}
void buttonLDOWN_pressed(){
    printf("Stopping Intake...\n");
    Intake.set_intake(OFF);
}

void buttonRUP_pressed(){
    Outtake.set_outtake(UP);

}
void buttonRDOWN_pressed(){
    Outtake.set_outtake(DOWN);

}

void buttonsR_released(){
    Outtake.set_outtake(STOP);
}

void buttonFUP_pressed(){
    if (drivemethod == ARCADE){
        drivemethod = TANK;
    
    }
    else{
        drivemethod = ARCADE;
    }
}
