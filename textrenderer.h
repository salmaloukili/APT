#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

/**
 * @brief The TextRenderer class
 */
class TextRenderer : public Renderer {
public:

    /**
     * @brief TextRenderer
     * Performs rendering of the bojects for the text view
     */
    TextRenderer();

    /**
     * @brief renderGameObject performs the selection of the function used to render based on the ObjectType
     * @param objectData
     * @param item
     */
    void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item) override;

private:

    /**
     * @brief renderTile renders tile object
     * @param object
     * @return QPixmap
     */
    QPixmap renderTile(QMap<DataRole, QVariant> object);

    /**
     * @brief renderDoorway renders doorway object
     * @param object
     * @return QPixmap
     */
    QPixmap renderDoorway(QMap<DataRole, QVariant> object);

    /**
     * @brief renderHealthPack renders health pack object
     * @param object
     * @return QPixmap
     */
    QPixmap renderHealthPack(QMap<DataRole, QVariant> object);

    /**
     * @brief renderProtagonist renders protagonist object
     * @param object
     * @return QPixmap
     */
    QPixmap renderProtagonist(QMap<DataRole, QVariant> object);

    /**
     * @brief renderEnemy renders Enemy object
     * @param object
     * @return QPixmap
     */
    QPixmap renderEnemy(QMap<DataRole, QVariant> object);

    /**
     * @brief renderPEnemy renders PEnemy object
     * @param object
     * @return QPixmap
     */
    QPixmap renderPEnemy(QMap<DataRole, QVariant> object);

    /**
     * @brief renderMovingEnemy renders MovingEnemy object
     * @param object
     * @return QPixmap
     */
    QPixmap renderMovingEnemy(QMap<DataRole, QVariant> object);

    /**
     * @brief renderCharacter generalized rendering of objects
     * @param str
     * @param color
     * @return QPixmap
     */
    QPixmap renderCharacter(QString str, QColor color);
};

#endif // TEXTRENDERER_H
