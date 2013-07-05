#include "obstaclefield.h"

#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawSphere dsDrawSphereD
#define dsDrawCylinder dsDrawCylinderD
#define dsDrawCapsule dsDrawCapsuleD
#define dsDrawLine dsDrawLineD
#endif

ObstacleField::ObstacleField()
{

}

ObstacleField::~ObstacleField()
{

}

void ObstacleField::makeObjects()
{
    dReal cylinderList[][2] = {
        {4, 0},
        {2, 0},
        {0, 0}
    };

    for (size_t i = 0; i < LENGTH(cylinders); ++i) {
        cylinders[i] = new RigidCylinder(*world, 0.1, 1, 0.08, 0.8);
        cylinders[i]->makeGeom(*space);
        cylinders[i]->setColor(72/255., 231/255., 99/255.);
        cylinders[i]->setPosition(cylinderList[i][0], cylinderList[i][1], 0.4);
        cylindersFix[i] = new dFixedJoint(world->id(), 0);
        cylindersFix[i]->attach(0, cylinders[i]->id());
        cylindersFix[i]->set();

    }
}

void ObstacleField::destroyObjects()
{
    for (size_t i = 0; i < LENGTH(cylinders); ++i) {
        SAFE_DELETE(cylinders[i]);
    }
}

void ObstacleField::drawObjects()
{
    for (size_t i = 0; i < LENGTH(cylinders); ++i) {
        cylinders[i]->drawInStuff();
    }
}

void ObstacleField::simulationStep()
{

}

bool ObstacleField::isGround(dGeomID id)
{
    for (size_t i = 0; i < LENGTH(cylinders); i++) {
        if (id == cylinders[i]->geomID())
            return true;
    }
    
    return false;
}
