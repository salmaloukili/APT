#ifndef POISON_H
#define POISON_H

#include "behavior.h"

#include "model/gameobject.h"

#include <QSharedPointer>

class Poison : public Behavior {
public:
    Poison(QPointer<GameObject> owner)
        : Behavior(owner) {};

    virtual ~Poison() = 0;
    const static struct SETTINGS {
        // Max/Min allowed amount of poison for a Game Object to get during gameplay.
        constexpr static int MAX_POISON = 100;
        constexpr static int MIN_POISON = 0;

        // Min that Game Object will poison per tick/action.
        constexpr static int MIN_POISON_PER_ACTION = 2;
        // How much a Game Object will poison per tick/action.
        constexpr static int MAX_POISON_PER_ACTION = 10;
        // How many times a PEnemy will spread its poison.
        constexpr static int POISON_SPREAD_TIMES = 3;
        // The Min ticks between poison spread
        constexpr static int POISON_SPREAD_MIN_TICKS = 5;
        // The Max ticks between poison spread
        constexpr static int POISON_SPREAD_MAX_TICKS = 10;
        // How much damage poison does per tick.
        constexpr static int DAMAGE_PER_TICK = 1;
        // Yay for the geometric formula, ensures the PEnemy has enough poison to get all the neighbors.
        constexpr static int PENEMY_POISON_LEVEL = (MAX_POISON_PER_ACTION * 8 * (1 - POISON_SPREAD_TIMES * POISON_SPREAD_TIMES) / (1 - POISON_SPREAD_TIMES));

    } Settings;

    Poison &operator=(const Poison &) {
        return *this;
    };
    /**
     * @brief poison
     * @param target
     * @return
     */
    virtual int poison(const QPointer<GameObject> &target) {
        return 0;
    };
    /**
     * @brief getPoisoned
     * @param level
     * @return
     */
    virtual int getPoisoned(int level);
    ;
    /**
     * @brief getPoisoned
     * @param level
     * @return
     */
    virtual int clearPoison(int level) {
        return 0;
    };
};

#endif // POISON_H
