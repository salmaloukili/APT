#include "generichealthbehavior.h"

int GenericHealthBehavior::getHealthChanged(int amount) {
    QVariant currentHealth = m_owner->getData(DataRole::Health);
    if(currentHealth.isNull()) {
        throw("Cannot change health of object without health");
    }
    if(currentHealth == Settings.MAX_HEALTH && amount > 0) {
        return 0;
    }
    int newHealth = currentHealth.toInt() + amount;

    if(newHealth <= 0) {
        m_owner->setData(DataRole::Health, 0);
        die();
        return 0;
    } else if(newHealth > Settings.MAX_HEALTH) {
        newHealth = Settings.MAX_HEALTH;
    }

    m_owner->setData(
      DataRole::Health, QVariant(newHealth));

    return newHealth - currentHealth.toInt();
}

void GenericHealthBehavior::die() {
    delete m_owner;
}
