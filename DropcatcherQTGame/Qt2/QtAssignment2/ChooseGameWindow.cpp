#include "ChooseGameWindow.h"



IntermediateDialog::IntermediateDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Choose Game");
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Please choose a game to play!");
    layout->addWidget(label);

//============================================== Collecting Droplets Game Button  ============================================//

    QPushButton *collectingDropletsButton = new QPushButton("Collecting Droplets Game");
    collectingDropletsButton->setStyleSheet("QPushButton {"
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

    layout->addWidget(collectingDropletsButton);

    connect(collectingDropletsButton, &QPushButton::clicked, this, &IntermediateDialog::onCollectingDropletsClicked);
}

//================================================= OnClicked Action  ======================================================//

void IntermediateDialog::onCollectingDropletsClicked()
{
    emit collectingDropletsClicked();
    close();
}

//======================================================= The End  ==========================================================//
