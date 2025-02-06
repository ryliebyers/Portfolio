#include "droplet.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "bucket.h"
#include "sound.h"
#include "points.h"
#include "globals.h"
#include "QVBoxLayout"
#include <QMediaPlayer>


Droplet::Droplet() {
    // Set up timer for movement
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Droplet::moveDroplet);
    timer->start(250);//speed
    speedUp();
}

Droplet::~Droplet() {
    delete timer;
}

//method that moves droplets
void Droplet::moveDroplet() {
    Sound *sound = new Sound;


    //if pos is within screen then move droplet
    if (scene() && pos().y() < scene()->height()) {
        setPos(x(), y() + 10);
        //checkes for collision
        QList<QGraphicsItem*> colliding_items = collidingItems();
        //iterate through all collisions
        for (int i = 0; i < colliding_items.size(); ++i) {
            //if same type where bucket is then remove droplet and returns
            if (typeid(*(colliding_items[i])) == typeid(Bucket)) {
                sound->AddSplash();

                if (totalPoints <150){

                    totalPoints+=50;
                }


                DropsCaught += 1;
                if(isWon || totalPoints == 150){
                    // Create a QGraphicsTextItem for "You Won"
                    QGraphicsTextItem *youWonText = new QGraphicsTextItem("You Won!");

                    // Set font and color
                    QFont font("Arial", 80, QFont::Bold);
                    youWonText->setFont(font);
                    youWonText->setDefaultTextColor(Qt::green);

                    // Center the text item
                    QPointF centerPoint = QPointF(scene()->width() / 2 - youWonText->boundingRect().width() / 2,
                                                  scene()->height() / 2 - youWonText->boundingRect().height() / 2);
                    youWonText->setPos(centerPoint);
                    // Create a QGraphicsPixmapItem for the image
                    QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(QPixmap(":/AdditionalWindow.gif").scaled(130, 130));

                    // Set the position of the image item
                    QPointF imagePos = QPointF(scene()->width() / 2 - imageItem->boundingRect().width() / 2,
                                               scene()->height() / 2 - imageItem->boundingRect().height() / 2 + youWonText->boundingRect().height());
                    imageItem->setPos(imagePos);
                    scene()->addItem(imageItem);

                    scene()->addItem(youWonText);

                }


                scene()->removeItem(this);
                delete this;
                return;
            }

        }

    } else {
        //Out of window
        sound->AddBeep();
        if (totalPoints <150){

        totalPoints-=5;
        }
        qDebug() << "Total points: " << totalPoints;
        scene()->removeItem(this);
        delete this;
    }
    delete sound;

}




void Droplet::speedUp() {
    qDebug() << "Total Collisions: " << DropsCaught;




    if (DropsCaught >= 5 && DropsCaught <= 9 ) {

        // x2
        if (timer->isActive()) {
            timer->stop(); // Stop the previous timer if active
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Droplet::moveDroplet);
        timer->start(250/2); // Start a new timer with the updated speed
    } else if (DropsCaught >= 10 && DropsCaught <= 14) {
        // x4
        if (timer->isActive()) {
            timer->stop();
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Droplet::moveDroplet);
        timer->start(250/4);
    } else if (DropsCaught >= 15 && DropsCaught <= 19 ) {
        // x8
        if (timer->isActive()) {
            timer->stop();
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Droplet::moveDroplet);
        timer->start(250/8);
    } else if (DropsCaught >= 20) {
        // x16
        if (timer->isActive()) {
            timer->stop();
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Droplet::moveDroplet);
        timer->start(250/16);
    }
}











