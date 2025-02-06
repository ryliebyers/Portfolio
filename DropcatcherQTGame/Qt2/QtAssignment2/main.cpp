#include <QApplication>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "game1scene.h"
#include "LoginWindow.h"
#include "historywindow.h"
#include <QDateTime>
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "globals.h"
#include <QAudioOutput>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create and display the UserInfo dialog
    UserInfo userInfoDialog;
    if (userInfoDialog.exec() != QDialog::Accepted) {
        // If the user cancels or closes the dialog, exit the application
        return 0;
    }

    // Retrieve signed-in user information from the UserInfo dialog
    QString fullName = userInfoDialog.getSignedInFullName();
    QString profilePicturePath = userInfoDialog.getSignedInProfilePicturePath();
    QString dateOfBirth = userInfoDialog.getDateOfBirth();


    // Create a widget to hold the profile picture, user name, and score
    QWidget *bottomWidget = new QWidget();
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);

    if(level1Clicked == true){
        // Create view to visualize the scene
        Level1 *scene1 = new Level1(fullName, profilePicturePath);

        QGraphicsView *view = new QGraphicsView(scene1);
        view->setFixedSize(910, 512);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Create a QWidget to hold the view and additional widgets
        QWidget *mainWidget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);



        // Set the layout of the bottom widget
        bottomWidget->setLayout(bottomLayout);

        // Add the view to the main layout
        mainLayout->addWidget(view);
        // Add the bottom widget to the main layout
        mainLayout->addWidget(bottomWidget);

        // Set the main layout to the main widget
        mainWidget->setLayout(mainLayout);

        // Set the main widget as the central widget of the application
        mainWidget->show();
        level1Clicked = false;

    }


    if(level2Clicked == true){
        // Create view to visualize the scene
        Level2 *scene1 = new Level2(fullName, profilePicturePath);

        QGraphicsView *view = new QGraphicsView(scene1);
        view->setFixedSize(910, 512);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Create a QWidget to hold the view and additional widgets
        QWidget *mainWidget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);



        // Set the layout of the bottom widget
        bottomWidget->setLayout(bottomLayout);

        // Add the view to the main layout
        mainLayout->addWidget(view);
        // Add the bottom widget to the main layout
        mainLayout->addWidget(bottomWidget);

        // Set the main layout to the main widget
        mainWidget->setLayout(mainLayout);

        // Set the main widget as the central widget of the application
        mainWidget->show();
        level2Clicked = false;

    }


    if(level3Clicked == true){
        // Create view to visualize the scene
        Level3 *scene1 = new Level3(fullName, profilePicturePath);

        QGraphicsView *view = new QGraphicsView(scene1);
        view->setFixedSize(910, 512);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Create a QWidget to hold the view and additional widgets
        QWidget *mainWidget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);



        // Set the layout of the bottom widget
        bottomWidget->setLayout(bottomLayout);

        // Add the view to the main layout
        mainLayout->addWidget(view);
        // Add the bottom widget to the main layout
        mainLayout->addWidget(bottomWidget);

        // Set the main layout to the main widget
        mainWidget->setLayout(mainLayout);

        // Set the main widget as the central widget of the application
        mainWidget->show();
        level3Clicked = false;

    }



    // Create and add profile picture
    QPixmap profilePicture(profilePicturePath);
    QLabel *profilePictureLabel = new QLabel();
    profilePictureLabel->setPixmap(profilePicture.scaled(45, 45));
    bottomLayout->addWidget(profilePictureLabel);
    // Add user name label
    QLabel *userNameLabel = new QLabel(fullName);
    userNameLabel->setStyleSheet("color: back; font-size: 14px; font-weight: bold;");
    bottomLayout->addWidget(userNameLabel);

    // Add date label
    QLabel *dateLabel = new QLabel();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDate = currentDateTime.toString("ddd MMM d yyyy");
    dateLabel->setText(formattedDate);
    dateLabel->setStyleSheet("color: black; font-size: 14px; font-weight: bold;");
    bottomLayout->addWidget(dateLabel);


    // Check if user is signed in
    if (userInfoDialog.isSignedInUser == true) { // Use '==' for comparison, not '='
        // Create "View History" button
        QPushButton *viewHistoryButton = new QPushButton("View History");
        // Set style sheet for the button
        viewHistoryButton->setStyleSheet("QPushButton {"
                                         "background-color: darkgreen;"
                                         "color: white;"
                                         "border-style: outset;"
                                         "border-width: 2px;"
                                         "border-radius: 10px;"
                                         "border-color: beige;"
                                         "font: bold 14px;"
                                         "min-width: 10em;"
                                         "padding: 6px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "background-color: green;"
                                         "}");

        // Connect the button's clicked signal to a lambda function
        QObject::connect(viewHistoryButton, &QPushButton::clicked, [&]() {
            // Create and display the history window
            HistoryWindow *historyWindow = new HistoryWindow();
            historyWindow->show();
        });

        // Add the "View History" button to the layout
        bottomLayout->addWidget(viewHistoryButton);
    }


    // Create "Quit" button
    QPushButton *quitButton = new QPushButton("Quit");
    // Set style sheet for the button
    quitButton->setStyleSheet("QPushButton {"
                              "background-color: blue;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 2px;"
                              "border-radius: 10px;"
                              "border-color: beige;"
                              "font: bold 14px;"
                              "min-width: 10em;"
                              "padding: 6px;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: darkblue;"
                              "}");

    // Connect the "Quit" button's clicked signal to QApplication::quit
    QObject::connect(quitButton, &QPushButton::clicked, &a, &QApplication::quit);

    // Add the "Quit" button to the layout
    bottomLayout->addWidget(quitButton);

    // Set the layout of the bottom widget
    bottomWidget->setLayout(bottomLayout);

    return a.exec();
}
