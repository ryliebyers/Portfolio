#include "sound.h"
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlayer>
#include <QAudio>
#include <QSoundEffect>
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>
Sound::Sound(QObject *parent)
    : QObject{parent}
{

}

void Sound::AddSplash() {
    QMediaPlayer *splash = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    splash->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
    splash->setSource(QUrl("qrc:/sounds/Splash.wav"));

    splash->play();
}

void Sound::AddBeep() {
    QMediaPlayer *beep = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    beep->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
    beep->setSource(QUrl("qrc:/sounds/Beep.mp3"));
    beep->play();
}
