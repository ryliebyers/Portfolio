#ifndef LEVEL2_H
#define LEVEL2_H

#include <QWidget>
#include "QtWidgets/qgraphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bucket.h"
#include <QGraphicsItem>


class Level2 : public QGraphicsScene
{
    Q_OBJECT
public:
    Level2(const QString& userName, const QString& profilePicturePath);
    ~Level2();
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

#endif // LEVEL2_H
