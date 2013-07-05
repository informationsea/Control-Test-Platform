#include "odeutil/platform.h"
#include "odeutil/normal.h"
#include "odeutil/marker.h"
#include "odeutil/obstaclefield.h"

static int left, right;
static MarkerID marker;
static int step_num;

#define CONTINE_TIME 1
#define TORQUE 2
#define ROTATION_STEP 2000

void controller_initialize(void)
{
    printf ("q : Left Forward\n"
            "a : Left Backward\n"
            "w : Right Forward\n"
            "s : Right Backward\n");
    left  = 0;
    right = 0;
    step_num = 0;
}

void controller_simulation_step(void)
{
    double x, y;
    if (step_num < ROTATION_STEP) {
        x = cos(M_PI*2*step_num/ROTATION_STEP);
        y = sin(M_PI*2*step_num/ROTATION_STEP);
    } else if (step_num < ROTATION_STEP*3/2) {
        x = -cos(M_PI*2*step_num/ROTATION_STEP)+2;
        y = sin(M_PI*2*step_num/ROTATION_STEP);
    } else if (step_num < ROTATION_STEP*5/2) {
        x = cos(M_PI*2*step_num/ROTATION_STEP)+4;
        y = sin(M_PI*2*step_num/ROTATION_STEP);
    } else if (step_num < ROTATION_STEP*3) {
        x = -cos(M_PI*2*step_num/ROTATION_STEP)+2;
        y = sin(M_PI*2*step_num/ROTATION_STEP);
    }

    step_num += 1;
    if (step_num >= ROTATION_STEP*3)
        step_num = 0;

    marker_set(marker, x, y, NO_ANGLE);

    
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
    platform_add_objectset(new NormalRobot(1, 0, 0.1, M_PI/2, 0.1, 0.7, 0.4, 0.2, 1));
    platform_add_objectset(new ObstacleField());

    Marker *pos_marker = new Marker();
    marker = pos_marker->id();
    platform_add_objectset(pos_marker);
    
    platform_start(argc, argv);

    return 0;
}
