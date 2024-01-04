#ifndef GENERICHEALINGBEHAVIOR_H
#define GENERICHEALINGBEHAVIOR_H

#include <model/behaviors/health.h>
#include <model/behaviors/movement.h>

class GenericHealingBehavior : public Health {
public:
    GenericHealingBehavior(QPointer<GameObject> owner)
        : Health(owner) {};

    // Health interface
public:
    int heal(const QPointer<GameObject> &target) override;
};

#endif // GENERICHEALINGBEHAVIOR_H
