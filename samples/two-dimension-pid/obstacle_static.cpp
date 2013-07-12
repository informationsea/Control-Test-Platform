#include "odeutil/platform.h"
#include "odeutil/normal.h"
#include "odeutil/marker.h"
#include "odeutil/obstaclefield.h"

#include <math.h>

static MarkerID marker;
static double target_x, target_y;
static bool target_updated;

#define CONTINE_TIME 1
#define TORQUE 2
#define ROTATION_STEP 2000

void controller_initialize(void)
{
    printf ("q : Left Forward\n"
            "a : Left Backward\n"
            "w : Right Forward\n"
            "s : Right Backward\n");
    target_x = 1;
    target_y = 0.005;
    marker_set(marker, target_x, target_y, NO_ANGLE);
}

static double last_distance;
static double last_angle;

void controller_simulation_step(void)
{
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

    printf("angle: %8.4f  distance: %8.4f", target_angle, target_distance);

    if (ABS(target_angle) > M_PI/10 && target_distance > 0.1) {
        double torque_diff = target_angle/M_PI*1.5 - target_angle_diff*500;
        car_set_motor_torque_left(-torque_diff);
        car_set_motor_torque_right(+torque_diff);
        printf(" diff: %8.4f\n", torque_diff);
    } else if (target_distance > 0.1) {
        double torque_master = target_distance - target_distance_diff*1000;
        if (torque_master > 1)
            torque_master = 1;
        double torque_diff = target_angle/M_PI*0.4 - target_angle_diff*500;
        printf(" master: %8.4f  diff: %8.4f\n", torque_master, torque_diff);

        car_set_motor_torque_left(torque_master - torque_diff);
        car_set_motor_torque_right(torque_master + torque_diff);
    } else {
        car_set_motor_torque_left(-target_distance_diff*1000);
        car_set_motor_torque_right(-target_distance_diff*1000);
        printf("\n");
    }

    last_distance = target_distance;
    last_angle = target_angle;
}

void controller_key_event(int key)
{
    switch(key) {
    case 'a':
        target_x = 0;
        target_y = 1;
        break;
    case 's':
        target_x = 1;
        target_y = 2;
        break;
    case 'd':
        target_x = 2;
        target_y = 2;
        break;
    case 'f':
        target_x = 1;
        target_y = -1;
        break;
    default:
        break;
    }

    target_updated = true;
    marker_set(marker, target_x, target_y, NO_ANGLE);
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
