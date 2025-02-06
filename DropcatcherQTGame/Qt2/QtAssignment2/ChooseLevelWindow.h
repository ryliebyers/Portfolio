#ifndef CHOOSELEVELWINDOW_H
#define CHOOSELEVELWINDOW_H

#include <QDialog>
#include <QPushButton>

class LevelSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit LevelSelectionDialog(QWidget *parent = nullptr);

private:
    QPushButton* createLevelButton(const QString& text, const QString& tooltipText);
    QPushButton* createQuestionMarkButton(const QString& tooltipText);
    QPushButton *level1Button;
    QPushButton *level2Button;
    QPushButton *level3Button;


private slots:
    void startGameAtLevel1();
    void startGameAtLevel2();
    void startGameAtLevel3();
    void displayInstructions();

};

#endif // CHOOSELEVELWINDOW_H
