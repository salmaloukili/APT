#ifndef GENERICPOISONABLEBEHAVIOR_H
#define GENERICPOISONABLEBEHAVIOR_H

#include <model/behaviors/poison.h>

class GenericPoisonableBehavior : public QObject, public Poison {
    Q_OBJECT
public:
    GenericPoisonableBehavior(QPointer<GameObject> owner)
        : Poison(owner) {
        connect(owner, &GameObject::tick, this, &GenericPoisonableBehavior::poisonEffect);
    };

public slots:
    void poisonEffect();
};

#endif // GENERICPOISONABLEBEHAVIOR_H
