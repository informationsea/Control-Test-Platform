/* -*- mode: c++ -*- */

/** @file indicator.h
 *  @author Y.Okamura
 *  
 */

/** @defgroup indicator_group Indicator
 *  @ingroup objectset
 */

#ifndef _INDICATOR_H_
#define _INDICATOR_H_

#include <ode/ode.h>
#include "platform.h"

typedef int IndicatorID;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @ingroup indicator_group
 */
    void indicator_set(IndicatorID id, double value);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/**
 * Draw indicator.
 * This class has no other functions. Just draw indicator.
 * @note This class is not thread-safe
 * @ingroup indicator_group objectset
 */
class Indicator: public ObjectSet
{
  public:
    Indicator(double x, double y);
    virtual ~Indicator(){}

    virtual void makeObjects(){}
    virtual void destroyObjects(){}
    virtual void drawObjects();
    virtual void simulationStep(){}
    
    void set(double value) { _value = value; }
    IndicatorID id() { return _id; }

  private:
    IndicatorID _id;
    double _x,_y;
    double _value;
};

#endif

#endif /* _INDICATOR_H_ */


