#include "bucket.h"
#include "game1scene.h"
#include "cloud.h"
#include <QBrush>
#include <QImage>
#include <QKeyEvent>

Bucket::Bucket() {scaleFactor = 1;}
void Bucket::keyPressEvent(QKeyEvent *event) {

    qreal step = 40; // Step size for movement
    // Get the current bounding rect of the scene
    QRectF sceneRect = scene()->sceneRect();
    if (event->key() == Qt::Key_Right) {
        // Move right
        if (x() + boundingRect().width() + step < 1080) {
            setPos(x() + step, y());
        }
        // Flip horizontally from the center
        QPointF oldCenter = mapToScene(boundingRect().center()); // Previous center in scene coordinates
        setTransformOriginPoint(oldCenter); // Set the previous center as the transformation origin
        scaleFactor = -1;
        setTransform(QTransform::fromScale(scaleFactor, 1));
        QPointF newCenter = mapToScene(boundingRect().center()); // New center after transformation in scene coordinates
        QPointF diff = oldCenter - newCenter; // Calculate the difference
        setPos(x() + diff.x(), y() + diff.y());

    } else if (event->key() == Qt::Key_Left) {
        // Move left
        if (x() - step >= -40) {
            setPos(x() - step, y());
        }

        // Restore original scale
        QPointF oldCenter = mapToScene(boundingRect().center()); // Previous center in scene coordinates
        setTransformOriginPoint(oldCenter); // Set the previous center as the transformation origin
        scaleFactor = 1;
        setTransform(QTransform::fromScale(scaleFactor, 1));
        QPointF newCenter = mapToScene(boundingRect().center()); // New center after transformation in scene coordinates
        QPointF diff = oldCenter - newCenter; // Calculate the difference
        setPos(x() + diff.x(), y() + diff.y());
    }
}
