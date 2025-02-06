#ifndef GAME1SCENE_H
#define GAME1SCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bucket.h"
#include <QGraphicsItem>
#include "droplet.h"
#include "additionalwindow.h"
#include <QMainWindow>

class Game1Scene : public QGraphicsScene {
    Q_OBJECT
public:
    Game1Scene(const QString& userName, const QString& profilePicturePath);
    ~Game1Scene();
private:
    Bucket *bucket;
    QTimer *timerDrop;
     bool isGuestMode;
    QGraphicsRectItem *pointsRect;
    QGraphicsTextItem *pointsTextItem;
    QGraphicsTextItem *dropsTextItem;
    AdditionalWindow *additionalWindow;
public slots:
    void addDroplet();
    void updatePointsDisplay();
    //void quitGame();
    //void viewHistory();
    //void viewHistoryButtonClicked();
};
#endif // GAME1SCENE_H

