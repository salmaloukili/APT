#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include "gameobjectmodel.h"

#include <node.h>

class ObjectModelFactory {
public:
    static QPair<GameObjectModel *, std::vector<Node>> createModel(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks,
                                                                   float pRatio, int level, int rows = 40, int columns = 40);
    static void createWorld(int level, int width, int height, double difficulty = 1.0);
};

#endif // MODELFACTORY_H
