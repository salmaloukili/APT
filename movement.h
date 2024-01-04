#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "behavior.h"

#include <model/gameobject.h>

#include <QSharedPointer>

class Movement : public Behavior {
public:
    Movement(QPointer<GameObject> owner)
        : Behavior(owner) {};

    virtual ~Movement() = 0;
    Movement &operator=(const Movement &) {
        return *this;
    };
    static const struct SETTINGS {
        static constexpr int MAX_ENERGY = 100;
    } Settings;

    /**
     * @brief stepOn
     * @param target
     * @return
     */
    virtual bool stepOn(const QPointer<GameObject> target) {
        return 0;
    };
    /**
     * @brief stepOn
     * @param direction
     * @return
     */
    virtual bool stepOn(Direction direction) {
        return 0;
    };
    /**
     * @brief isStepable
     * @return
     */
    virtual bool isSteppable() {
        return 0;
    };
    /**
     * @brief getSeppedOn
     * @param source
     * @return
     */
    virtual bool
    getSteppedOn(const QPointer<GameObject> &source) {
        return 0;
    };
};

#endif // MOVEMENT_H
