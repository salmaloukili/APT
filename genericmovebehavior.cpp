#include "genericmovebehavior.h"

bool GenericMoveBehavior::stepOn(QPointer<GameObject> target) {
    auto behaviors = target->getAllBehaviors<Movement>();
    bool steppable = true;

    for(const auto &bh : behaviors) {
        if(bh.isNull())
            return false;

        steppable = steppable && bh->isSteppable();
    }
    if(!steppable)
        return false;

    float energy = m_owner->getData(DataRole::Energy).toFloat();
    float targetEnergy = target->getData(DataRole::Energy).toFloat();

    if(energy - targetEnergy < 0) {
        for(const auto &neighbor : m_owner->getAllNeighbors()) {
            if(neighbor->getData(DataRole::Energy).toFloat())
                break;
            m_owner->setData(DataRole::Energy, 0);
        }
        return false;
    }

    for(const auto &bh : behaviors) {
        bh->getSteppedOn(m_owner);
    }

    m_owner->setParent(target);
    m_owner->event(new QEvent(QEvent::ParentChange));
    m_owner->setData(DataRole::Energy, energy - targetEnergy);

    return true;
}

bool GenericMoveBehavior::stepOn(Direction direction) {
    auto currentDirection = m_owner->getData(DataRole::Direction).value<Direction>();
    if(direction != currentDirection) {
        m_owner->setData(DataRole::Direction, QVariant::fromValue<Direction>(direction));
        return false;
    }

    auto neighbor = m_owner->getNeighbor(direction);
    if(!neighbor) {
        return false;
    }

    return stepOn(neighbor);
}
