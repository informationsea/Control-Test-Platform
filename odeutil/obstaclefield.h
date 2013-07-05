#ifndef _OBSTACLEFIELD_H_
#define _OBSTACLEFIELD_H_

#include "platform.h"

/** The field with slope
 *  @ingroup objectset
 */
class ObstacleField : public ObjectSet
{
public:
    ObstacleField();
    virtual ~ObstacleField();

    virtual void makeObjects();
    virtual void destroyObjects();
    virtual void drawObjects();
    virtual void simulationStep();
    virtual bool isGround(dGeomID id);
private:
    RigidCylinder *cylinders[3];
    dFixedJoint *cylindersFix[3];
};

#endif /* _OBSTACLEFIELD_H_ */


// Local variables:
// mode:c++
// End:
