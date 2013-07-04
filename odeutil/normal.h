/* -*- mode: c++ -*- */

/** @file normal.h
 *  @author Y.Okamura
 * 
 *  Normal robot for DC motor practice.
 *
 * \section Basic usage
 * \include samples/normal-robot/normalkey.cpp
 */

/** @defgroup normal_robot Normal Robot
 *  @ingroup objectset
 */

#ifndef _NORMAL_H_
#define _NORMAL_H_

#include <ode/ode.h>
#include "platform.h"

#ifdef __cplusplus

extern "C"{
#endif

/** Robot position
 *  @ingroup normal_robot
 */
struct CarPosition {
    dReal x;
    dReal y;
    dReal angle;
};

/** Get robot position
 *  @ingroup normal_robot
 */
struct CarPosition car_get_position(void);

/** Set left motor torque
 *  @ingroup normal_robot
 *  @param torque Torque
 */
void car_set_motor_torque_left(double torque);

/** Set right motor torque
 *  @ingroup normal_robot
 *  @param torque Torque
 */
void car_set_motor_torque_right(double torque);

/** Get encoder value
 *  @ingroup normal_robot
 */
void car_get_encoder_value(double *left, double *right);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

/** Normal Robot for DC Motor practice
 *  @ingroup objectset normal_robot
 */
class NormalRobot : public ObjectSet
{
public:
    /** Constructor of NormalRobot
     *  @see car_set_motor_torque_left
     *  @see car_set_motor_torque_right
     *  @see car_get_encoder_value
     *  @see car_get_point
     *  @param x_offset Offset of X axis
     *  @param y_offset Offset of Y axis
     *  @param z_offset Offset of Z axis
     *  @param angle Offset of angle
     *  @param wheelSize Size of wheel
     *  @param x_size Length of x axis
     *  @param y_size Length of y axis
     *  @param z_size Length of z axis
     */
    NormalRobot(double x_offset = 0, double y_offset = 0, double z_offset = 0,
                double angle = 0, double wheelSize = 0.08,
                double x_size = 0.5, double y_size = 0.3, double z_size = 0.1,
                double mass = 1);
    virtual ~NormalRobot();

    virtual void makeObjects();
    virtual void destroyObjects();
    virtual void drawObjects();
    virtual void simulationStep();

    CarPosition getCarPosition();
    void setMotorTorqueLeft(double torque);
    void setMotorTorqueRight(double torque);

    double getEncoderValueLeft();
    double getEncoderValueRight();

private:
    dVector3 offset;
    dVector3 size;
    double angle;
    double wheelSize;
    double bodyMass;

    RigidBox *mainBody;
    RigidBody *wheels[3];
    dHingeJoint *hinge[2];
    dBallJoint *ballcaster;

    double motor_torque[2];
    double encoder_value[2];
    double last_angle[2];
    int encoder_offset[2];
};

#endif

#endif /* _NORMAL_H_ */


// Local variables:
// mode:c++
// End:

