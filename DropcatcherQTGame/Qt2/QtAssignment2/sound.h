#ifndef SOUND_H
#define SOUND_H

#include <QObject>
#include <QtMultimedia/QAudio>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>

class Sound : public QObject, QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Sound(QObject *parent = nullptr);
    void AddSplash();
    void AddBeep();
signals:
};

#endif // SOUND_H
