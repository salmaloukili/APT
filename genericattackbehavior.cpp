#include <QRandomGenerator>
#include "genericattackbehavior.h"
#include "model/behaviors/health.h"
#include "model/behaviors/movement.h"
#include "publicenums.h"

int GenericAttackBehavior::attack(const QPointer<GameObject> &target) {
    // Get the strength of the object and calculate the attack
    // strength randomly.
    float strenght = m_owner->getData(DataRole::Strength).toFloat();
    int attackStrength = QRandomGenerator::global()->bounded(1, (int)strenght);

    int attacks = 0;
    for(const auto &bh : target->getAllBehaviors<Attack>()) {
        auto at = qSharedPointerDynamicCast<Attack>(bh);
        if(!bh.isNull()) {
            int healthChange = at->getAttacked(m_owner, attackStrength);
            if(healthChange + attackStrength > 0) {
                m_owner->setData(DataRole::Energy, Movement::SETTINGS::MAX_ENERGY);
            }
            attacks += healthChange;
            m_owner->setData(DataRole::Strength, strenght + 0.1);
        }
    };
    return -attacks;
}

int GenericAttackBehavior::attack(Direction direction) {
    auto neighbor = m_owner->getNeighbor(direction);
    if(!neighbor) {
        return 0;
    }
    return attack(neighbor);
}
int GenericAttackBehavior::attack() {
    return attack(m_owner->getData(DataRole::Direction).value<Direction>());
}

int GenericAttackBehavior::getAttacked(const QPointer<GameObject> &, int strength) {
    m_owner->setData(DataRole::Strength,
                     m_owner->getData()[DataRole::Strength].toFloat() - 0.1);

    auto behavior = m_owner->getBehavior<Health>();
    return behavior.isNull() ? 0 : behavior->getHealthChanged(-strength);
}
