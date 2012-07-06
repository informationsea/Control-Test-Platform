#include "inroffield.h"

#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#define dsDrawSphere dsDrawSphereD
#define dsDrawCylinder dsDrawCylinderD
#define dsDrawCapsule dsDrawCapsuleD
#define dsDrawLine dsDrawLineD
#endif

#define Z_OFFSET 0.02
#define Z_LINE_OFFSET (0.005 + Z_OFFSET)

InRoFField::InRoFField()
{
    static float xyz[] = {0.2, -2.5, 1};
    static float hpr[] = {90, -20, 0};
    platform_default_viewpoint(xyz, hpr);
}

InRoFField::~InRoFField()
{

}

void InRoFField::makeObjects()
{
    // main field
    field[0] = new RigidBox(*world, 1, 1.8, 1.8, 0.001);
    field[0]->setPosition(0, 0, Z_OFFSET);
    // start field
    field[1] = new RigidBox(*world, 1, 0.5, 0.5, 0.001);
    field[1]->setPosition(1.150, -.650, Z_OFFSET);
    // island
    field[2] = new RigidBox(*world, 1, 0.9, 0.28, 0.04);
    field[2]->setPosition(0.05, -0.16, 0.02 + Z_OFFSET);
    // wall
    field[3] = new RigidBox(*world, 1, 0.001, 1.8, 0.04);
    field[3]->setPosition(-0.9, 0, 0.02 + Z_OFFSET);
    field[4] = new RigidBox(*world, 1, 1.8, 0.001, 0.04);
    field[4]->setPosition(0, 0.9, 0.02 + Z_OFFSET);
    field[5] = new RigidBox(*world, 1, 0.001, 1.3, 0.04);
    field[5]->setPosition(0.9, 0.25, 0.02 + Z_OFFSET);
    field[6] = new RigidBox(*world, 1, 0.001, 0.5, 0.04);
    field[6]->setPosition(1.4, -0.65, 0.02 + Z_OFFSET);
    field[7] = new RigidBox(*world, 1, 0.5, 0.001, 0.04);
    field[7]->setPosition(1.15, -0.4, 0.02 + Z_OFFSET);
    field[8] = new RigidBox(*world, 1, 0.6, 0.001, 0.04);
    field[8]->setPosition(1.1, -0.9, 0.02 + Z_OFFSET);
    field[9] = new RigidBox(*world, 1, 0.35, 0.001, 0.04);
    field[9]->setPosition(0.325, -0.9, 0.02 + Z_OFFSET);
    field[10] = new RigidBox(*world, 1, 0.35, 0.001, 0.04);
    field[10]->setPosition(-0.325, -0.9, 0.02 + Z_OFFSET);
    field[11] = new RigidBox(*world, 1, 0.1, 0.001, 0.04);
    field[11]->setPosition(-0.85, -0.9, 0.02 + Z_OFFSET);


    for (size_t i = 0; i < LENGTH(field); ++i) {
        fieldfix[i] = new dFixedJoint(*world);
        fieldfix[i]->attach(0, field[i]->id());
        fieldfix[i]->set();

        field[i]->setColor(1, 1, 1);
        field[i]->makeGeom(*space);
        field[i]->setKinematic();
    }

    // yellow island
    field[2]->setColor(1,1,0.5);

    // yellow wall
    for (size_t i = 3; i < LENGTH(field); ++i) {
        field[i]->setColor(1, 1, 0);
    }
}

void InRoFField::destroyObjects()
{
    for (size_t i = 0; i < LENGTH(field); ++i) {
        SAFE_DELETE(field[i]);
    }
    for (size_t i = 0; i < LENGTH(fieldfix); ++i) {
        SAFE_DELETE(fieldfix[i]);
    }
}

void InRoFField::drawObjects()
{
    for (size_t i = 0; i < LENGTH(field); ++i) {
        field[i]->drawInStuff();
    }

    dVector3 slopeLines[][2] = {
            {{0.9 , -0.9, Z_LINE_OFFSET}, {0.9, -0.4, Z_LINE_OFFSET}},
            {{0.75, -0.6, Z_LINE_OFFSET}, {-0.6, -0.6, Z_LINE_OFFSET}},
            {{0.9, 0.44, Z_LINE_OFFSET}, {-0.6, 0.44, Z_LINE_OFFSET}},
            {{-0.75, -0.45, Z_LINE_OFFSET}, {-0.75, 0.29, Z_LINE_OFFSET}},
            {{0.75, -0.75, Z_LINE_OFFSET}, {0.75, -0.45, Z_LINE_OFFSET}},
            {{0, -0.75, Z_LINE_OFFSET}, {0, -0.45, Z_LINE_OFFSET}},
    };

    dsSetColor(0,0,0);
    for (size_t i = 0; i < LENGTH(slopeLines); ++i) {
        dsDrawLine(slopeLines[i][0], slopeLines[i][1]);
    }

}

void InRoFField::simulationStep()
{

}

bool InRoFField::isGround(dGeomID id)
{
    for (size_t i = 0; i < LENGTH(field); ++i) {
        if (field[i]->geomID() == id)
            return true;
    }
    return false;
}
