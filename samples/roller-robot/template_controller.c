#include "roller.h"
#include "slope_roller.h"

void controller_initialize(void)
{
    auto_set_target_position_by_value(0.5);
    auto_print_target_position_list();
}

void controller_simulation_step(void)
{
    double diff = auto_get_target_position() - roller_get_point();
    indicator_set(difference_indicator_id, diff);

    /* TODO : implement here */
}

void controller_key_event(int key)
{
    auto_set_target_position_by_key(key);
}

void controller_finalize(void)
{
    
}
