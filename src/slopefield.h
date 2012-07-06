#ifndef _SlopeFIELD_H_
#define _SlopeFIELD_H_

#include "platform.h"

/** The field with slope
 *  @ingroup objectset
 */
class SlopeField : public ObjectSet
{
public:
    SlopeField();
    virtual ~SlopeField();

    virtual void makeObjects();
    virtual void destroyObjects();
    virtual void drawObjects();
    virtual void simulationStep();
    virtual bool isGround(dGeomID id);
private:
    RigidBox *slopes[3];
    dFixedJoint *slopeFix[3];

};

#endif /* _SlopeFIELD_H_ */


// Local variables:
// mode:c++
// End:

