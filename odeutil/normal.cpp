#include <iostream>
#include <vector>
#include "odeutil.h"
#include "normal.h"

/* Normal Robot Class */

static NormalRobot *onlyRobot;

#define FRICTION_RATE 0.01

extern "C" {
CarPosition car_get_position(void)
{
    return onlyRobot->getCarPosition();
}

void car_set_motor_torque_left(double torque)
{
    onlyRobot->setMotorTorqueLeft(torque);
}

void car_set_motor_torque_right(double torque)
{
    onlyRobot->setMotorTorqueRight(torque);
}

void car_get_encoder_value(double *left, double *right)
{
    *left  = onlyRobot->getEncoderValueLeft();
    *right = onlyRobot->getEncoderValueRight();
}
}


NormalRobot::NormalRobot(double x_offset, double y_offset, double z_offset,
        double angle, double wheelSize,
                         double x_size, double y_size, double z_size, double mass):
    angle(angle), wheelSize(wheelSize), bodyMass(mass), _initialized(false), enable_friction(false), enable_realmotor(false)
{
    offset[0] = x_offset;
    offset[1] = y_offset;
    offset[2] = z_offset;

    size[0] = x_size;
    size[1] = y_size;
    size[2] = z_size;

    onlyRobot = this;
}

NormalRobot::~NormalRobot()
{

}

void printVector3(const dVector3 vec)
{
    printf("%lf %lf %lf\n", vec[0], vec[1], vec[2]);
}

void NormalRobot::makeObjects()
{
    size_t i;

    /* Make a robot */
    mainBody = new RigidBox(*world, 1, size[0], size[1], size[2]);
    mainBody->setColor(1,0,0);
    mainBody->setPosition(0, 0, size[2]/2 + wheelSize);
    mainBody->makeGeom(*space);
    mainBody->setTotalMass(bodyMass);

    foreach(wheels) {
        wheels[i] = new RigidSphere(*world, 0.005, wheelSize);
        wheels[i]->setColor(1,1,0);
        wheels[i]->makeGeom(*space);
        wheels[i]->setAngularDamping(0.001);
        wheels[i]->setAngularDampingThreshold(0.001);
    }
    wheels[0]->setPosition(size[0]/2-wheelSize,
            (size[1] - wheelSize)/2, wheelSize);
    wheels[1]->setPosition(size[0]/2-wheelSize,
            -(size[1] - wheelSize)/2, wheelSize);
    wheels[2]->setPosition(-(size[0] - wheelSize)/2, 0 , wheelSize);

    foreach(hinge) {
        hinge[i] = new dHingeJoint(world->id(), 0);
        hinge[i]->attach(*wheels[i], *mainBody);
        hinge[i]->setAnchor(wheels[i]->getPosition());
        hinge[i]->setAxis(0, 1, 0);
        hinge[i]->setParam(dParamLoStop, -dInfinity);
        hinge[i]->setParam(dParamHiStop,  dInfinity);
    }

    ballcaster = new dBallJoint(world->id(), 0);
    ballcaster->attach(*wheels[2], *mainBody);
    ballcaster->setAnchor(wheels[2]->getPosition());

    foreach(last_angle) {
        last_angle[i] = 0;
    }

    foreach(encoder_value) {
        encoder_value[i] = hinge[i]->getAngle();
    }

    foreach(encoder_offset) {
        encoder_offset[i] = 0;
    }

    dMatrix3 rotation = {
            cos(angle),-sin(angle), 0, 0,
            sin(angle), cos(angle), 0, 0,
            0         , 0         , 1, 0
    };

    printVector3(offset);

    foreach(wheels) {
        rotate_object(wheels[i]->id(), offset, rotation);
    }
    rotate_object(mainBody->id(), offset, rotation);

    _initialized = true;
    setFriction(enable_friction);
}

void NormalRobot::destroyObjects()
{
    SAFE_DELETE(mainBody);
    for (size_t i = 0; i < LENGTH(wheels); ++i) {
        SAFE_DELETE(wheels[i]);
    }
    for (size_t i = 0; i < LENGTH(hinge); ++i) {
        SAFE_DELETE(hinge[i]);
    }
    SAFE_DELETE(ballcaster);    
}

void NormalRobot::drawObjects()
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
            {-0.5, 1, motor_torque[1]},
            {-1  , 1, motor_torque[0]},
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
    for (size_t i = 0; i < LENGTH(motor_torque); ++i) {
        motor_torque[i] = 0;
    }
}

void NormalRobot::simulationStep()
{
    for (size_t i = 0; i < LENGTH(hinge); ++i) {
        double current_angle = hinge[i]->getAngle();
        double angle_difference = last_angle[i] - current_angle;
        while (M_PI < angle_difference) {
            angle_difference -= M_PI;
            encoder_offset[i] += 1;
        }
        while (-M_PI > angle_difference) {
            angle_difference += M_PI;
            encoder_offset[i] -= 1;
        }
        last_angle[i] = current_angle;
        encoder_value[i] = 2*M_PI*encoder_offset[i] + current_angle;
    }
}

CarPosition NormalRobot::getCarPosition()
{
    CarPosition point;
    const dReal *dpos = mainBody->getPosition();
    point.x = dpos[0];
    point.y = dpos[1];
    const dReal *rotation = mainBody->getRotation();
    RotationAngles angles = get_angles(rotation);
    point.angle = angles.psi;

    return point;
}

void NormalRobot::setMotorTorqueLeft(double torque)
{
    motor_torque[0] = torque;
    if (enable_realmotor) {
        if (torque > 0) {
            torque = MAX(0, torque*2-1);
        } else if (torque < 0) {
            torque = MIN(0, torque*1.4+0.7);
        }
    }
    hinge[0]->addTorque(torque);
}

void NormalRobot::setMotorTorqueRight(double torque)
{
    motor_torque[1] = torque;
    if (enable_realmotor) {
        torque = -torque;
        if (torque > 0) {
            torque = MAX(0, torque*2-1);
        } else if (torque < 0) {
            torque = MIN(0, torque*1.4+0.7);
        }
        torque = -torque;
    }
    hinge[1]->addTorque(torque);
}

double NormalRobot::getEncoderValueLeft()
{
    return encoder_value[0];
}

double NormalRobot::getEncoderValueRight()
{
    return encoder_value[1];
}

void NormalRobot::setFriction(bool enable)
{
    size_t i;
    enable_friction = enable;
    if (_initialized) {
        foreach(wheels) {
            wheels[i]->setAngularDamping(enable ? FRICTION_RATE : 0.001);
        }
    }
}
