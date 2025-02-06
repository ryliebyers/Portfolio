
#ifndef BUCKET_H
#define BUCKET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Bucket : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    int scaleFactor;
    int sceneWidth;
    Bucket();
    void keyPressEvent(QKeyEvent *event);
    void setSceneWidth(int width);
};
#endif // BUCKET_H
