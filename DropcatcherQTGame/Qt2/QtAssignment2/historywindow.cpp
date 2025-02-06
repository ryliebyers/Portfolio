// historywindow.cpp
#include "signupui.h"
#include "LoginWindow.h"
#include "historywindow.h"
#include "gamehistorymanager.h"
#include <QMessageBox>
#include "globals.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

HistoryWindow::HistoryWindow(QWidget *parent) : QWidget(parent)
{
 //  recordScore(); // Call recordScore in constructor

   QVBoxLayout *layout = new QVBoxLayout(this);

   QString filePath = QDir::homePath() + "/" + USERNAME + ".txt";
   QFile file(filePath);

   if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QLabel *errorLabel = new QLabel("Failed to open score history file.");
       layout->addWidget(errorLabel);
       return;
   }

   QTextStream in(&file);
   QStringList scores;
   while (!in.atEnd()) {
       QString line = in.readLine();
       scores.append(line);
   }
   file.close();

   if (scores.isEmpty()) {
       QLabel *infoLabel = new QLabel("No scores found for this user.");
       layout->addWidget(infoLabel);
   } else {
       int highestScore = 0;
       foreach(const QString& score, scores) {
           int currentScore = score.split(":").last().toInt();
           highestScore = qMax(highestScore, currentScore);
       }

       QLabel *titleLabel = new QLabel("Score History for " + USERNAME + ":");
       layout->addWidget(titleLabel);

       foreach(const QString& score, scores) {
           QLabel *scoreLabel = new QLabel(score);
           layout->addWidget(scoreLabel);
       }

       QLabel *highestScoreLabel = new QLabel("Highest Score: " + QString::number(highestScore));
       layout->addWidget(highestScoreLabel);
   }

   QPushButton *okButton = new QPushButton("OK");
   layout->addWidget(okButton);
   connect(okButton, &QPushButton::clicked, this, &HistoryWindow::close);
}

void HistoryWindow::recordScore() {
    if (((isWon && totalPoints == 150)) || &QApplication::quit) {

    QString filePath = QDir::homePath() + "/" + USERNAME + ".txt";
    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open score history file.");
        return;
    }

    // Get current date and time
    QDateTime dateTime = QDateTime::currentDateTime();

    // Write score to file
    QTextStream out(&file);
    out << dateTime.toString(Qt::ISODate) << " - Total Points: " << totalPoints << "\n";

    file.close();
    }
}
