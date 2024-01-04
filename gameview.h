#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QObject>
#include <QList>
#include "view/renderer/renderer.h"

class GameView : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GameView(QObject *parent = nullptr);

    void createScene(const QList<QList<QList<QMap<DataRole, QVariant>>>> &gameObjects,
                     QSharedPointer<Renderer> renderer = nullptr);

    void setRenderer(QSharedPointer<Renderer> newRenderer);

private:
    QSharedPointer<Renderer> m_renderer;

    // Store the graphical representation of each GameObject
    QList<QList<GamePixmapItem *>> m_tiles;
    GamePixmapItem *getPixmapItem(int x, int y, QVariant type);

public slots:
    void dataChanged(QMap<DataRole, QVariant> objectData);
};

#endif // GAMEVIEW_H
