#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "ui_signupui.h"



class UserInfo : public QDialog {
    Q_OBJECT


public:
    QString m_profilePicturePath; // Store the profile picture path
    QString m_fullName; // Store the user's full name
    QString userBirthday;
    QString m_dateOfBirth;
    QString  m_UserName;

    bool isSignedInUser=false;


    explicit UserInfo(QWidget *parent = nullptr);
    // Getter functions for user information
    QString getFirstName() const { return firstNameLineEdit->text(); }
    QString getLastName() const { return lastNameLineEdit->text(); }
    QString getProfilePicturePath() const;
    QString getFullName() const;
    QString getSignedInFullName() const;
     QString getDateOfBirth() const;
     // Declaration for getting signed-in user's full name
    QString getSignedInProfilePicturePath() const;
     QString getUserName() const;

signals:
    void startGameRequested(const QString& fullName, const QString& profilePicturePath);

private slots:
    void startUserGame();
    void startGuestGame();
    void signUp();
    void showLevelSelectionDialog();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *firstNameLineEdit;
    QLineEdit *lastNameLineEdit;
    QLineEdit *profilePicturePathLineEdit;
    Ui::SignUpUI *ui;
    QString m_signedInFullName;
    QString m_signedInProfilePicturePath;
    QLabel *m_signedInFullNameLabel;
    QLabel *m_signedInProfilePictureLabel;


    // Function prototype for creating question mark button
    QPushButton* createQuestionMarkButton(const QString& tooltipText);

};

#endif // LOGINWINDOW_H

