#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <iostream>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include <QCoreApplication>
#include <qdatetime.h>
#include <QDateTime>

#include <node.h>
#include <pathfinder_class.h>

#include "model/gameobjectmodel.h"
#include "view/gameview.h"
#include <model/behaviors/concrete/poison/genericpoisonablebehavior.h>
#include <model/behaviors/concrete/poison/genericpoisoningbehavior.h>
#include <pathfinder_class.h>
#include <model/behaviors/health.h>

class GameWindow;

/**
 * @brief The GameController class
 */
class GameController : public QGraphicsView {
    Q_OBJECT
public:
    /**
     * @brief The State enum, Game states can be Running, Paused or GameOver
     */
    enum class State {
        Running,
        Paused,
        GameOver,
    };
    /**
     * @brief The View enum, Game visualizations can be Text, Color or Sprites
     */
    enum class View {
        Text,
        Sprite,
        Color,
    };
    /**
     * @brief GameController controls the state of the game, has instance of the model data
     */
    GameController();
    /**
     * @brief startGame starts the game at level 1
     */
    void startGame();
    /**
     * @brief findAndMoveTo
     * @param x
     * @param y
     */
    // void findAndMoveTo(int x, int y);
    /**
     * @brief characterMove call model behavior to move the protagonist
     * @param to
     */
    void characterMove(Direction to);
    /**
     * @brief characterAtttack attacks enemy in current protagonist direction
     */
    void characterAtttack();
    /**
     * @brief pathFinder automatically routes the protagonist to given position using the algorithm for the shortest path
     * @param x x coordinate of the world grid
     * @param y y coordinate of the world grid
     */
    void pathFinder(int x, int y);
    /**
     * @brief updateEnergy retrieves lastest protagonist energy level upon data change and triggers corresponding slot in the GameWindow
     */
    void updateEnergy();
    /**
     * @brief updateHealth retrieves lastest protagonist health level upon data change and triggers corresponding slot in the GameWindow
     */
    void updateHealth();
    /**
     * @brief updateLevel handles going up and down the levels (upon stepping on doorways), captures data change in the model and triggers GameWindow
     * @param direction UP to go to next level, DOWN to go to previous level, parameter passed from data change
     */
    void updateLevel(Direction direction);
    /**
     * @brief updateGameView calls the new visualization renderer of the scene upon switching views, captures data change in the model and triggers GameWindow
     * @param view Text, Color or Sprite
     */
    void updateGameView(View view);
    /**
     * @brief dataChanged captures any model changes and filters to call corresponding methods
     * @param objectData
     */
    void dataChanged(QMap<DataRole, QVariant> objectData);
    /**
     * @brief disconnectCurrentModel disconnects current model upon changing levels
     */
    void disconnectCurrentModel();
    /**
     * @brief connectCurrentModel connects new level model
     */
    void connectCurrentModel();
    /**
     * @brief emitLevelUpdates emits changing level, health packs and enemies signals upon changing levels, signals captured by GameWindow
     */
    void emitLevelUpdates();
    /**
     * @brief createNewLevel creates new level upon going up levels
     * @param level
     */
    void createNewLevel(int level);

    // GETTERS AND SETTERS
    void setState(State new_state) { m_gameState = new_state; }
    void setView(QSharedPointer<GameView> view) { m_view = view; } // GameView

    State getState() { return m_gameState; }
    QSharedPointer<GameView> getView() { return m_view; } // GameView
    View getGameView() { return m_gameView; } // Visualization enum

    void automaticAttack(Direction direction);
    void executePath(std::vector<int> path, bool fully = false);
signals:
    /**
     * @brief tick Emitted when a turn is complete.
     * @param clock The count of clocks so far
     */
    void tick();
    /**
     * @brief gameOver This is emitted when the game is over.
     */
    void gameOver();
    /**
     * @brief stateChanged This is emitted when the game state changes
     * @param stateChanged state The new game state
     */
    /**
     * @brief stateChanged Emitted when game switches states (Running, Paused or GameOver)
     * @param state
     */
    void stateChanged(State state);
    /**
     * @brief energyUpdated Emitted whenever the protagonist energy level changes, captured by GameWindow to be displayed in the UI
     * @param energy
     */
    void energyUpdated(int energy);
    /**
     * @brief healthUpdated Emitted whenever the protagonist health level changes, captured by GameWindow to be displayed in the UI
     * @param health
     */
    void healthUpdated(int health);
    /**
     * @brief enemiesUpdated Emitted when the level of the game changes and thus the number of enemies for that level, captured by GameWindow to be displayed in the UI
     * @param enemies
     */
    void enemiesUpdated(int enemies);
    /**
     * @brief healthPacksUpdated Emitted when the level of the game changes and thus the number of health packs for that level, captured by GameWindow to be displayed in the UI
     * @param health_packs
     */
    void healthPacksUpdated(int health_packs);
    /**
     * @brief levelUpdated Emitted when the level of the game changes, captured by GameWindow to be displayed in the UI
     * @param level
     */
    void levelUpdated(int level);



private:
    /**
     * @brief m_model List of the different game models for different levels, holds all game data and logic
     */
    QList<QPair<GameObjectModel *, std::vector<Node>>> m_models;
    /**
     * @brief m_view The scene of the controller
     */
    QSharedPointer<GameView> m_view;

    /**
     * @brief m_character The protagonist of the game
     */
    QPointer<GameObject> m_protagonist;
    /**
     * @brief m_gameLevel current game level
     */
    int m_gameLevel;
    /**
     * @brief m_gameState current game state
     */
    State m_gameState;
    /**
     * @brief m_gameView current game visualization (Text, Color, Sprite)
     */
    View m_gameView;
    /**
     * @brief m_health_packs Number of current health packs in the game
     */
    int m_health_packs;
    /**
     * @brief m_enemies Number of current enemies in the game
     */
    int m_enemies;
};

#endif // GAMECONTROLLER_H
