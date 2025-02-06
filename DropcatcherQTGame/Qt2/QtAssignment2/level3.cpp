#include "level3.h"
#include "cloud.h"
#include <QBrush>
#include <QImage>
#include <QKeyEvent>
#include "droplet.h"
#include "globals.h"
#include "historywindow.h"

Level3::Level3(const QString& userName, const QString& profilePicturePath)
{
    // Set background image
    QImage backgroundImage(":/images/background.jpg");
    if (backgroundImage.isNull()) {
        qDebug() << "Error loading background image: " << backgroundImage;
    } else {
        // Set background image
        setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(512).scaledToWidth(910)));
    }

    // Set scene rectangle
    setSceneRect(0, 0, 910, 512);

    // Create and add bucket
    bucket = new Bucket();
    bucket->setPixmap((QPixmap(":/images/bucket.png")).scaled(130, 130));

    addItem(bucket);
    bucket->setPos(400, 390);
    bucket->setFlag(QGraphicsItem::ItemIsFocusable);
    bucket->setFocus();


    // Create timer for droplets
    timerDrop = new QTimer(this);
    connect(timerDrop, &QTimer::timeout, this, &Level3::addDroplet);
    timerDrop->start(100);

    // Create and add clouds
    Cloud *cloud1 = new Cloud();
    Cloud *cloud2 = new Cloud();
    Cloud *cloud3 = new Cloud();
    Cloud *cloud4 = new Cloud();
    Cloud *cloud5 = new Cloud();

    addItem(cloud1);
    addItem(cloud2);
    addItem(cloud3);
    addItem(cloud4);
    addItem(cloud5);

    // Set positions for the clouds
    cloud1->setPos(50, -10);
    cloud2->setPos(200, 10);
    cloud3->setPos(350, -5);
    cloud4->setPos(550, 10);
    cloud5->setPos(700, 0);

    // Create points rectangle
    pointsRect = addRect(10, 10, 100, 50, QPen(Qt::black), QBrush(Qt::white)); // Create a white rectangle
    pointsRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pointsRect->setFlag(QGraphicsItem::ItemIsFocusable, false);
    pointsRect->setFlag(QGraphicsItem::ItemIsMovable, false);

    // Create text item for displaying points
    QString str = QString::number(totalPoints);
    pointsTextItem = new QGraphicsTextItem(str, pointsRect);
    QPointF textPos = pointsRect->boundingRect().center() - pointsTextItem->boundingRect().center();
    pointsTextItem->setPos(textPos);
}


Level3::~Level3() {
    delete bucket;
}

void Level3::updatePointsDisplay() {
    if(!isWon){
    // Update or create the text items for displaying score and drops caught
    if (!pointsTextItem ) {
        // Create the text item for displaying score
        pointsTextItem = new QGraphicsTextItem();
        addItem(pointsTextItem);
        pointsTextItem->setParentItem(pointsRect);
        QPointF scoreTextPos = pointsRect->boundingRect().center() - pointsTextItem->boundingRect().center();
        pointsTextItem->setPos(scoreTextPos);
    }

    if (!dropsTextItem) {
        // Create the text item for displaying drops caught
        dropsTextItem = new QGraphicsTextItem();
        addItem(dropsTextItem);
        dropsTextItem->setParentItem(pointsRect);
        dropsTextItem->setDefaultTextColor(Qt::red); // Set the text color to red for drops
        QPointF dropsTextPos = pointsRect->boundingRect().center() + QPointF(0, 20); // Position it below the score
        dropsTextItem->setPos(dropsTextPos);
    }

    // Update the text item with the current values
    QString scoreStr = "Score: " + QString::number(totalPoints);
    QString dropsStr = "DropsCaught: " + QString::number(DropsCaught);
    QString combinedStr = scoreStr + "\n" + dropsStr; // Combine score and drops caught with a newline in between
    pointsTextItem->setPlainText(combinedStr);

    // Position the text item within the points rectangle
    QPointF textPos = pointsRect->boundingRect().center() - pointsTextItem->boundingRect().center();
    pointsTextItem->setPos(textPos);
    if (totalPoints == 150) {
        isWon = true;
        HistoryWindow hist;
        hist.recordScore();
    }
    }
}

void Level3::addDroplet() {
    // Create droplet

    updatePointsDisplay();

    Droplet *droplet = new Droplet();
    droplet->setPixmap((QPixmap(":/images/water.gif")).scaled(30, 30));
    addItem(droplet);
    droplet->setPos(rand() % 800, 0); // Random position under clouds
    // Connect signal for deletion
    connect(droplet, &Droplet::outOfScene, [=]() {
        removeItem(droplet);
        delete droplet;
    });

}
