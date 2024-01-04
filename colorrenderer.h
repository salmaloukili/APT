#ifndef COLORRENDERER_H
#define COLORRENDERER_H

#include "renderer.h"
#include <algorithm>
#include <QBrush>
#include <QPainter>
#include <iostream>
#include <QtGlobal>

/**
 * @brief The ColorRenderer class
 */
class ColorRenderer : public Renderer {
public:

    /**
     * @brief ColorRenderer
     * Performs rendering of objects for color view
     */
    ColorRenderer() {}

    /**
     * @brief renderGameObject makes the selection of which object to render based on ObjectType
     * @param objectData
     * @param item
     */
    void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) override;

private:

    /**
     * @brief renderTile
     * @param object
     * @return QPixmap of the tile
     */
    QPixmap renderTile(QMap<DataRole, QVariant> object);

    /**
     * @brief renderDoorway
     * @param object
     * @return QPixmap of the doorway object
     */
    QPixmap renderDoorway(QMap<DataRole, QVariant> object);

    /**
     * @brief renderHealthPack
     * @param object
     * @return QPixmap of the health pack object
     */
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object);

    /**
     * @brief renderProtagonist
     * @param object
     * @return QPixmap of the protagonist object
     */
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object);

    /**
     * @brief renderEnemy
     * @param object
     * @return QPixmap of the enemy object
     */
    QPixmap renderEnemy(QMap<DataRole, QVariant> object);

    /**
     * @brief renderPEnemy
     * @param object
     * @return QPixmap of the PEnemy object
     */
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object);

    /**
     * @brief renderMovingEnemy
     * @param object
     * @return QPixmap of the moving enemy object
     */
    QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object);
};

#endif // COLORRENDERER_H
