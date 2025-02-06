#ifndef ADDITIONALWINDOW_H
#define ADDITIONALWINDOW_H

#include <QDialog>
#include <QPushButton>

class AdditionalWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdditionalWindow(QWidget *parent = nullptr) : QDialog(parent)
    {
        // Create the Quit button
        QPushButton *quitButton = new QPushButton("Quit", this);
        quitButton->setGeometry(10, 10, 75, 30); // Set button position and size

        // Connect the Quit button to close the window
        connect(quitButton, &QPushButton::clicked, this, &AdditionalWindow::close);
    }
};

#endif // ADDITIONALWINDOW_H
