#include "roller.h"

static int torque;

#define CONTINE_TIME 1
#define TORQUE 2

void controller_initialize(void)
{
    printf ("q : forward\n"
            "a : Backword\n");
    torque = 0;
}

void controller_simulation_step(void)
{
    if (torque > 0){
        roller_set_motor_torque(TORQUE);
        torque--;
    } else if (torque < 0) {
        roller_set_motor_torque(-TORQUE);
        torque++;
    }
}

void controller_key_event(int key)
{
    switch(key) {
    case 'q':
        torque =  CONTINE_TIME / STEP_SIZE;
        break;
    case 'a':
        torque = -CONTINE_TIME / STEP_SIZE;
        break;
    default:
        break;
    }
}

void controller_finalize(void)
{
    
}
