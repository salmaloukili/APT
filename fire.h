#ifndef FIRE_H
#define FIRE_H

#include "behavior.h"

#include <QSharedPointer>
#include <model/gameobject.h>

class Fire : public Behavior {
public:
    Fire(QPointer<GameObject> owner)
        : Behavior(owner) {};

    virtual ~Fire() = 0;
    Fire &operator=(const Fire &) {
        return *this;
    };
    /**
     * @brief setOnFire
     * @param target
     * @return
     */
    virtual int setOnFire(const QPointer<GameObject> &target) = 0;
    /**
     * @brief extinguish
     * @param target
     * @return
     */
    virtual int extinguish(const QPointer<GameObject> &target) = 0;
    /**
     * @brief getSetOnFire
     * @return
     */
    virtual int getSetOnFire() = 0;
    /**
     * @brief getExtinguished
     * @return
     */
    virtual int getExtinguished() = 0;
};

#endif // FIRE_H
