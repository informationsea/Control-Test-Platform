#include <vector>

#include "platform.h"

static int number_of_steps;

static dWorld *world;
static dSpace *space;
static dPlane *ground;
static dJointGroup *contactGroup;

static bool enableConstDelay;
static bool enableTopView;
static int simulationPerDraw;

static std::vector<ObjectSet *> objectSets;

static void start();
static void command(int cmd);
static void simLoop(int pause);
static void stop();
static void nearCallback (void *data, dGeomID o1, dGeomID o2);

void platform_initialize(void)
{
    dInitODE();
    world = new dWorld;
    world->setGravity(0,0,GRAVITY);
    world->setCFM(0.001);
    world->setERP(0.2);

    space = new dHashSpace;
    ground = new dPlane(*space, 0, 0, 1, 0);
    contactGroup = new dJointGroup();
    enableTopView = false;

    number_of_steps = 0;
}

void platform_add_objectset(ObjectSet *objectSet)
{
    objectSet->setWorld(world);
    objectSet->setSpace(space);
    objectSets.push_back(objectSet);
}

void platform_start(int argc, char *argv[])
{
    for (std::vector<ObjectSet *>::iterator it = objectSets.begin();
            it != objectSets.end(); ++it) {
        (*it)->makeObjects();
    }

    dsFunctions fn;
    fn.version = DS_VERSION;
    fn.version = DS_VERSION;
    fn.start = &start;
    fn.step = &simLoop;
    fn.command = &command;
    fn.stop = &stop;
    fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH;

    dsSimulationLoop (argc,argv,600,400,&fn);

    for (std::vector<ObjectSet *>::iterator it = objectSets.begin();
            it != objectSets.end(); ++it) {
        (*it)->destroyObjects();
    }

    delete contactGroup;
    delete ground;
    delete space;
    delete world;
    dCloseODE();
}

static float default_xyz[3] = {1, -5, 2};
static float default_hpr[3] = {90, -20, 0};

void platform_default_viewpoint(float xyz[3], float hpr[3])
{
    for (size_t i = 0; i < LENGTH(default_xyz); ++i) {
        default_xyz[i] = xyz[i];
    }
    for (size_t i = 0; i < LENGTH(default_hpr); ++i) {
        default_hpr[i] = hpr[i];
    }
}

static void start()
{
    dsSetViewpoint (default_xyz, default_hpr);

    printf("Key commands : \n"
            "r : reset world\n"
            "t : disable/enable const delay\n"
            "y : Fast simulation\n"
            "u : toggle top view\n");
    enableConstDelay = true;
    simulationPerDraw = 5;

    controller_initialize();
}

static void command(int cmd)
{
    switch(cmd) {
    case 'r':
        for (std::vector<ObjectSet *>::iterator it = objectSets.begin();
                it != objectSets.end(); ++it) {
            (*it)->destroyObjects();
        }
        for (std::vector<ObjectSet *>::iterator it = objectSets.begin();
                it != objectSets.end(); ++it) {
            (*it)->makeObjects();
        }
        break;
    case 't':
        if (simulationPerDraw > 5)
            enableConstDelay = false;
        else
            enableConstDelay = !enableConstDelay;
        if (enableConstDelay) {
            printf("Const delay is enabled\n");
        } else {
            printf("Const delay is disabled\n");
        }
        break;
    case 'y':
        if (simulationPerDraw > 5) {
            simulationPerDraw = 5;
        } else {
            simulationPerDraw = 200;
            enableConstDelay = false;
        }
        break;
    case 'u':{
        enableTopView = !enableTopView;
        if (enableTopView) {
            float xyz[3] = {0, 0, 3};
            float hpr[3] = {90, -90, 0};
            dsSetViewpoint(xyz, hpr);
        } else {
            dsSetViewpoint (default_xyz, default_hpr);
        }
        break;
    }
    default:
        controller_key_event(cmd);
        break;
    }
}

static void simLoop(int pause)
{
    if (!pause) {
        for (int j = 0; j < simulationPerDraw; ++j){
            controller_simulation_step();

            for (std::vector<ObjectSet *>::iterator it = objectSets.begin();
                    it != objectSets.end(); ++it) {
                (*it)->simulationStep();
            }

            dSpaceCollide (space->id(),0,&nearCallback);
            world->step(STEP_SIZE);
            number_of_steps++;
            contactGroup->empty();
        }
        /*
        if (number_of_steps % 50 == 0)
            printf("Time %lf\n", number_of_steps * STEP_SIZE);
            */
    }

    if (enableConstDelay)
        const_delay(STEP_SIZE*simulationPerDraw);

    for (std::vector<ObjectSet *>::iterator it = objectSets.begin();
            it != objectSets.end(); ++it) {
        (*it)->drawObjects();
    }
}

static void stop()
{
    controller_finalize();
}

static bool isGround(dGeomID id)
{
    if (id == ground->id())
        return true;
    for (std::vector<ObjectSet *>::iterator it = objectSets.begin();
            it != objectSets.end(); ++it) {
        if ((*it)->isGround(id))
            return true;
    }

    return false;
}

static void nearCallback (void */*data*/, dGeomID o1, dGeomID o2)
{
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    dContact contact;

    if ((isGround(o1) && isGround(o2)) ||
            (!isGround(o1) && !isGround(o2)))
        return;

    contact.surface.mode = dContactSoftCFM | dContactSoftERP;
    // friction parameter
    contact.surface.mu = dInfinity;
    // bounce is the amount of "bouncyness".
    contact.surface.bounce = 0.1;
    // bounce_vel is the minimum incoming velocity to cause a bounce
    contact.surface.bounce_vel = 0.1;
    // constraint force mixing parameter
    contact.surface.soft_cfm = 0.001;
    contact.surface.soft_erp = 0.8;
    if (dCollide (o1,o2,1,&contact.geom,sizeof(dContact))) {
        dJointID c = dJointCreateContact (world->id(),contactGroup->id(),&contact);
        dJointAttach (c,b1,b2);
    }
}

void printMatrix3(const dMatrix3 matrix)
{
    printf ("%lf %lf %lf %lf\n"
            "%lf %lf %lf %lf\n"
            "%lf %lf %lf %lf\n",
            matrix[0], matrix[1], matrix[2], matrix[3],
            matrix[4], matrix[5], matrix[6], matrix[7],
            matrix[8], matrix[9], matrix[10],matrix[11]);
}
