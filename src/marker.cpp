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

#define DEFAULT_Z 0.2

static std::map<MarkerID, Marker*> markers;
static MarkerID last_id = 0;

extern "C" {
void marker_set(MarkerID id, double x, double y, double angle)
{
    dMatrix3 rotation;
    dVector3 position;
    dRFromEulerAngles(rotation, 0, 0, angle);
    position[0] = x;
    position[1] = y;
    position[2] = DEFAULT_Z;
    markers[id]->set(position, rotation);
}
}

Marker::Marker(double red, double green, double blue) : _red(red), _green(green), _blue(blue)
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

void Marker::drawObjects()
{
    dsSetColor(_red, _green, _blue);
    dReal positions[][3] = {
            {0, 0, 0},
            {0.1, 0, 0},
            {-0.1, -0.1, 0},
            {-0.1, 0.1, 0},
            {0.1, 0, 0},
    };
    dReal rotatedPositions[LENGTH(positions)][3];

    size_t i;
    foreach(positions) {
        dMultiply0(rotatedPositions[i], _rotation, positions[i], 3, 3, 1);
        for(size_t j = 0; j < LENGTH(rotatedPositions[0]); ++j) {
            rotatedPositions[i][j] += _position[j];
        }
    }

    foreach(positions) {
        size_t next = ((i == LENGTH(positions) - 1) ? 0 : i+1);
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

