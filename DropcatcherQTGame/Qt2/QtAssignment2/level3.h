#ifndef LEVEL3_H
#define LEVEL3_H

#include <QWidget>
#include "QtWidgets/qgraphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bucket.h"
#include <QGraphicsItem>
class Level3 : public QGraphicsScene
{
    Q_OBJECT
public:
    Level3(const QString& userName, const QString& profilePicturePath);
    ~Level3();
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

#endif // LEVEL3_H
