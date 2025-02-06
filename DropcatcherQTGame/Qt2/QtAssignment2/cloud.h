#ifndef CLOUD_H
#define CLOUD_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

class Cloud : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Cloud(QObject *parent = nullptr);

signals:
public slots:
    void move();
private:
    QTimer *timer;
};
#endif // CLOUD_H


