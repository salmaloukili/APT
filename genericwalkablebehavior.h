#ifndef GENERICWALKABLEBEHAVIOR_H
#define GENERICWALKABLEBEHAVIOR_H

#include <model/behaviors/movement.h>

class GenericWalkableBehavior : public Movement {
public:
    GenericWalkableBehavior(QPointer<GameObject> owner)
        : Movement(owner) {};

    // Movement interface
public:
    bool isSteppable() override { return true; };
};

#endif // GENERICWALKABLEBEHAVIOR_H
