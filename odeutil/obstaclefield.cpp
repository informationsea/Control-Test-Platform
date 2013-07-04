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
    dMatrix3 rotationList[] = {
        { -0.9578262852211514, 0, 0.28734788556634544, 0,
                            0, 1,                   0, 0,
         -0.28734788556634544, 0, -0.9578262852211514, 0},
        {1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0},
        {  0.9578262852211514, 0, 0.28734788556634544, 0,
                            0, 1,                   0, 0,
         -0.28734788556634544, 0,  0.9578262852211514, 0}
    };

    dReal positionList[][3] ={
            {1.5, 0, 0.3/2},
            {2.5, 0, 0.3},
            {3.5, 0, 0.3/2}
    };

    for (size_t i = 0; i < LENGTH(slopes); ++i) {
        slopes[i] = new RigidBox(*world, 0.1, 1.044030650891055, 1.97, 0.001);
        slopes[i]->setColor(0.10138431372549, 0.44901960784314, 0.89607843137255);
        slopes[i]->makeGeom(*space);
        slopes[i]->setPosition(positionList[i]);
        slopes[i]->setRotation(rotationList[i]);
        slopes[i]->setKinematic();
        slopeFix[i] = new dFixedJoint(world->id(), 0);
        slopeFix[i]->attach(0, slopes[i]->id());
        slopeFix[i]->set();
    }

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
    for (size_t i = 0; i < LENGTH(slopes); ++i) {
        SAFE_DELETE(slopes[i]);
        SAFE_DELETE(slopeFix[i]);
    }

    for (size_t i = 0; i < LENGTH(cylinders); ++i) {
        SAFE_DELETE(cylinders[i]);
    }
}

void ObstacleField::drawObjects()
{
    for (size_t i = 0; i < LENGTH(slopes); ++i) {
        slopes[i]->drawInStuff();
    }

    for (size_t i = 0; i < LENGTH(cylinders); ++i) {
        cylinders[i]->drawInStuff();
    }

#define LINE_DRAW_OFFSET 0.005
    dVector3 slopeLines[][2] = {
            {{1  , 0.985,        LINE_DRAW_OFFSET}, {1  , -0.985,        LINE_DRAW_OFFSET}},
            {{1.5, 0.985, 0.15 + LINE_DRAW_OFFSET}, {1.5, -0.985, 0.15 + LINE_DRAW_OFFSET}},
            {{2  , 0.985, 0.3  + LINE_DRAW_OFFSET}, {2  , -0.985, 0.3  + LINE_DRAW_OFFSET}},
            {{2.5, 0.985, 0.3  + LINE_DRAW_OFFSET}, {2.5, -0.985, 0.3  + LINE_DRAW_OFFSET}},
            {{3  , 0.985, 0.3  + LINE_DRAW_OFFSET}, {3  , -0.985, 0.3  + LINE_DRAW_OFFSET}},
            {{3.5, 0.985, 0.15 + LINE_DRAW_OFFSET}, {3.5, -0.985, 0.15 + LINE_DRAW_OFFSET}},
            {{4  , 0.985,        LINE_DRAW_OFFSET}, {4  , -0.985,        LINE_DRAW_OFFSET}},
            {{1  , 0    , 0.00 + LINE_DRAW_OFFSET}, {2  ,  0    , 0.3  + LINE_DRAW_OFFSET}},
            {{2  , 0    , 0.30 + LINE_DRAW_OFFSET}, {3  ,  0    , 0.3  + LINE_DRAW_OFFSET}},
            {{3  , 0    , 0.30 + LINE_DRAW_OFFSET}, {4  ,  0    , 0.0  + LINE_DRAW_OFFSET}},
            {{1  , 0.5  , 0.00 + LINE_DRAW_OFFSET}, {2  ,  0.5  , 0.3  + LINE_DRAW_OFFSET}},
            {{2  , 0.5  , 0.30 + LINE_DRAW_OFFSET}, {3  ,  0.5  , 0.3  + LINE_DRAW_OFFSET}},
            {{3  , 0.5  , 0.30 + LINE_DRAW_OFFSET}, {4  ,  0.5  , 0.0  + LINE_DRAW_OFFSET}},
            {{1  , -0.5 , 0.00 + LINE_DRAW_OFFSET}, {2  , -0.5  , 0.3  + LINE_DRAW_OFFSET}},
            {{2  , -0.5 , 0.30 + LINE_DRAW_OFFSET}, {3  , -0.5  , 0.3  + LINE_DRAW_OFFSET}},
            {{3  , -0.5 , 0.30 + LINE_DRAW_OFFSET}, {4  , -0.5  , 0.0  + LINE_DRAW_OFFSET}},

    };


    dsSetColor(1,1,1);
    for (size_t i = 0; i < LENGTH(slopeLines); ++i) {
        dsDrawLine(slopeLines[i][0], slopeLines[i][1]);
    }
}

void ObstacleField::simulationStep()
{

}

bool ObstacleField::isGround(dGeomID id)
{
    for (size_t i = 0; i < LENGTH(slopes); i++) {
        if (id == slopes[i]->geomID())
            return true;
    }

    for (size_t i = 0; i < LENGTH(cylinders); i++) {
        if (id == cylinders[i]->geomID())
            return true;
    }
    
    return false;
}
