#ifndef POISONONKILLEDBEHAVIOR_H
#define POISONONKILLEDBEHAVIOR_H

#include "generichealthbehavior.h"

class PoisonOnKilledBehavior : public QObject, public GenericHealthBehavior {
    Q_OBJECT
public:
    PoisonOnKilledBehavior(QPointer<GameObject> owner)
        : GenericHealthBehavior(owner) {};

    // Health interface
    void die() override;

private:
    unsigned int m_ticksToPoison = 0, m_poisonCount = 0, m_tickCount = 0;

public slots:
    void spreadPoison();
};

#endif // POISONONKILLEDBEHAVIOR_H
