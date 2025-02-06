
#include "cloud.h"

Cloud::Cloud(QObject *parent) : QObject(parent)
{
    setPixmap(QPixmap(":/images/cloud.png")); // Set pixmap to the cloud image
    setPos(0,0); // Set initial position (top-left corner)
    setScale(0.09); //Set its scale

    // Create a timer to move the cloud
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Cloud::move);
    timer->start(50); // Adjust the interval as needed for desired speed
}

void Cloud::move()
{
    // Move the cloud horizontally
    setPos(x() + 1, y()); // Adjust the movement speed (1 pixel per timer interval)

    // If the cloud goes off the right edge of the scene, reset its position to the left
    if (x() > scene()->width())
        setPos(0, y());
}
