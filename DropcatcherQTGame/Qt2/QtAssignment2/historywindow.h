// historywindow.h

#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class HistoryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryWindow(QWidget *parent = nullptr);
//  void  showScoreHistoryPopup();
    void recordScore();
signals:

public slots:

private:

};

#endif // HISTORYWINDOW_H
