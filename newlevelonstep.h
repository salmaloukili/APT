#ifndef NEWLEVELONSTEP_H
#define NEWLEVELONSTEP_H

#include "genericwalkablebehavior.h"

class NewLevelOnStep : public GenericWalkableBehavior {
public:
    NewLevelOnStep(QPointer<GameObject> owner)
        : GenericWalkableBehavior(owner) {};
    bool getSteppedOn(const QPointer<GameObject> &source) override;
};

#endif // NEWLEVELONSTEP_H
