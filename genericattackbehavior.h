#ifndef GENERICATTACKBEHAVIOR_H
#define GENERICATTACKBEHAVIOR_H

#include <model/behaviors/attack.h>

class GenericAttackBehavior : public Attack {
public:
    GenericAttackBehavior(QPointer<GameObject> owner)
        : Attack(owner) {};
    // Attack interface

    int attack(const QPointer<GameObject> &target) override;
    int attack(Direction direction) override;
    int attack() override;

    int getAttacked(const QPointer<GameObject> &by, int strength) override;
};

#endif // GENERICATTACKBEHAVIOR_H
