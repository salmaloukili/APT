#ifndef ATTACK_H
#define ATTACK_H

#include <QSharedPointer>

#include <model/gameobject.h>

class Attack : public Behavior {
public:
    Attack(QPointer<GameObject> owner)
        : Behavior(owner) {};
    virtual ~Attack() = 0;
    static const struct SETTINGS {
        static constexpr int PLAYER_STRENGTH = 30;
        static constexpr int ENEMY_STRENGTH = 5;

    } Settings;

    Attack &operator=(const Attack &) { return *this; };

    /**
     * @brief attack
     * @param target
     * @return
     */
    virtual int attack(const QPointer<GameObject> &target) = 0;
    /**
     * @brief attack
     * @param target
     * @return
     */
    virtual int attack(Direction direction) = 0;
    /**
     * @brief attack
     * @return
     */
    virtual int attack() = 0;

    /**
     * @brief getAttacked
     * @param strength
     * @return
     */
    virtual int getAttacked(const QPointer<GameObject> &by, int strength) = 0;
};

#endif // ATTACK_H
