#include "healonstepbehavior.h"

#include <model/behaviors/health.h>

bool HealOnStepBehavior::getSteppedOn(const QPointer<GameObject> &source) {
    return m_owner->getBehavior<Health>()->heal(source);
}
