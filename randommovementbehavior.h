#ifndef RANDOMMOVEMENTBEHAVIOR_H
#define RANDOMMOVEMENTBEHAVIOR_H

#include "genericmovebehavior.h"
#include <QObject>

class RandomMovementBehavior : public QObject, public GenericMoveBehavior {
    Q_OBJECT
public:
    RandomMovementBehavior(QPointer<GameObject> owner)
        : GenericMoveBehavior(owner) {
        connect(owner, &GameObject::tick, this, &RandomMovementBehavior::moveRandomly);
    };
public slots:
    void moveRandomly();
};

#endif // RANDOMMOVEMENTBEHAVIOR_H
