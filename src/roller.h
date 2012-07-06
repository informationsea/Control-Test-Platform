/* -*- mode: c++ -*- */

/**
   @file roller.h
   A Robot for 1 dimension control practice
   @author Y.Okamura

   - nhk_roller.cpp
   @include ../pid-practice/main/nhk_roller.cpp

   - nhk_roller.h
   @include ../pid-practice/main/nhk_roller.h

   - controller.c
   @include ../pid-practice/onoff-control/controller.c
 */

/** @defgroup roller_robot Roller Robot
 *  @ingroup objectset
 */

#ifndef _NORMAL_H_
#define _NORMAL_H_

#include <ode/ode.h>
#include "platform.h"

#ifdef __cplusplus

extern "C"{
#endif

/** Get X coordinate of roller robot.
 * @return X position
 * @ingroup roller_robot
 */
double roller_get_point(void);

/** Set motor torque.
 * @param torque
 * @ingroup roller_robot
 */
void roller_set_motor_torque(double torque);

/** Get encoder value.
 *  @return encoder value
 * @ingroup roller_robot
 */
double roller_get_encoder_value();

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

/** A robot for 1 dimension control practice.
 *  see roller.h to get example.
 *  @see roller_get_encoder_value
 *  @see roller_set_motor_torque
 *  @see roller_get_point
 *  @ingroup roller_robot objectset
 */
class RollerRobot : public ObjectSet
{
public:
    RollerRobot();
    virtual ~RollerRobot();

    virtual void makeObjects();
    virtual void destroyObjects();
    virtual void drawObjects();
    virtual void simulationStep();

    double getPosition();
    void setMotorTorque(double torque);

    double getEncoderValue();

private:
    RigidBox *mainBody;
    RigidBody *wheels[4];
    dHingeJoint *hinge[4];

    double motor_torque;
    double encoder_value;
    double last_angle;
    int encoder_offset;
};

#endif

#endif /* _NORMAL_H_ */


// Local variables:
// mode:c++
// End:
