#ifndef GENERICMOVEBEHAVIOR_H
#define GENERICMOVEBEHAVIOR_H

#include <model/behaviors/movement.h>

class GenericMoveBehavior : public Movement {
public:
    GenericMoveBehavior(QPointer<GameObject> owner)
        : Movement(owner) {};
    bool stepOn(QPointer<GameObject> target) override;
    bool stepOn(Direction direction) override;
};

#endif // GENERICMOVEBEHAVIOR_H
