#include "ChooseLevelWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QScrollArea>
#include "globals.h"
LevelSelectionDialog::LevelSelectionDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Choose Level");
    resize(450, 300);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    // Add instruction label
    QLabel *instructionLabel = new QLabel("Choose the Level: Pick one of the options below");
    instructionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(instructionLabel);

//===================================================== Easy Level Button  ==================================================//

    // Create level buttons and question mark buttons for each level
    QHBoxLayout *level1Layout = new QHBoxLayout; // Create a horizontal layout for level 1
    level1Button = new QPushButton("Easy", this);
    level1Button->setStyleSheet("QPushButton {"
                                "background-color: darkblue;"
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
                                "background-color: blue;"
                                "}");
    connect(level1Button, &QPushButton::clicked, this, &LevelSelectionDialog::startGameAtLevel1);
    level1Layout->addWidget(level1Button); // Add the level button to the layout
    mainLayout->addLayout(level1Layout); // Add the horizontal layout to the main vertical layout

//===================================================== Medium Level Button  ================================================//

    // Repeat the same process for level 2
    QHBoxLayout *level2Layout = new QHBoxLayout; // Create a horizontal layout for level 2
    level2Button = new QPushButton("Medium", this);
    level2Button->setStyleSheet("QPushButton {"
                                "background-color: darkorange;"
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
                                "background-color: orange;"
                                "}");
    connect(level2Button, &QPushButton::clicked, this, &LevelSelectionDialog::startGameAtLevel2);
    level2Layout->addWidget(level2Button);
    mainLayout->addLayout(level2Layout);

//===================================================== Hard Level Button  ==================================================//

    // Repeat the same process for level 3
    QHBoxLayout *level3Layout = new QHBoxLayout; // Create a horizontal layout for level 3
    level3Button = new QPushButton("Hard", this);
    level3Button->setStyleSheet("QPushButton {"
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
    connect(level3Button, &QPushButton::clicked, this, &LevelSelectionDialog::startGameAtLevel3);
    level3Layout->addWidget(level3Button);
    mainLayout->addLayout(level3Layout);

//===================================================== Instruction Button ================================================//

    // Create the instructions button
    QPushButton *instructionsButton = new QPushButton("Instructions");
    instructionsButton->setStyleSheet("QPushButton {"
                                      "background-color: gray;"
                                      "color: white;"
                                      "border-style: outset;"
                                      "border-width: 2px;"
                                      "border-radius: 10px;"
                                      "border-color: beige;"
                                      "font: bold 14px;"
                                      "max-width: 100px;"
                                      "padding: 6px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: darkgray;"
                                      "}");
    connect(instructionsButton, &QPushButton::clicked, this, &LevelSelectionDialog::displayInstructions);

    mainLayout->addWidget(instructionsButton); // Add the button to the layout


//===================================================== Start Game Levels     =============================================//

}

void LevelSelectionDialog::startGameAtLevel1() {
    // Start the game at Level 1
    level1Clicked = true;
    accept();
}

void LevelSelectionDialog::startGameAtLevel2() {
    // Start the game at Level 2
    level2Clicked = true;
    accept();
}

void LevelSelectionDialog::startGameAtLevel3() {
    // Start the game at Level 3
    level3Clicked = true;
    accept();
}

//===================================================== Display Instructions =============================================//
void LevelSelectionDialog::displayInstructions() {
    // Define the instructions text
    QString instructionsText = "Game Instructions:\n\n"
                               "Welcome to the Water Droplet Collector Game!\n\n"
                               "Objective:\n"
                               "Your goal is to collect water droplets to earn points and progress through the levels.\n\n"
                               "How to Play:\n\n"
                               "Click on the 'Level 1', 'Level 2', or 'Level 3' button to choose the difficulty level.\n"
                               "Use the bucket to catch falling water droplets. Each droplet caught earns you points.\n"
                               "You need to collect 150 points to win the game.\n"
                               "Be careful! Missing 5 droplets will end the game.\n"
                               "The speed of the water droplets increases as you collect more. Keep an eye on their speed!\n\n"
                               "Game Levels:\n\n"
                               "Level 1: The easiest level with slow-moving droplets.\n"
                               "Level 2: A moderate challenge with faster droplets.\n"
                               "Level 3: Test your skills with the fastest and most challenging droplets.\n\n"
                               "Tips:\n\n"
                               "Stay focused and react quickly to catch as many droplets as possible.\n"
                               "Watch out for sound cues to know when you catch or miss a droplet.\n"
                               "Don't let the droplets overwhelm you, especially at higher levels!\n\n"
                               "Good luck and have fun!";

    // Create a pop-up window to display instructions
    QDialog instructionsDialog(this);
    instructionsDialog.setWindowTitle("Game Instructions");
    instructionsDialog.setFixedSize(600, 550); // Set the size of the dialog
    // Create a layout for the instructions
    QVBoxLayout *instructionsLayout = new QVBoxLayout(&instructionsDialog);
    QLabel *instructionsLabel = new QLabel();
    instructionsLabel->setText(instructionsText);
    instructionsLayout->addWidget(instructionsLabel);
    // Add a button to close the instructions window
    QPushButton *closeButton = new QPushButton("Close");
    QObject::connect(closeButton, &QPushButton::clicked, &instructionsDialog, &QDialog::close);
    instructionsLayout->addWidget(closeButton);
    instructionsDialog.exec(); // Display the instructions dialog
}

//=========================================================== The END  ======================================================//

