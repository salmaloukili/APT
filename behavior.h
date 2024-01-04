#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <QPointer>
#include <QSharedPointer>

class GameObject;
class Behavior {
public:
    Behavior(QPointer<GameObject> owner)
        : m_owner(owner) {};

    virtual ~Behavior() = 0;
    Behavior &operator=(const Behavior &) {
        return *this;
    };

protected:
    QPointer<GameObject> m_owner;
};
#endif // BEHAVIOR_H
