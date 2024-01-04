#ifndef COUNTERATTACKBEHAVIOR_H
#define COUNTERATTACKBEHAVIOR_H

#include "genericattackbehavior.h"

class CounterAttackBehavior : public GenericAttackBehavior {
public:
    CounterAttackBehavior(QPointer<GameObject> owner)
        : GenericAttackBehavior(owner) {};

    // Attack interface
public:
    int getAttacked(const QPointer<GameObject> &by, int strength) override;
};

#endif // COUNTERATTACKBEHAVIOR_H
