/* -*- mode: c++ -*- */

/**
 * @file marker.h
 * @author Y.Okamura
 */


/** @defgroup marker_group Marker
 *  @ingroup objectset
 */

#ifndef MARKER_H_
#define MARKER_H_

#include <ode/ode.h>
#include "platform.h"

typedef int MarkerID;
#define NO_ANGLE -100

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Set marker position with C function.
 * @ingroup marker_group
 * @param id Marker ID
 * @param x x-axis position
 * @param y y-axis position
 * @param angle angle of marker. If you don't need angle display, please set NO_ANGLE
 */
void marker_set(MarkerID id, double x, double y, double angle);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/**
 * Draw marker.
 * This class has no other functions. Just draw marker.
 * @note This class is not thread-safe
 * @ingroup marker_group objectset
 */
class Marker: public ObjectSet
{
public:
    Marker(double red = 0, double green = 1, double blue = 0);
    virtual ~Marker();

    virtual void makeObjects(){}
    virtual void destroyObjects(){}
    virtual void drawObjects();
    virtual void simulationStep(){}

    /** Set marker position and rotation
        @param position position of marker
        @param rotation rotation of marker
    */
    void set(dVector3 position, dMatrix3 rotation);

    /** Set marker position without angle
        @param position position of marker
    */
    void set(dVector3 position);
    MarkerID id() { return _id; }

private:
    MarkerID _id;
    bool _noangle;
    dVector3 _position;
    dMatrix3 _rotation;
    double _red, _green, _blue;
};

#endif

#endif /* MARKER_H_ */
