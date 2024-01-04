#include "newlevelonstep.h"
bool NewLevelOnStep::getSteppedOn(const QPointer<GameObject> &source) {
    ObjectType srcType = source->getData(DataRole::Type).value<ObjectType>();

    if(srcType == ObjectType::Protagonist) {
        m_owner->setData(DataRole::Direction, m_owner->getData(DataRole::Direction));
    }

    return true;
}
