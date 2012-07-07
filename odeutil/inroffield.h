#ifndef _INROFFIELD_H_
#define _INROFFIELD_H_

#include "platform.h"

/** Intelligence Robot Contest Field
 *  @ingroup objectset
 */
class InRoFField : public ObjectSet
{
public:
    InRoFField();
    virtual ~InRoFField();

    virtual void makeObjects();
    virtual void destroyObjects();
    virtual void drawObjects();
    virtual void simulationStep();
    virtual bool isGround(dGeomID id);
private:
#define INROF_BOX_NUM 12
    RigidBox *field[INROF_BOX_NUM];
    dFixedJoint *fieldfix[INROF_BOX_NUM];

};


#endif /* _INROFFIELD_H_ */


// Local variables:
// mode:c++
// End:

