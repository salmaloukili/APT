#ifndef GAMEOBJECTSETTINGS_H
#define GAMEOBJECTSETTINGS_H

#include "model/behaviors/concrete/movement/randommovementbehavior.h"
#include <model/behaviors/concrete/poison/genericpoisonablebehavior.h>
#include <model/behaviors/concrete/poison/genericpoisoningbehavior.h>

#include <model/behaviors/concrete/movement/genericmovebehavior.h>
#include <model/behaviors/concrete/movement/healonstepbehavior.h>
#include <model/behaviors/concrete/movement/newlevelonstep.h>
#include <model/behaviors/concrete/movement/poisononstepbehavior.h>

#include <model/behaviors/concrete/health/generichealingbehavior.h>
#include <model/behaviors/concrete/health/generichealthbehavior.h>
#include <model/behaviors/concrete/health/poisononkilledbehavior.h>

#include <model/behaviors/concrete/attack/counterattackbehavior.h>
#include <model/behaviors/concrete/attack/genericattackbehavior.h>

class GameObjectSettings {
    struct ProtagonistSettings {
        inline static const QList<QPair<DataRole, QVariant>> defaultData {
          {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Protagonist)},
          {DataRole::Health, Health::SETTINGS::MAX_HEALTH},
          {DataRole::Energy, Movement::SETTINGS::MAX_ENERGY},
          {DataRole::Strength, (float)Attack::SETTINGS::PLAYER_STRENGTH},
          {DataRole::PoisonLevel, Poison::SETTINGS::MIN_POISON},
          {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Down)},

        };

        static void setObject(GameObject *obj) {
            obj->setData(defaultData);
            obj->setBehavior<Attack>(QSharedPointer<GenericAttackBehavior>::create(obj));
            obj->setBehavior<Movement>(QSharedPointer<GenericMoveBehavior>::create(obj));
            obj->setBehavior<Poison>(QSharedPointer<GenericPoisonableBehavior>::create(obj));
            obj->setBehavior<Health>(QSharedPointer<GenericHealthBehavior>::create(obj));
        };
    };

    struct TileSettings {
        inline static const QList<QPair<DataRole, QVariant>> defaultData {
          {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Tile)},
          {DataRole::PoisonLevel, Poison::SETTINGS::MIN_POISON},
        };

        static void setObject(GameObject *obj) {
            obj->setData(defaultData);
            obj->setBehavior<Movement>(QSharedPointer<PoisonOnStepBehavior>::create(obj));
            obj->setBehavior<Poison>(QSharedPointer<GenericPoisoningBehavior>::create(obj));
        };
    };

    struct DoorSettings {
        inline static const QList<QPair<DataRole, QVariant>> defaultData {
          {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Doorway)},
        };

        static void setObject(GameObject *obj) {
            obj->setData(defaultData);
            obj->setBehavior<Movement>(QSharedPointer<NewLevelOnStep>::create(obj));
        };
    };

    struct HealthPackSettings {
        inline static const QList<QPair<DataRole, QVariant>> defaultData {
          {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::HealthPack)},
          {DataRole::Health, Health::SETTINGS::HEALTH_PACK_AMOUNT},
        };

        static void setObject(GameObject *obj) {
            obj->setData(defaultData);
            obj->setBehavior<Movement>(QSharedPointer<HealOnStepBehavior>::create(obj));
            obj->setBehavior<Health>(QSharedPointer<GenericHealingBehavior>::create(obj));
        };
    };
    struct EnemySettings {
        inline static const QList<QPair<DataRole, QVariant>> defaultData {
          {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::Enemy)},
          {DataRole::Health, Health::SETTINGS::MAX_HEALTH},
          {DataRole::Strength, (float)Attack::SETTINGS::ENEMY_STRENGTH},
          {DataRole::Direction, 0},

        };

        static void setObject(GameObject *obj) {
            obj->setData(defaultData);
            obj->setBehavior<Attack>(QSharedPointer<CounterAttackBehavior>::create(obj));
            obj->setBehavior<Health>(QSharedPointer<GenericHealthBehavior>::create(obj));
        };
    };
    struct PoisonEnemySettings {
        inline static const QList<QPair<DataRole, QVariant>> defaultData {
          {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::PoisonEnemy)},
          {DataRole::Health, Health::SETTINGS::MAX_HEALTH},
          {DataRole::Strength, Attack::SETTINGS::ENEMY_STRENGTH},
          {DataRole::PoisonLevel, Poison::SETTINGS::PENEMY_POISON_LEVEL},
        };

        static void setObject(GameObject *obj) {
            obj->setData(defaultData);
            obj->setBehavior<Attack>(QSharedPointer<CounterAttackBehavior>::create(obj));
            obj->setBehavior<Health>(QSharedPointer<PoisonOnKilledBehavior>::create(obj));
            obj->setBehavior<Poison>(QSharedPointer<GenericPoisoningBehavior>::create(obj));
        };
    };
    struct MovingEnemySettings {
        inline static const QList<QPair<DataRole, QVariant>> defaultData {
          {DataRole::Type, QVariant::fromValue<ObjectType>(ObjectType::MovingEnemy)},
          {DataRole::Health, Health::SETTINGS::MAX_HEALTH},
          {DataRole::Strength, Attack::SETTINGS::ENEMY_STRENGTH},
          {DataRole::Energy, Movement::SETTINGS::MAX_ENERGY * 10},
        };

        static void setObject(GameObject *obj) {
            obj->setData(defaultData);
            obj->setBehavior<Attack>(QSharedPointer<CounterAttackBehavior>::create(obj));
            obj->setBehavior<Health>(QSharedPointer<GenericHealthBehavior>::create(obj));
            obj->setBehavior<Movement>(QSharedPointer<RandomMovementBehavior>::create(obj));
        };
    };

public:
    static std::function<void(GameObject *)> getFunction(ObjectType type) {
        switch(type) {
        case ObjectType::Tile:
            return TileSettings::setObject;
        case ObjectType::Doorway:
            return DoorSettings::setObject;
        case ObjectType::HealthPack:
            return HealthPackSettings::setObject;
        case ObjectType::Protagonist:
            return ProtagonistSettings::setObject;
        case ObjectType::Enemy:
            return EnemySettings::setObject;
        case ObjectType::PoisonEnemy:
            return PoisonEnemySettings::setObject;
        case ObjectType::MovingEnemy:
            return MovingEnemySettings::setObject;
        default:
            return EnemySettings::setObject;
        }
    }
};

#endif // GAMEOBJECTSETTINGS_H
