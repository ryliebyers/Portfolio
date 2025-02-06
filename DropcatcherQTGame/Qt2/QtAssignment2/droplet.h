//Author: Mina Akbari
//Assignment: Qt2
//Course: CS6015
//Date: April 15, 2024

#ifndef DROPLET_H
#define DROPLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "sound.h"
#include "points.h"



class Droplet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Droplet();
    ~Droplet();
    Droplet(const QPointF& cloudPosition);
    void speedUp();
private:
    QTimer *timer;
    qreal speed = 5;
    //might delete these later
  //  Points m_points; // Member variable to hold the Points object
    //Sound m_sound;   // Member variable to hold the Sound object
private slots:
    void moveDroplet();
signals:
    void outOfScene();
};
#endif // DROPLET_H
