#ifndef HEALTH_H
#define HEALTH_H

#include "behavior.h"

#include "model/gameobject.h"
#include <QSharedPointer>

class Health : public Behavior {
public:
    Health(QPointer<GameObject> owner)
        : Behavior(owner) {};

    virtual ~Health() = 0;
    Health &operator=(const Health &) {
        return *this;
    };
    static const struct SETTINGS {
        static constexpr int MAX_HEALTH = 100;
        static constexpr int MIN_HEALTH = 0;
        static constexpr int HEALTH_PACK_AMOUNT = 36;
    } Settings;

    /**
     * @brief heal
     * @param target
     * @return
     */
    virtual int heal(const QPointer<GameObject> &target) {
        return 0;
    };
    /**
     * @brief getHealthChange
     * @param amount
     * @return
     */
    virtual int getHealthChanged(int amount) {
        return 0;
    };

    /**
     * @brief getHealthChange
     * @param amount
     * @return
     */
    virtual void die() {
        return;
    };
};

#endif // HEALTH_H
