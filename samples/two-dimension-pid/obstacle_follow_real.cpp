#include "odeutil/platform.h"
#include "odeutil/normal.h"
#include "odeutil/marker.h"
#include "odeutil/obstaclefield.h"

#include <math.h>

static MarkerID marker;
static bool target_updated;
static int step_num;

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define ROTATION_STEP 4000

void controller_initialize(void)
{
    printf ("q : Left Forward\n"
            "a : Left Backward\n"
            "w : Right Forward\n"
            "s : Right Backward\n");
}

static double last_distance;
static double last_angle;

void controller_simulation_step(void)
{
    double target_x, target_y;
    if (step_num < ROTATION_STEP) {
        target_x = cos(M_PI*2*step_num/ROTATION_STEP);
        target_y = sin(M_PI*2*step_num/ROTATION_STEP);
    } else if (step_num < ROTATION_STEP*3/2) {
        target_x = -cos(M_PI*2*step_num/ROTATION_STEP)+2;
        target_y = sin(M_PI*2*step_num/ROTATION_STEP);
    } else if (step_num < ROTATION_STEP*5/2) {
        target_x = cos(M_PI*2*step_num/ROTATION_STEP)+4;
        target_y = sin(M_PI*2*step_num/ROTATION_STEP);
    } else if (step_num < ROTATION_STEP*3) {
        target_x = -cos(M_PI*2*step_num/ROTATION_STEP)+2;
        target_y = sin(M_PI*2*step_num/ROTATION_STEP);
    }

    step_num += 1;
    if (step_num >= ROTATION_STEP*3)
        step_num = 0;

    marker_set(marker, target_x, target_y, NO_ANGLE);

    CarPosition pos = car_get_position();

    double target_angle = atan2(target_y - pos.y, target_x - pos.x) + pos.angle;
    double target_distance = sqrt(pow(target_y - pos.y, 2) + pow(target_x - pos.x, 2));
    if (target_updated) {
        last_distance = target_distance;
        last_angle = target_angle;
        target_updated = false;
    }

    while(target_angle > M_PI) {
        target_angle -= M_PI*2;
    }
    while(target_angle < -M_PI) {
        target_angle += M_PI*2;
    }

    double target_angle_diff = last_angle - target_angle;
    double target_distance_diff = last_distance - target_distance;

    while(target_angle_diff > M_PI) {
        target_angle_diff -= M_PI*2;
    }
    while(target_angle_diff < -M_PI) {
        target_angle_diff += M_PI*2;
    }


    printf("angle: %8.4f(%8.4f)  distance: %8.4f(%8.4f)", target_angle, target_angle_diff, target_distance, target_distance_diff);

    double torque_master = target_distance*5;
    if (torque_master > 4)
        torque_master = 4;
    // if (ABS(target_angle) > M_PI/4)
    //     torque_master = 0.5;
    double torque_diff = (target_angle/M_PI*8)*(torque_master*0.5+0.5);
#define MAX_TORQUE_DIFF 3.0
    if (torque_diff > MAX_TORQUE_DIFF)
        torque_diff = MAX_TORQUE_DIFF;
    else if (torque_diff < -MAX_TORQUE_DIFF)
        torque_diff = -MAX_TORQUE_DIFF;
    
    printf(" master: %8.4f  diff: %8.4f", torque_master, torque_diff);

    car_set_motor_torque_left(torque_master - torque_diff);
    car_set_motor_torque_right(torque_master + torque_diff);

    printf(" left: %8.4f  right: %8.4f\n", torque_master - torque_diff, torque_master + torque_diff);

    last_distance = target_distance;
    last_angle = target_angle;
}

void controller_key_event(int key)
{

}

void controller_finalize(void)
{
    
}

int main(int argc, char *argv[])
{
    platform_initialize();
    NormalRobot *robot = new NormalRobot(1, 0, 0.1, M_PI/2, 0.1, 0.7, 0.4, 0.2, 1);
    platform_add_objectset(robot);
    platform_add_objectset(new ObstacleField());

    robot->setFriction(true);

    Marker *pos_marker = new Marker();
    marker = pos_marker->id();
    platform_add_objectset(pos_marker);
    
    platform_start(argc, argv);

    return 0;
}
