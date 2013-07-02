#include "odeutil.h"

#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawSphere dsDrawSphereD
#define dsDrawCylinder dsDrawCylinderD
#define dsDrawCapsule dsDrawCapsuleD
#endif

#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

#include "config.h"

const char* DRAWSTUFF_TEXTURE_PATH = DRAWSTUFF_TEXTURE_PATH_DEF;

extern "C" {
void const_delay(double msec)
{
    double elapsedTime = dsElapsedTime();
    if (msec > elapsedTime) {
#ifdef _WIN32
        DWORD difference = (msec - elapsedTime)*1000;
        Sleep(difference);
#else
        time_t difference = (msec - elapsedTime) * 1000;
        struct timespec req, rmtp;
        memset(&req, 0, sizeof(req));
        memset(&rmtp, 0, sizeof(req));
        req.tv_sec = difference / 1000;
        req.tv_nsec = (difference % 1000) * 1000 * 1000;
        nanosleep(&req, &rmtp);
#endif
    }
}

void rotate_object(dBodyID body, const dVector3 offset, const dMatrix3 rotation)
{
    dVector3 position;
    dVector3 rotatedPosition;

    dBodyCopyPosition(body, position);
    dMultiply0(rotatedPosition, rotation, position, 3, 3, 1);
    for (size_t i = 0; i < 3; i++)
        rotatedPosition[i] += offset[i];
    dBodySetPosition(body, rotatedPosition[0], rotatedPosition[1],
            rotatedPosition[2]);
    dBodySetRotation(body, rotation);
}

RotationAngles get_angles(const dMatrix3 rotation)
{
    RotationAngles angles;

    /* Matrix Index */
    const size_t mi[][4] = {
            {-1, -1, -1},
            {-1, 0, 1, 2},
            {-1, 4, 5, 6},
            {-1, 8, 9 ,10}
    };

    angles.theta = atan2(-rotation[mi[3][1]], sqrt(rotation[mi[3][2]] * rotation[mi[3][2]] + rotation[mi[3][3]] * rotation[mi[3][3]]));
    angles.psi = -atan2(rotation[mi[2][1]], rotation[mi[1][1]]);
    angles.phi = atan2(rotation[mi[3][2]], rotation[mi[3][3]]);

    return angles;
}
}

RigidBody::RigidBody(dWorldID world) :
            dBody(world), _r(0.5), _g(0.5), _b(0.5), _texture(DS_NONE), _geom(0), _mass(-1), _density(-1)
{
    dMassSetZero(&_dmass);
}

RigidBody::RigidBody(dWorld& world) :
            dBody(world), _r(0.5), _g(0.5), _b(0.5), _texture(DS_NONE), _geom(0), _mass(-1), _density(-1)
{
    dMassSetZero(&_dmass);
}

void RigidBody::setTotalMass(dReal newmass)
{
    _mass = newmass;
    _density = -1;
    setMassParameter();
}

void RigidBody::setDensity(dReal density)
{
    _density = density;
    _mass = -1;
    setMassParameter();
}

bool RigidBody::haveGeom()
{
    return _geom != 0;
}

RigidBody::~RigidBody(){}

// ----------------------------------------

RigidSphere::RigidSphere(dWorldID world,dReal newmass,dReal radius)
: RigidBody(world),_radius(radius)
{
    setTotalMass(newmass);
}

RigidSphere::RigidSphere(dWorld &world,dReal newmass,dReal radius)
: RigidBody(world),_radius(radius)
{
    setTotalMass(newmass);
}

RigidSphere::~RigidSphere(){}

void RigidSphere::setRadius(dReal radius)
{
    _radius = radius;
    setMassParameter();
}

void RigidSphere::drawInStuff()
{
    dsSetColor(_r,_g,_b);
    dsSetTexture(_texture);
    dsDrawSphere(getPosition(),getRotation(),_radius);
}

void RigidSphere::setMassParameter()
{
    if (_mass >= 0) {
        dMassSetSphereTotal(&_dmass,_mass,_radius);
    } else if (_density >= 0) {
        dMassSetSphere(&_dmass,_density,_radius);
    }
}

void RigidSphere::makeGeom(dSpaceID space)
{
    _geom = new dSphere(space, _radius);
    _geom->setBody(id());
}

// ----------------------------------------

RigidCylinder::RigidCylinder(dWorld &world,dReal newmass,int direction, dReal radius, dReal length)
: RigidBody(world),_direction(direction),_radious(radius),_length(length)
{
    setTotalMass(newmass);
}
RigidCylinder::RigidCylinder(dWorldID world,dReal newmass,int direction, dReal radius, dReal length)
: RigidBody(world),_direction(direction),_radious(radius),_length(length)
{
    setTotalMass(newmass);
}

RigidCylinder::~RigidCylinder() {}

void RigidCylinder::setCylinderParameter(int direction, dReal radius, dReal length)
{
    _direction = direction;
    _radious = radius;
    _length = length;
}

void RigidCylinder::drawInStuff()
{
    dsSetColor(_r,_g,_b);
    dsSetTexture(_texture);
    dsDrawCylinder(getPosition(),getRotation(),_length,_radious);
}

void RigidCylinder::setMassParameter()
{
    if (_mass >= 0) {
        dMassSetCylinderTotal(&_dmass,_mass,_direction,_radious,_length);
    } else if (_density >= 0) {
        dMassSetCylinder(&_dmass,_density,_direction,_radious,_length);
    }
}

void RigidCylinder::makeGeom(dSpaceID space)
{
    _geom = new dCylinder(space, _radious, _length);
    _geom->setBody(id());
}


// ----------------------------------------

RigidBox::RigidBox(dWorldID world,dReal newmass,dReal lx,dReal ly,dReal lz)
:RigidBody(world)
{
    _l[0] = 0;_l[1] = 0;_l[2] = 0;
    setTotalMass(newmass);
    setSize(lx,ly,lz);
}

RigidBox::RigidBox(dWorld &world,dReal newmass,dReal lx,dReal ly,dReal lz)
:RigidBody(world)
{
    _l[0] = 0;_l[1] = 0;_l[2] = 0;
    setTotalMass(newmass);
    setSize(lx,ly,lz);
}

RigidBox::~RigidBox(){}

void RigidBox::setSize(dReal lx,dReal ly,dReal lz)
{
    _l[0] = lx;
    _l[1] = ly;
    _l[2] = lz;
    setMassParameter();
}


void RigidBox::drawInStuff()
{
    dsSetColor(_r,_g,_b);
    dsSetTexture(_texture);
    dsDrawBox(getPosition(),getRotation(),_l);
}

void RigidBox::setMassParameter()
{
    for (int i = 0; i < 3; ++i) {
        if(_l[i] < 0)
            return;
    }
    if (_mass >= 0) {
        dMassSetBoxTotal(&_dmass, _mass, _l[0], _l[1], _l[2]);
    } else if (_density >= 0) {
        dMassSetBox(&_dmass, _density, _l[0], _l[1], _l[2]);
    }
}

void RigidBox::makeGeom(dSpaceID space)
{
    _geom = new dBox(space, _l[0], _l[1], _l[2]);
    _geom->setBody(id());
}
