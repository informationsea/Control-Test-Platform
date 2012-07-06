#include "roller.h"
#include "slope_roller.h"

static int torque;

#define CONTINE_TIME 20
#define TORQUE 1

void controller_initialize(void)
{
    torque = 0;
    auto_set_target_position_by_value(0.5);
    auto_print_target_position_list();
}

void controller_simulation_step(void)
{
    double diff = auto_get_target_position() - roller_get_point();
    indicator_set(difference_indicator_id, diff);
    if (diff < 0) {
        roller_set_motor_torque(-TORQUE);
    } else {
        roller_set_motor_torque(TORQUE);
    }
    printf("%lf %lf %lf\r", auto_get_target_position(), diff, roller_get_encoder_value());
}

void controller_key_event(int key)
{
    auto_set_target_position_by_key(key);
}

void controller_finalize(void)
{
    
}
