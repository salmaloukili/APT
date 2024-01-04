#ifndef RENDERER_H
#define RENDERER_H

#include "publicenums.h"
#include "qpixmap.h"
#include "view/gamepixmapitem.h"

/**
 * @brief The Renderer class
 */
class Renderer {
public:

    /**
     * @brief Renderer constructor
     */
    Renderer();

    /**
     * @brief ~Renderer virtual destructor
     */
    virtual ~Renderer() {
    }

    /**
     * @brief renderGameObjects renders the initial state of the world
     * @param objectData
     * @return GamePixmapItem
     */
    GamePixmapItem *renderGameObjects(QList<QMap<DataRole, QVariant>> objectData);

    /**
     * @brief renderGameObject renders separate objects one by one
     * @param objectData
     * @return GamePixmapItem
     */
    virtual GamePixmapItem *renderGameObject(QMap<DataRole, QVariant> objectData);

    /**
     * @brief renderGameObject applies latest change to the object visually to show change of the state
     * @param objectData
     * @param item
     */
    virtual void renderGameObject(QMap<DataRole, QVariant> objectData, GamePixmapItem *item);

    /**
     * @brief rotatePixmap rotated the pixmap based on direction
     * @param originalPixmap
     * @param direction
     * @return QPixmap
     */
    QPixmap rotatePixmap(const QPixmap &originalPixmap, int direction);

protected:

    /**
     * @brief CELL_SIZE
     */
    inline static constexpr int CELL_SIZE = 50;

protected:

    /**
     * @brief animateHealthPack animates the protagonist obtain of the healthpack
     * @param health
     * @param item
     * @return QImage
     */
    QImage animateHealthPack(int health, GamePixmapItem *item);

    /**
     * @brief animateTint animates tint over the pixmap to visualize damage
     * @param final
     * @param initial
     * @return QPropertyAnimation
     */
    QPropertyAnimation *animateTint(QColor final, QColor initial = {0, 0, 0, 0});

    /**
     * @brief animateAttack animates the attack by slightly moving the pixmap in the direction of dir
     * @param dir
     * @param attacking
     * @return QPropertyAnimation
     */
    QPropertyAnimation *animateAttack(int dir, bool attacking);

    /**
     * @brief animateBounce animates bouncing movement of the protagonist
     * @return QPropertyAnimation
     */
    QPropertyAnimation *animateBounce();

    /**
     * @brief animateHealth animates health gain of the protagonist
     * @param dir
     * @return QPropertyAnimation
     */
    QPropertyAnimation *animateHealth(Direction dir);

    /**
     * @brief animateHide animates the change of the opacity in the object, implemented on the moving enemy in our case
     * @return QPropertyAnimation
     */
    QPropertyAnimation *animateHide();
};

#endif // RENDERER_H
