#ifndef LEVEL1_H
#define LEVEL1_H

#include "QtWidgets/qgraphicsscene.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bucket.h"
#include <QGraphicsItem>
class Level1 : public QGraphicsScene
{
    Q_OBJECT
public:
    Level1(const QString& userName, const QString& profilePicturePath);
    ~Level1();
private:
    Bucket *bucket;
    QTimer *timerDrop;
    QGraphicsRectItem *pointsRect;
    QGraphicsTextItem *pointsTextItem;
    QGraphicsTextItem *dropsTextItem;
public slots:
    void addDroplet();
    void updatePointsDisplay();
};

#endif // LEVEL1_H
