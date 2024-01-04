#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QEvent>
#include <QPointer>
#include <QVariant>
#include <typeindex>

#include "publicenums.h"
#include "model/behaviors/behavior.h"

class GameObject : public QObject {
    Q_OBJECT
public:
    GameObject(QMap<DataRole, QVariant> objectData)
        : m_objectData(objectData) {};
    GameObject() { m_objectData = QMap<DataRole, QVariant>(); };

    ~GameObject() {};
    // Extra child getter
    const QPointer<GameObject> findChild(ObjectType type);

    // Data getters and setters.
    QVariant getData(DataRole role) const;
    QMap<DataRole, QVariant> getData() const;
    QList<QMap<DataRole, QVariant>> getAllData(bool self = true) const;

    void setData(DataRole role, QVariant value);
    void setData(QList<QPair<DataRole, QVariant>> data);

    // Neighbors getters and setters.
    const QList<QPointer<GameObject>> getAllNeighbors(int offset = 0) const;
    const QPointer<GameObject> getNeighbor(double direction, int offset = 0) const;
    const QPointer<GameObject> getNeighbor(Direction direction, int offset = 0) const;

    // Behavior getters and setters
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    void setBehavior(QSharedPointer<T> behavior) {
        m_behaviors[typeid(T)] = behavior;
    }

    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    QSharedPointer<T> getBehavior() const {
        auto behavior = m_behaviors[typeid(T)];
        return qSharedPointerDynamicCast<T>(behavior);
    }
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    void removeBehavior() {
        m_behaviors.remove(typeid(T));
    }
    template <typename T, typename = std::enable_if<std::is_base_of<Behavior, T>::value>::type>
    const QList<QSharedPointer<T>> getAllBehaviors() const {
        auto list = QList<QSharedPointer<T>>();
        list.append(qSharedPointerDynamicCast<T>(m_behaviors[typeid(T)]));

        for(auto *child : findChildren<GameObject *>()) {
            list.append(qSharedPointerDynamicCast<T>(child->getBehavior<T>()));
        }
        return list;
    };

    // QObject interface
    bool event(QEvent *event) override;

    void setData(const QMap<DataRole, QVariant> &data);

    bool operator==(GameObject const &obj) const {
        return m_objectData[DataRole::Type].value<ObjectType>() == obj;
    }

    bool operator==(ObjectType const &type) const {
        return m_objectData[DataRole::Type].value<ObjectType>() == type;
    }

    bool hasChild(ObjectType type) const;

    bool hasChild(QPair<ObjectType, ObjectType> range) const;

    const GameObject *nearest(QPair<ObjectType, ObjectType> range) const;

    const GameObject *nearest(ObjectType type) const;
    const QPointer<GameObject> findChild(QPair<ObjectType, ObjectType> range);
private:
    QMap<std::type_index, QSharedPointer<Behavior>> m_behaviors;
    QMap<DataRole, QVariant> m_objectData;

signals:
    void dataChanged(QMap<DataRole, QVariant> objectData);
    void tick();
};

#endif // GAMEOBJECT_H
