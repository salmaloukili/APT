#include <QRandomGenerator>
#include <QFile>

#include "model/noise/perlinnoise.h"
#include "gameobjectsettings.h"
#include "modelfactory.h"
#include "world.h"

QPair<GameObjectModel *, std::vector<Node>> ObjectModelFactory::createModel(
  unsigned int nrOfEnemies, unsigned int nrOfHealthpacks,
  float pRatio, int level, int rows, int columns) {
    std::vector<Node> nodes; // Node class for the pathfinder
    World m_world;

    createWorld(level, rows, columns, (double)(level + 1) / 20.0);
    m_world.createWorld(QStringLiteral("./world_%1.png").arg(level), nrOfEnemies, nrOfHealthpacks, pRatio);
    QFile::remove(QStringLiteral("./world_%1.png").arg(level));

    QList<QList<QPointer<GameObject>>> worldGrid(rows); // instantiate gameObjectModel aka the worldgrid
    for(int i = 0; i < rows; ++i) {
        worldGrid[i] = QList<QPointer<GameObject>>(columns);
    }

    // insert tiles into model
    auto tiles = m_world.getTiles();
    for(const auto &tile : tiles) {
        nodes.emplace_back(tile->getXPos(), tile->getYPos(), tile->getValue());
        auto *obj = new GameObject({
          {DataRole::Energy, tile->getValue()},
          {DataRole::Position, QPoint(tile->getXPos(), tile->getYPos())},
        });
        GameObjectSettings::getFunction(ObjectType::Tile)(obj);
        worldGrid[tile->getYPos()][tile->getXPos()] = obj;
    }
    // Process doorways
    if(level) {
        auto *entryDoor = new GameObject({
          {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Down)},
        });
        GameObjectSettings::getFunction(ObjectType::Doorway)(entryDoor);
        entryDoor->setParent(worldGrid[0][0]);
    }

    auto *exitDoor = new GameObject({
      {DataRole::Direction, QVariant::fromValue<Direction>(Direction::Up)},
    });
    GameObjectSettings::getFunction(ObjectType::Doorway)(exitDoor);
    exitDoor->setParent(worldGrid[rows - 1][columns - 1]);

    // Process protagonist
    auto protagonist = m_world.getProtagonist();
    auto *proObj = new GameObject();
    GameObjectSettings::getFunction(ObjectType::Protagonist)(proObj);
    proObj->setParent(worldGrid[protagonist->getXPos()][protagonist->getYPos()]);

    // Process Health Packs
    auto healthPacks = m_world.getHealthPacks();
    for(const auto &hp : healthPacks) {
        auto *hpObj = new GameObject();
        GameObjectSettings::getFunction(ObjectType::HealthPack)(hpObj);
        nodes[hp->getYPos() * columns + hp->getXPos()].setValue(0.01);
        hpObj->setParent(worldGrid[hp->getXPos()][hp->getYPos()]);
    }

    // Process Enemies and Poison Enemies
    auto enemies = m_world.getEnemies();
    int enemyLocations[rows][columns];
    memset(enemyLocations, 0, sizeof(enemyLocations));

    for(const auto &enemy : enemies) {
        int enemyX = enemy->getXPos();
        int enemyY = enemy->getYPos();
        enemyLocations[enemyX - 1][enemyY - 1] = 1;
        if((enemyX == columns - 1 && enemyY == rows - 1) || (enemyX == 0 && enemyY == 0)) {
            enemyX = columns - 2;
            enemyY = rows - 2; // make sure no enemies on the doorway
        }

        nodes[enemyY * columns + enemyX].setValue(0.8);

        ObjectType type = dynamic_cast<PEnemy *>(enemy.get()) ? ObjectType::PoisonEnemy : ObjectType::Enemy;
        auto *enemyObj = new GameObject();
        GameObjectSettings::getFunction(type)(enemyObj);
        enemyObj->setParent(worldGrid[enemyX][enemyY]);
    }

    // Moving enemies not placed in the same place as other enemies.
    int movingEnemies = 5;
    while(movingEnemies) {
        auto *enemyObj = new GameObject();
        GameObjectSettings::getFunction(ObjectType::MovingEnemy)(enemyObj);
        int x = 0, y = 0;
        do {
            x = QRandomGenerator::global()->bounded(1, rows - 2);
            y = QRandomGenerator::global()->bounded(1, columns - 2);
        } while(!enemyLocations[x][y]);
        enemyObj->setParent(worldGrid[x][y]);
        movingEnemies--;
    }

    auto *model = new GameObjectModel(worldGrid);

    return {model, nodes};
}

void ObjectModelFactory::createWorld(int level, int width, int height, double difficulty) {
    QImage image(width, height, QImage::Format_Grayscale8);
    int seed = floor(QRandomGenerator::global()->bounded(1, 1000));
    PerlinNoise pn(seed);
    for(int i = 0; i < height; ++i) { // y
        auto pLine = image.scanLine(i);

        for(int j = 0; j < width; ++j) { // x
            double x = (double)j / ((double)width);
            double y = (double)i / ((double)height);

            double n = 2 * pn.noise(x * width / 15, y * height / 30, 0.8);

            // Map the values to the [0, 255] interval
            *pLine++ = floor(255 * n * difficulty);
        }
    }

    image.save(QStringLiteral("./world_%1.png").arg(level), "png", -1);
}
