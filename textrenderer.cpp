#include <QFont>
#include <QPainter>
#include <QPen>
#include <QRandomGenerator>
#include "textrenderer.h"

TextRenderer::TextRenderer() {
}

void TextRenderer::renderGameObject(QMap<DataRole, QVariant> data, GamePixmapItem *item) {
    switch(data[DataRole::Type].value<ObjectType>()) {
    case ObjectType::Tile:
        item->setSprite(renderTile(data).toImage());
        break;
    case ObjectType::Doorway:
        item->setSprite(renderDoorway(data).toImage());
        break;
    case ObjectType::HealthPack:
        item->setSprite(renderHealthPack(data).toImage());
        break;
    case ObjectType::Protagonist:
        item->setSprite(renderProtagonist(data).toImage());
        break;
    case ObjectType::Enemy:
        item->setSprite(renderEnemy(data).toImage());
        break;
    case ObjectType::PoisonEnemy:
        item->setSprite(renderPEnemy(data).toImage());
        break;
    case ObjectType::MovingEnemy:
        item->setSprite(renderMovingEnemy(data).toImage());
        break;
    default:
        item->setSprite(renderEnemy(data).toImage());
        break;
    }
    item->updatePixmap();
    item->setActive(true);
    Renderer::renderGameObject(data, item);
}

QPixmap TextRenderer::renderTile(QMap<DataRole, QVariant> object) {
    // The Pixmaps have to be transparent, text is AAd by default
    QPixmap pixmap(CELL_SIZE, CELL_SIZE);
    pixmap.fill({227, 239, 255, 255});
    QPainter painter(&pixmap);

    QFont font = painter.font();
    font.setBold(true);
    font.setKerning(false);
    font.setFixedPitch(true);
    font.setPointSize(CELL_SIZE / 4); // Set the font size relative to cell size
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    font.setWeight(QFont::Black);
    painter.setFont(font);
    painter.setLayoutDirection(Qt::LeftToRight);

    // This has to be calculated to know the offset of the underscore characters
    QFontMetrics fontMetrics(font);
    int linePosition = ((CELL_SIZE - fontMetrics.horizontalAdvance("_")) / 4);

    // Draw the bottom lines, we don't need top lines unless we are at the top
    // The offsets are a bit arbitrary on the y ax.
    painter.drawText(linePosition - 4, CELL_SIZE - 3, "_");
    painter.drawText(2 * linePosition - 4, CELL_SIZE - 3, "_");
    painter.drawText(3 * linePosition - 4, CELL_SIZE - 3, "_");
    painter.drawText(4 * linePosition - 4, CELL_SIZE - 3, "_");

    if(!object[DataRole::Position].toPoint().y()) {
        painter.drawText(linePosition - 4, 0, "_");
        painter.drawText(2 * linePosition - 4, 0, "_");
        painter.drawText(3 * linePosition - 4, 0, "_");
        painter.drawText(4 * linePosition - 4, 0, "_");
    }

    // The | characters are much longer than the _ so we make them smaller
    font.setPointSize(CELL_SIZE / 8);
    font.setStretch(125);
    painter.setFont(font);

    // This looks extremely funky but it is what it is
    painter.drawText(-1, CELL_SIZE / 4 - 2, "|");
    painter.drawText(-1, 2 * (CELL_SIZE / 4) - 2, "|");
    painter.drawText(-1, 3 * (CELL_SIZE / 4) - 2, "|");
    painter.drawText(-1, CELL_SIZE - 2, "|");
    // Since the renderer has no idea about the size of the world,
    // It cannot simply know where the
    painter.drawText(CELL_SIZE - 2, CELL_SIZE / 4 - 2, "|");
    painter.drawText(CELL_SIZE - 2, 2 * (CELL_SIZE / 4) - 2, "|");
    painter.drawText(CELL_SIZE - 2, 3 * (CELL_SIZE / 4) - 2, "|");
    painter.drawText(CELL_SIZE - 2, CELL_SIZE - 2, "|");

    if(object[DataRole::Energy] == INFINITY) {
        for(int i = 0; i < CELL_SIZE; i++)
            for(int j = 0; j < CELL_SIZE; j++)
                painter.drawText(i, j, ".");
    }

    if(int poisonLevel = object[DataRole::PoisonLevel].toInt()) {
        int maxDots = CELL_SIZE;
        int numberOfDots = (maxDots * poisonLevel);
        painter.setPen(Qt::green);
        for(int i = 0; i < numberOfDots; ++i) {
            int randomX = QRandomGenerator::global()->bounded(CELL_SIZE);
            int randomY = QRandomGenerator::global()->bounded(CELL_SIZE);
            painter.drawText(randomX, randomY, ".");
        }
    }

    if(int energy = object[DataRole::Energy].toInt()) {
        int maxDots = CELL_SIZE;
        int numberOfDots = (maxDots * energy);
        painter.setPen(Qt::blue);
        for(int i = 0; i < numberOfDots; ++i) {
            int randomX = QRandomGenerator::global()->bounded(CELL_SIZE);
            int randomY = QRandomGenerator::global()->bounded(CELL_SIZE);
            painter.drawText(randomX, randomY, ".");
        }
    }

    return pixmap;
}

QPixmap TextRenderer::renderDoorway(QMap<DataRole, QVariant>) {
    QColor color(0, 0, 0);
    return renderCharacter("||", color);
}

QPixmap TextRenderer::renderHealthPack(QMap<DataRole, QVariant>) {
    QColor color(43, 255, 0);
    return renderCharacter("c[]", color);
}

QPixmap TextRenderer::renderProtagonist(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int direction = object[DataRole::Direction].toInt();
    QColor color("black");
    color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());

    return rotatePixmap(renderCharacter(">", color), direction);
}

QPixmap TextRenderer::renderEnemy(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int direction = object[DataRole::Direction].toInt();

    QColor color("red");
    color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());

    return rotatePixmap(renderCharacter("◎", color), direction);
}

QPixmap TextRenderer::renderPEnemy(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int poisonLevel = object[DataRole::PoisonLevel].toInt();
    int direction = object[DataRole::Direction].toInt();
    QColor color;
    if(healthLevel <= 0) {
        color = QColor("darkgreen");
        color.setHsv(color.hue(), poisonLevel, color.value(), color.alpha());

    } else {
        color = QColor("green");
        color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());
    }

    return rotatePixmap(renderCharacter("ⓧ", color), direction);
}

QPixmap TextRenderer::renderCharacter(QString str, QColor color) {
    QPixmap pixmap(CELL_SIZE, CELL_SIZE);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QFont font = painter.font();
    font.setBold(true);
    font.setKerning(false);
    font.setFixedPitch(true);
    font.setPointSize(CELL_SIZE / 1.7); // Set the font size relative to cell size
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    font.setWeight(QFont::Black);
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setColor(color);
    painter.setPen(pen);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(str));
    painter.end();

    return pixmap;
}

QPixmap TextRenderer::renderMovingEnemy(QMap<DataRole, QVariant> object) {
    int healthLevel = object[DataRole::Health].toInt();
    int energyLevel = object[DataRole::Energy].toInt();
    int direction = object[DataRole::Direction].toInt();
    QColor color;
    if(healthLevel <= 0) {
        color = QColor("darkyellow");
        color.setHsv(color.hue(), energyLevel, color.value(), color.alpha());

    } else {
        color = QColor("yellow");
        color.setHsv(color.hue(), healthLevel, color.value(), color.alpha());
    }

    return rotatePixmap(renderCharacter("@", color), direction);
}

