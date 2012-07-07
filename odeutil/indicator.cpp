#include "indicator.h"

#include <cmath>
#include <map>

static std::map<IndicatorID, Indicator*> indicators;
static IndicatorID last_id = 0;

extern "C" {
    void indicator_set(IndicatorID id, double value)
    {
        indicators[id]->set(value);
    }
}

Indicator::Indicator(double x, double y) :
    _x(x), _y(y), _value(0)
{
    _id = last_id;
    indicators[last_id++] = this;
}

void Indicator::drawObjects()
{
    double startpos[3] = {_x, _y, 0};
    double endpos[3]   = {_x, _y, fabs(_value)};
    if (_value < 0) {
        dsSetColor(1, 0, 0);
    } else {
        dsSetColor(0, 1, 0);
    }

    dsDrawLineD(startpos, endpos);
}
