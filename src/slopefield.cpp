#include "slopefield.h"

#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawSphere dsDrawSphereD
#define dsDrawCylinder dsDrawCylinderD
#define dsDrawCapsule dsDrawCapsuleD
#define dsDrawLine dsDrawLineD
#endif

SlopeField::SlopeField()
{

}

SlopeField::~SlopeField()
{

}

void SlopeField::makeObjects()
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
}

void SlopeField::destroyObjects()
{
    for (size_t i = 0; i < LENGTH(slopes); ++i) {
        SAFE_DELETE(slopes[i]);
        SAFE_DELETE(slopeFix[i]);
    }
}

void SlopeField::drawObjects()
{
    for (size_t i = 0; i < LENGTH(slopes); ++i) {
        slopes[i]->drawInStuff();
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

void SlopeField::simulationStep()
{

}

bool SlopeField::isGround(dGeomID id)
{
    for (size_t i = 0; i < 3; i++) {
        if (id == slopes[i]->geomID())
            return true;
    }
    return false;
}
