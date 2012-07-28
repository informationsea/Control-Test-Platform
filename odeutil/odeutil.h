#ifndef _ODELIB_H_
#define _ODELIB_H_

/** @defgroup ode_support Open Dyanamics Engine Support
 */

/** @file odeutil.h
 *  Open Dynamics Engine Support Library.
 *  You can use ODE easily with this library.
 *  @author Y.Okamura
 */

#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#include "config.h"

#ifndef LENGTH
/**
 * Calculate length of array.
 * @ingroup ode_support
 */
#define LENGTH(x) (sizeof(x)/sizeof(x[0]))
#endif

#ifndef foreach
/**
 * For each.
 * @note You have to declare integer variable 'i' before use this.
 * @ingroup ode_support
 */
#define foreach(x) for(i = 0; i < LENGTH(x); ++i)
#endif

#ifndef DRAWSTUFF_TEXTURE_PATH
/** Drawsutff texture path.
 *  You can change this by -D option.
 *  @ingroup ode_support
 */
#error "Did you configured?"
// #define DRAWSTUFF_TEXTURE_PATH "/usr/local/share/drawstuff"
#endif

struct RotationAngles {
    dReal phi;
    dReal theta;
    dReal psi;
};

#ifdef __cplusplus
extern "C" {
#endif

/** constant delay.
 *  You can use this function to fix frame rate.
 *  @ingroup ode_support
 *  @param sec seconds
 */
void const_delay(double sec);

/** Rotate and move a object.
 *  @ingroup ode_support
 *  @param body BodyID
 *  @param offset move
 *  @param rotation Rotation matrix
 */
void rotate_object(dBodyID body, const dVector3 offset, const dMatrix3 rotation);

/**
 * Get rollPitchYaw from rotation matrix.
 * http://demura.net/9ode/511.html
 * @warning buggy. I didn't check results.
 * @param rotation Rotation matrix
 * @return angles
 */
struct RotationAngles get_angles(const dMatrix3 rotation);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <ode/odecpp.h>
#include <ode/odecpp_collision.h>


/** Rigid Body.
 *  Super class of bodies.
 *  @see RigidSphere
 *  @see RigidCylinder
 *  @see RigidBox
 *  @ingroup ode_support
 */
class RigidBody : public dBody
{
public:
    /** Constructor of rigid body.
     *  Use this if you don't like odecpp library
     *  @param world world id
     */
    RigidBody(dWorldID world);

    /** Constructor of rigid body.
     *  Use this if you like odecpp library
     *  @param world world object
     */
    RigidBody(dWorld& world);

    virtual ~RigidBody();


    /** Draw a object with drawstuff.
     *  You have to implement this method.
     */
    virtual void drawInStuff() = 0;

    /** Set color.
     *  Use this color to draw a object.
     *  You have to use this color when you implement drawInStuff()
     *  @param r Red  (0.0 - 1.0)
     *  @param g Gree  (0.0 - 1.0)
     *  @param b Blue  (0.0 - 1.0)
     *  @see _r
     *  @see _g
     *  @see _b
     */
    virtual void setColor(float r,float g,float b) {
        _r = r; _g = g;	_b = b;
    }

    /** Set texture of object.
     *  You have to use this texture when you implement drawInStuff()
     *  @param newtexture New texture. One of DS_NONE, DS_WOOD, DS_CHECKERED, DS_GROUND, DS_SKY
     *  @see _texture
     */
    virtual void setTexture(enum DS_TEXTURE_NUMBER newtexture) {
        _texture = newtexture;
    }

    /** Set total mass of this object.
     *  @see setDensity
     *  @see _mass
     */
    virtual void setTotalMass(dReal newmass);

    /** Set density of this object.
     *  @see setTotalMass
     *  @see _density
     */
    virtual void setDensity(dReal density);

    /** Make geometory to collision test.
     *  @see makeGeom
     *  @see haveGeom
     *  @see geom
     *  @see geomID
     */
    virtual void makeGeom(dSpaceID space) = 0;

    /** Make geometory to collision test.
     */
    virtual void makeGeom(const dSpace &space) { makeGeom(space.id()); }

    /** Check this object has geometory.
     *  @return true if this has geometory.
     */
    virtual bool haveGeom();

    /** get geometory object
     *  @see geomID
     */
    virtual dGeom* geom() { return _geom; }

    /** get geometory ID
     *  @see geom
     */
    virtual dGeomID geomID() { return _geom ? _geom->id() : 0; }

protected:
    float _r,_g,_b;
    enum DS_TEXTURE_NUMBER _texture;

    dGeom *_geom;

    dReal _mass,_density;
    dMass _dmass;

    /** Set mass parameter.
     *  Set mass parameter from _mass and _density.
     *  Only one of _mass or _density is larger than zero, so you have to set mass parameter with it
     */
    virtual void setMassParameter() = 0;
};

/** Rigid Sphere.
 *
 *  @ingroup ode_support
 */

class RigidSphere : public RigidBody
{
public:
    RigidSphere(dWorldID world,dReal newmass,dReal radius);
    RigidSphere(dWorld &world,dReal newmass,dReal radius);
    virtual ~RigidSphere();

    /** Set radius.
     *  Change radius of this object.
     */
    void setRadius(dReal radius);
    virtual void makeGeom(dSpaceID space);
    virtual void drawInStuff();
private:
    dReal _radius;
protected:
    virtual void setMassParameter();
};

/** Rigid Cylinder.
 *  @warning a parameter, direction, has no effect.
 *  @ingroup ode_support
 */

class RigidCylinder : public RigidBody
{
public:
    /**
     * Constructor of Rigid Cylinder
     *  @warning a parameter, direction, has no effect.
     * @param world World
     * @param newmass Toal mass.
     * @param direction No effect.
     * @param radius Radius
     * @param length Length
     */
    RigidCylinder(dWorld &world,dReal newmass,int direction, dReal radius, dReal length);
    RigidCylinder(dWorldID world,dReal newmass,int direction, dReal radius, dReal length);
    virtual ~RigidCylinder();

    void setCylinderParameter(int direction, dReal radius, dReal length);
    virtual void drawInStuff();
    virtual void makeGeom(dSpaceID space);
protected:
    virtual void setMassParameter();
private:
    int _direction;
    dReal _radious;
    dReal _length;
};


/** Ridid Box.
 *
 *  @ingroup ode_support
 */
class RigidBox : public RigidBody
{
public:
    RigidBox(dWorldID world,dReal newmass,dReal lx,dReal ly,dReal lz);
    RigidBox(dWorld &world,dReal newmass,dReal lx,dReal ly,dReal lz);
    virtual ~RigidBox();

    void setSize(dReal lx,dReal ly,dReal lz);

    virtual void makeGeom(dSpaceID space);

    virtual void drawInStuff();
private:
    dReal _l[3];
protected:
    virtual void setMassParameter();
};
#endif

#endif /* _ODELIB_H_ */


// Local variables:
// mode:c++
// End:
