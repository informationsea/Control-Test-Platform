#include "odeutil/indicator.h"
#include "odeutil/platform.h"
#include "odeutil/roller.h"
#include "odeutil/slopefield.h"

/* Controller */

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

/* End of controller */


/* Initialize platform */

int main(int argc, char *argv[])
{
    platform_initialize();
    platform_add_objectset(new RollerRobot());
    
    platform_add_objectset(new SlopeField());
    platform_start(argc, argv);

    return 0;
}

/* End of initializing platform */

