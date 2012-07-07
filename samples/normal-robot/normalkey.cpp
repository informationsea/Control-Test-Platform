#include "odeutil/platform.h"
#include "odeutil/normal.h"
#include "odeutil/slopefield.h"

static int left, right;

#define CONTINE_TIME 1
#define TORQUE 2

void controller_initialize(void)
{
    printf ("q : Left Forward\n"
            "a : Left Backward\n"
            "w : Right Forward\n"
            "s : Right Backward\n");
    left  = 0;
    right = 0;
}

void controller_simulation_step(void)
{
    if (left > 0){
        car_set_motor_torque_left(TORQUE);
        left--;
    } else if (left < 0) {
        car_set_motor_torque_left(-TORQUE);
        left++;
    }

    if (right > 0){
        car_set_motor_torque_right(TORQUE);
        right--;
    } else if (right < 0) {
        car_set_motor_torque_right(-TORQUE);
        right++;
    }
}

void controller_key_event(int key)
{
    switch(key) {
    case 'q':
        left =  CONTINE_TIME / STEP_SIZE;
        break;
    case 'a':
        left = -CONTINE_TIME / STEP_SIZE;
        break;
    case 'w':
        right = CONTINE_TIME / STEP_SIZE;
        break;
    case 's':
        right = -CONTINE_TIME / STEP_SIZE;
        break;
    default:
        break;
    }
}

void controller_finalize(void)
{
    
}

int main(int argc, char *argv[])
{
    platform_initialize();
    platform_add_objectset(new NormalRobot());
    platform_add_objectset(new SlopeField());
    platform_start(argc, argv);

    return 0;
}
