#ifndef GENERICPOISONINGBEHAVIOR_H
#define GENERICPOISONINGBEHAVIOR_H

#include <model/behaviors/poison.h>

class GenericPoisoningBehavior : public Poison {
public:
    GenericPoisoningBehavior(QPointer<GameObject> owner)
        : Poison(owner) {};

    int poison(const QPointer<GameObject> &target) override;
};

#endif // GENERICPOISONINGBEHAVIOR_H
