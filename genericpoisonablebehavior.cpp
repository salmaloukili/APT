#include "genericpoisonablebehavior.h"
#include "model/behaviors/health.h"

void GenericPoisonableBehavior::poisonEffect() {
    QVariant poisonLevel = m_owner->getData(DataRole::PoisonLevel);
    auto behavior = m_owner->getBehavior<Health>();

    if(!(poisonLevel.isValid() && behavior && poisonLevel.toInt())) {
        return;
    }

    int newPoison = poisonLevel.toInt() - Settings.DAMAGE_PER_TICK;
    if(newPoison > Settings.MIN_POISON) {
        behavior->getHealthChanged(-Settings.DAMAGE_PER_TICK);
        m_owner->setData(DataRole::PoisonLevel, newPoison);

    } else {
        m_owner->setData(DataRole::PoisonLevel, 0);
    }
}
