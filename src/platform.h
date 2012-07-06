/** @file platform.h
 *  Control Test Platform.
 *  @author Y.Okamura
 */

/** @defgroup platform Platform
 */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <ode/ode.h>
#include "odeutil.h"

/** Gravity.
 *  Default gravity
 *  @ingroup platform
 */
#define GRAVITY (-9.8)
#ifndef LENGTH
/** Get length of array.
 *  @ingroup ode_support
 */
#define LENGTH(x) (sizeof(x)/sizeof(x[0]))
#endif

/** Simulation step
 *  @ingroup platfrom
 */
#define STEP_SIZE 0.01
#define SIMULATION_TIMES 5

/**
 * Print dMatrix3.
 * @ingroup platform
 */
void printMatrix3(const dMatrix3 matrix);

#ifdef __cplusplus

#define SAFE_DELETE(x) {delete x; x = 0;}

extern "C"{
#endif
/** Initialize controller.
 *  You have to implement this function.
 *  Call this from platform_start()
 * @ingroup platform
 */
void controller_initialize(void);

/** Simulation step.
 *  You have to implement this function.
 *  Call this from platform_start()
 * @ingroup platform
 */
void controller_simulation_step(void);

/** Receive key event.
 *  You have to implement this function.
 *  Call this from platform_start()
 * @ingroup platform
 */
void controller_key_event(int key);

/** Finalizer.
 *  You have to implement this function.
 *  Call this from platform_start()
 * @ingroup platform
 */
void controller_finalize(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/** @defgroup objectset Object Set Group
 *  @ingroup platform
 */


/** make, destroy, draw objects
 *  This class contatins robot, field and so on.
 *  @ingroup objectset
 */

class ObjectSet
{
protected:
    dWorld *world;
    dSpace *space;
public:
    /** Constructor of ObjectSet.
     *  Don't create objects in the constructor.
     *  You can create objects in makeObjects()
     */
    ObjectSet(){}
    virtual ~ObjectSet(){}

    /** Set world object.
     *  You have to call this method before you call makeObjects()
     */
    void setWorld(dWorld *newworld){world = newworld;}

    /** Set space object.
     *  You have to call this method before you call makeObjects()
     */
    void setSpace(dSpace *newspace){space = newspace;}


    /** Make objects.
     *  You have to set world and space before you call this method.
     *  This is abstract method. You have to create objects in this.
     */
    virtual void makeObjects() = 0;

    /** Destroy objects.
     *  This is abstract method. You have to remove all objects from world and space
     */
    virtual void destroyObjects() = 0;

    /** Draw objects.
     *  This is abstract method. You have to draw objects in this.
     *  You can draw objects not in world and space, you don't have to draw all objects
     */
    virtual void drawObjects() = 0;

    /** step.
     *  This method is called every step of simulation
     */
    virtual void simulationStep(){}

    /** Is this geom id ground?
     *  You have to check that your object contains supplied id.
     *  Collision test use this value.
     *  Only ground objects and non-ground objects can be conflicted.
     *  @return return true if this object is ground.
     */
    virtual bool isGround(dGeomID /*id*/){return false;}
};

/** Initialize test platform.
 *  Call this function before you touch ODE functions.
 *  This function intialize Open Dynamics Engine.
 */
void platform_initialize(void);

/** Add ObjectSet.
 *  Call platform_initialize first.
 *  @see platform_initialize
 */
void platform_add_objectset(ObjectSet *objectSet);

/** Start test platform.
 *  Start simulation. You have to initialize and add object sets before call this.
 *  @see platform_initialize
 *  @see platform_add_objectset
 */
void platform_start(int argc, char *argv[]);

/** Set default viewpoint.
 */
void platform_default_viewpoint(float xyz[3], float hpr[3]);

#endif


#endif /* _PLATFORM_H_ */


// Local variables:
// mode:c++
// End:
