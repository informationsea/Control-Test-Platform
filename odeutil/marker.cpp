/*
 * marker.cpp
 *
 *  Created on: 2011/12/11
 *      Author: yasu
 */
#include "marker.h"

#include <cmath>
#include <map>

#ifdef dDOUBLE
#define dsDrawLine dsDrawLineD
#endif

#define DEFAULT_Z 0.5

static std::map<MarkerID, Marker*> markers;
static MarkerID last_id = 0;

static const dMatrix3 positions_with_angle[] = {
    {0, 0, 0},
    {0.1, 0, 0},
    {-0.1, -0.1, 0},
    {-0.1, 0.1, 0},
    {0.1, 0, 0},
};

#define MARKER_SIZE 0.1
static const dMatrix3 positions_without_angle[] = {
    {sin(0*M_PI/8)*MARKER_SIZE, cos(0*M_PI/8)*MARKER_SIZE, 0},
    {sin(1*M_PI/8)*MARKER_SIZE, cos(1*M_PI/8)*MARKER_SIZE, 0},
    {sin(2*M_PI/8)*MARKER_SIZE, cos(2*M_PI/8)*MARKER_SIZE, 0},
    {sin(3*M_PI/8)*MARKER_SIZE, cos(3*M_PI/8)*MARKER_SIZE, 0},
    {sin(4*M_PI/8)*MARKER_SIZE, cos(4*M_PI/8)*MARKER_SIZE, 0},
    {sin(5*M_PI/8)*MARKER_SIZE, cos(5*M_PI/8)*MARKER_SIZE, 0},
    {sin(6*M_PI/8)*MARKER_SIZE, cos(6*M_PI/8)*MARKER_SIZE, 0},
    {sin(7*M_PI/8)*MARKER_SIZE, cos(7*M_PI/8)*MARKER_SIZE, 0},
    {sin(8*M_PI/8)*MARKER_SIZE, cos(8*M_PI/8)*MARKER_SIZE, 0},
    {sin(9*M_PI/8)*MARKER_SIZE, cos(9*M_PI/8)*MARKER_SIZE, 0},
    {sin(10*M_PI/8)*MARKER_SIZE, cos(10*M_PI/8)*MARKER_SIZE, 0},
    {sin(11*M_PI/8)*MARKER_SIZE, cos(11*M_PI/8)*MARKER_SIZE, 0},
    {sin(12*M_PI/8)*MARKER_SIZE, cos(12*M_PI/8)*MARKER_SIZE, 0},
    {sin(13*M_PI/8)*MARKER_SIZE, cos(13*M_PI/8)*MARKER_SIZE, 0},
    {sin(14*M_PI/8)*MARKER_SIZE, cos(14*M_PI/8)*MARKER_SIZE, 0},
    {sin(15*M_PI/8)*MARKER_SIZE, cos(15*M_PI/8)*MARKER_SIZE, 0},
};

extern "C" {
void marker_set(MarkerID id, double x, double y, double angle)
{
    dVector3 position;
    position[0] = x;
    position[1] = y;
    position[2] = DEFAULT_Z;

    if (angle > NO_ANGLE) {
        dMatrix3 rotation;
        dRFromEulerAngles(rotation, 0, 0, angle);
        markers[id]->set(position, rotation);
    } else {
        markers[id]->set(position);
    }
}
}

Marker::Marker(double red, double green, double blue) : _noangle(false), _red(red), _green(green), _blue(blue)
{
    markers[last_id] = this;
    _id = last_id++;

    size_t i;
    foreach(_position) {
        _position[i] = 0;
    }
    _position[2] = DEFAULT_Z;

    dRSetIdentity(_rotation);
}

Marker::~Marker()
{
    markers.erase(_id);
}

void Marker::drawObjects()
{
    dsSetColor(_red, _green, _blue);

    size_t length;
    const dMatrix3 *positions;
    if (_noangle) {
        length = LENGTH(positions_without_angle);
        positions = positions_without_angle;
    } else {
        length = LENGTH(positions_with_angle);
        positions = positions_with_angle;
    }
    
    dReal rotatedPositions[length][3];

    for (size_t i = 0; i < length; ++i) {
        if (!_noangle) {
            dMultiply0(rotatedPositions[i], _rotation, positions[i], 3, 3, 1);
            for(size_t j = 0; j < 3; ++j) {
                rotatedPositions[i][j] += _position[j];
            }
        } else {
            for(size_t j = 0; j < 3; ++j) {
                rotatedPositions[i][j] = _position[j] + positions[i][j];
            }
        }
    }

    for (size_t i = 0; i < length; ++i) {
        size_t next = ((i == length - 1) ? 0 : i+1);
        dsDrawLine(rotatedPositions[i], rotatedPositions[next]);
    }
}


void Marker::set(dVector3 position, dMatrix3 rotation)
{
    size_t i;
    foreach(_position) {
        _position[i] = position[i];
    }
    foreach(_rotation) {
        _rotation[i] = rotation[i];
    }
}


void Marker::set(dVector3 position)
{
    size_t i;
    foreach(_position) {
        _position[i] = position[i];
    }
    _noangle = true;
}
