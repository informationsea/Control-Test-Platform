#include <iostream>
#include <vector>
#include "odeutil.h"
#include "roller.h"

/* Roller Robot Class */

#define TORQUE_LIMIT 2.1

static RollerRobot *onlyRobot;

extern "C" {
double roller_get_point(void)
{
    return onlyRobot->getPosition();
}

void roller_set_motor_torque(double torque)
{
    onlyRobot->setMotorTorque(torque);
}

double roller_get_encoder_value()
{
    return onlyRobot->getEncoderValue();
}
}


RollerRobot::RollerRobot()
{
    onlyRobot = this;
}

RollerRobot::~RollerRobot()
{

}

void RollerRobot::makeObjects()
{
    /* Make a robot */
    mainBody = new RigidBox(*world, 10, 0.5, 0.3, 0.1);
    mainBody->setColor(1,0,0);
    mainBody->setPosition(0,0,0.14);
    mainBody->makeGeom(*space);

    for (size_t i = 0; i < LENGTH(wheels); ++i) {
        wheels[i] = new RigidSphere(*world, 0.02, 0.08);
        wheels[i]->setColor(1,1,0);
        wheels[i]->makeGeom(*space);
        wheels[i]->setAngularDamping(0.0001);
        wheels[i]->setAngularDampingThreshold(0.001);
    }
    wheels[0]->setPosition(0.18 , 0.1, 0.09);
    wheels[1]->setPosition(0.18, -0.1, 0.09);
    wheels[2]->setPosition(-0.18 , 0.1, 0.09);
    wheels[3]->setPosition(-0.18, -0.1, 0.09);

    for (size_t i = 0; i < LENGTH(hinge); ++i) {
        hinge[i] = new dHingeJoint(world->id(), 0);
        hinge[i]->attach(*wheels[i], *mainBody);
        hinge[i]->setAnchor(wheels[i]->getPosition());
        hinge[i]->setAxis(0, 1, 0);
        hinge[i]->setParam(dParamLoStop, -dInfinity);
        hinge[i]->setParam(dParamHiStop,  dInfinity);
    }


    last_angle = 0;

    encoder_value = hinge[0]->getAngle();
}

void RollerRobot::destroyObjects()
{
    SAFE_DELETE(mainBody);
    for (size_t i = 0; i < LENGTH(wheels); ++i) {
        SAFE_DELETE(wheels[i]);
    }
    for (size_t i = 0; i < LENGTH(hinge); ++i) {
        SAFE_DELETE(hinge[i]);
    }
}

void RollerRobot::drawObjects()
{
    /* Draw robot */
    mainBody->drawInStuff();
    for (size_t i = 0; i < LENGTH(wheels); ++i) {
        wheels[i]->drawInStuff();
    }

    /* Draw status bar */
    double positions[][3] = {
            {1   , 1, hinge[1]->getAngleRate()/3},
            {0.5 , 1, hinge[0]->getAngleRate()/3},
            {-1  , 1, motor_torque},
    };

    for (size_t i = 0; i < LENGTH(positions); ++i) {
        double startpos[3] = {positions[i][0],positions[i][1],0};
        if (positions[i][2] < 0) {
            positions[i][2] = -positions[i][2];
            dsSetColor(1, 0, 0);
        } else {
            dsSetColor(0, 1, 0);
        }
        dsDrawLineD(startpos, positions[i]);
    }

    /* clear torque */
    motor_torque = 0;
}

void RollerRobot::simulationStep()
{
    double current_angle = hinge[0]->getAngle();
    double angle_difference = last_angle - current_angle;
    while (M_PI < angle_difference) {
        angle_difference -= M_PI;
        encoder_offset +=1;
    }
    while (-M_PI > angle_difference) {
        angle_difference += M_PI;
        encoder_offset -= 1;
    }
    encoder_value = M_PI*2*encoder_offset + current_angle;
    last_angle = current_angle;
}

double RollerRobot::getPosition()
{
    const dReal *dpos = mainBody->getPosition();
    return  dpos[0];
}


void RollerRobot::setMotorTorque(double torque)
{
    if (torque > TORQUE_LIMIT) {
        torque = TORQUE_LIMIT;
    } else if (torque < -TORQUE_LIMIT) {
        torque = -TORQUE_LIMIT;
    }

    for (size_t i = 0; i < LENGTH(hinge); ++i) {
        hinge[i]->addTorque(torque);
    }
    motor_torque = torque;
}

double RollerRobot::getEncoderValue()
{
    return encoder_value;
}


