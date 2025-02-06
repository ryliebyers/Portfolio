#ifndef SIGNUPUI_H
#define SIGNUPUI_H
#include "LoginWindow.h"
#include <QWidget>

namespace Ui {
class SignUpUI;
}

class SignUpUI : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpUI(QWidget *parent = nullptr);
    ~SignUpUI();

private slots:
    void on_submitBtn_clicked();


private:
    Ui::SignUpUI *ui;
    QString profilePicturePath;
    void populateImageSelector();
    bool isValidPassword(const QString &password);
    bool usernameExists(const QString &username, const QString &filePath);


};

#endif // SIGNUPUI_H
