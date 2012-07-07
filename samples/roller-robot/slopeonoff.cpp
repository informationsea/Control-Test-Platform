#include "odeutil/indicator.h"
#include "odeutil/platform.h"
#include "odeutil/roller.h"
#include "odeutil/slopefield.h"

IndicatorID difference_indicator_id;

double auto_get_target_position(void);
bool auto_set_target_position_by_key(char key);
void auto_set_target_position_by_value(double target);
void auto_print_target_position_list(void);

/* Controller */

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

/* End of controller */


/* Initialize platform */

int main(int argc, char *argv[])
{
    platform_initialize();
    platform_add_objectset(new RollerRobot());

    Indicator *ir = new Indicator(0, 1);
    difference_indicator_id = ir->id();
    platform_add_objectset(ir);
    
    platform_add_objectset(new SlopeField());
    platform_start(argc, argv);

    return 0;
}

/* End of initializing platform */

static double target_position = 0;

double auto_get_target_position(void)
{
    return target_position;
}
    
bool auto_set_target_position_by_key(char key)
{
    switch(key) {
    case 'e':
        target_position = -1.0;
        return true;
    case 'w':
        target_position = -0.5;
        return true;
    case 'q':
        target_position = 0.0;
        return true;
    case 'a':
        target_position = 0.5;
        return true;
    case 's':
        target_position = 1.0;
        return true;
    case 'd':
        target_position = 1.5;
        return true;
    case 'f':
        target_position = 2.0;
        return true;
    case 'g':
        target_position = 2.5;
        return true;
    case 'h':
        target_position = 3.0;
        return true;
    case 'j':
        target_position = 3.5;
        return true;
    case 'k':
        target_position = 4.0;
        return true;
    case 'l':
        target_position = 4.5;
        return true;
    default:
        return false;
    }

}

void auto_set_target_position_by_value(double target)
{
    target_position = target;
}
    
void auto_print_target_position_list(void)
{
    printf ("Target list\n"
            "e :-1.0\n"
            "w :-0.5\n"
            "q : 0.0\n"
            "a : 0.5\n"
            "s : 1.0\n"
            "d : 1.5\n"
            "f : 2.0\n"
            "g : 2.5\n"
            "h : 3.0\n"
            "j : 3.5\n"
            "k : 4.0\n"
            "l : 4.5\n");
}


