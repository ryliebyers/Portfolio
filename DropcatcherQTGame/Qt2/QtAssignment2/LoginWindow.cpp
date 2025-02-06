#include "LoginWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include "ChooseLevelWindow.h"
#include "signupui.h"
#include "game1scene.h"
#include <QGraphicsView>
#include "globals.h"
#include "ChooseGameWindow.h"

UserInfo::UserInfo(QWidget *parent) : QDialog(parent), ui(new Ui::SignUpUI) {
    // Initialize member variables
    m_signedInFullNameLabel = nullptr;
    m_signedInProfilePictureLabel = nullptr;

//=============================================== Login Window ==========================================================//
    // Set window title
    setWindowTitle("Login Window");

    // Set the fixed size of the dialog window
    setFixedSize(400, 300);

    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

//=============================================== Input Layout  ============================================================//

    // Create layout for input fields
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignCenter);

    // Create layout for input fields
    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->setAlignment(Qt::AlignCenter);

//============================================ Labels and Input Fields  ====================================================//

    // Username Label and Input Field
    QHBoxLayout *usernameLayout = new QHBoxLayout;
    usernameLayout->setAlignment(Qt::AlignLeft);
    QLabel *usernameLabel = new QLabel("Username:", this);
    usernameLabel->setAlignment(Qt::AlignLeft);
    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Username");
    usernameLineEdit->setFixedWidth(250);
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameLineEdit);
    usernameLayout->setSpacing(10);
    inputLayout->addLayout(usernameLayout);

    // Password Label and Input Field
    QHBoxLayout *passwordLayout = new QHBoxLayout;
    passwordLayout->setAlignment(Qt::AlignLeft);
    QLabel *passwordLabel = new QLabel("Password:", this);
    passwordLabel->setAlignment(Qt::AlignLeft);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setFixedWidth(250);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);
    passwordLayout->setSpacing(10);
    inputLayout->addLayout(passwordLayout);

    layout->addLayout(inputLayout);
    mainLayout->addLayout(layout);

//================================================= Sign In Button  =======================================================//

    // Create a QHBoxLayout to hold the "Sign in" button and question mark button
    QHBoxLayout *signInLayout = new QHBoxLayout;
    QPushButton *signInButton = new QPushButton("Sign in", this);
    signInButton->setStyleSheet("QPushButton {"
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

    QPushButton *signInQuestionMarkButton = createQuestionMarkButton("Sign In: Click here to access your account by entering your username and password.");
    signInLayout->addWidget(signInButton);
    signInLayout->addWidget(signInQuestionMarkButton);
    mainLayout->addLayout(signInLayout);

//================================================= Sign Out Button  =======================================================//

    // Create a QHBoxLayout to hold the "Sign Up" button and question mark button
    QHBoxLayout *signUpLayout = new QHBoxLayout;
    QPushButton *signUpButton = new QPushButton("Sign up", this);
    signUpButton->setStyleSheet("QPushButton {"
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

    QPushButton *signUpQuestionMarkButton = createQuestionMarkButton("Sign Up: Click here to create a new account. Start your journey now!"); 
    signUpLayout->addWidget(signUpButton);
    signUpLayout->addWidget(signUpQuestionMarkButton);
    mainLayout->addLayout(signUpLayout);

//================================================= Guest Login Button  ====================================================//

    // Create a QHBoxLayout to hold the "Guest login" button and question mark button
    QHBoxLayout *guestLoginLayout = new QHBoxLayout;

    QPushButton *guestLogin = new QPushButton("Guest login", this);
    guestLogin->setStyleSheet("QPushButton {"
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

    QPushButton *guestQuestionMarkButton = createQuestionMarkButton("Guest Login: Sign in as a temporary user to access limited features. Your progress and data may not be saved between sessions. For full access and to save your game history, consider creating an account.");
    guestLoginLayout->addWidget(guestLogin);
    guestLoginLayout->addWidget(guestQuestionMarkButton);
    mainLayout->addLayout(guestLoginLayout);

//================================================= Connect Buttons   ====================================================//

    connect(guestLogin, &QPushButton::clicked, this, &UserInfo::startGuestGame);
    connect(signInButton, &QPushButton::clicked, this, &UserInfo::startUserGame);
    connect(signUpButton, &QPushButton::clicked, this, &UserInfo::signUp);
}

//================================================= Question Mark Label   ===================================================//

QPushButton* UserInfo::createQuestionMarkButton(const QString& tooltipText) {
    QPushButton *questionMarkButton = new QPushButton(this);
    questionMarkButton->setFixedSize(20, 20);
    questionMarkButton->setIcon(QIcon(":/images/questionMark.png"));
    questionMarkButton->setIconSize(QSize(20, 20));
    questionMarkButton->setFlat(true);
    questionMarkButton->setToolTip(tooltipText);
    return questionMarkButton;
}

//================================================= Sign Up Function   ===================================================//

void UserInfo::signUp() {
    SignUpUI *signUpForm = new SignUpUI(this);  // Create a new instance of SignUpUI QDialog
    signUpForm->setModal(true);  // Set the dialog to be modal
    signUpForm->exec();  // Show the SignUpUI form as a modal dialog
}

//================================================= Start User Game ======================================================//

void UserInfo::startUserGame() {
    // Open the file for reading
    QString filePath = QDir::homePath() + "/userInfo.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return;
    }
    // Read the file line by line
    QTextStream in(&file);
    while (!in.atEnd()) {
        // Read user information from the file
        QString firstName = in.readLine().split(":").at(1).trimmed();
        QString lastName = in.readLine().split(":").at(1).trimmed();
        QString dateOfBirth = in.readLine().split(":").at(1).trimmed();
        QString gender = in.readLine().split(":").at(1).trimmed();
         USERNAME = in.readLine().split(":").at(1).trimmed();
        QString password = in.readLine().split(":").at(1).trimmed();
        // QString profilePicturePath = in.readLine().split(":").at(1).trimmed();
        QString line = in.readLine();
        QStringList parts = line.split(":");
        QString profilePicturePath;
        if (parts.count() > 2) {
            // Join all parts after the first colon, since the path itself might contain colons (as seen with ":/")
            profilePicturePath = parts.mid(1).join(":").trimmed();
        }
        // Check if entered username and password match
        if (USERNAME == usernameLineEdit->text() && password == passwordLineEdit->text()) {
            isSignedInUser = true;
            // Close the dialog if the credentials are correct
            accept();
            // Emit the signal with the full name and profile picture path
            emit startGameRequested(firstName + " " + lastName, profilePicturePath);
            // Store the full name for later retrieval
            m_signedInFullName = firstName + " " + lastName;
            m_signedInProfilePicturePath = profilePicturePath;
            // Check if today is the user's birthday
            QDate today = QDate::currentDate();
            QDate userBirthday = QDate::fromString(dateOfBirth, "yyyy-MM-dd");
            if (userBirthday.month() == today.month() && userBirthday.day() == today.day()) {
                // Display a popup window for birthday celebration
                QMessageBox birthdayPopup;
                QPixmap birthdayImage(":/images/birthdayEmoji.jpeg");
                birthdayImage = birthdayImage.scaled(200, 200, Qt::KeepAspectRatio); // Adjust the size here
                birthdayPopup.setIconPixmap(birthdayImage); // Set the resized birthday image
                birthdayPopup.setWindowTitle("Happy Birthday!");
                birthdayPopup.setText("Happy Birthday, " + m_signedInFullName + "!");
                QPushButton *thankYouButton = birthdayPopup.addButton("Thank you", QMessageBox::AcceptRole);
                thankYouButton->setDefault(true);
                birthdayPopup.exec();
            }
             emit startGameRequested(firstName + " " + lastName, profilePicturePath);
            // // Close the dialog if the credentials are correct
            accept();

             // Open the intermediate dialog first
             IntermediateDialog *intermediateDialog = new IntermediateDialog(this);
             connect(intermediateDialog, &IntermediateDialog::collectingDropletsClicked, this, &UserInfo::showLevelSelectionDialog);
             intermediateDialog->exec();
            return;
        }
    }

    // Show error message if username is not found in the file
    QMessageBox::critical(this, "Invalid Credentials", "The username or password is invalid. Please sign up to create an account.");
}

//================================================= Start Guest Game ======================================================//

void UserInfo::startGuestGame() {
    // Close the dialog if the credentials are correct
    accept();
    // Open the intermediate dialog first
    IntermediateDialog *intermediateDialog = new IntermediateDialog(this);
    connect(intermediateDialog, &IntermediateDialog::collectingDropletsClicked, this, &UserInfo::showLevelSelectionDialog);
    intermediateDialog->exec();
    return;
}

//================================================= Choose Level Window ==================================================//

void UserInfo::showLevelSelectionDialog() {
    // Open the level selection dialog
    LevelSelectionDialog *levelDialog = new LevelSelectionDialog(this);
    levelDialog->exec();
}


//====================================================== Getters  ========================================================//


QString UserInfo::getSignedInFullName() const {
    return m_signedInFullName;
}

QString UserInfo::getSignedInProfilePicturePath() const {
    return m_signedInProfilePicturePath;
}
QString UserInfo::getDateOfBirth() const {
    return m_dateOfBirth;
}

QString UserInfo::getUserName() const {
    return m_UserName;
}

//====================================================== The End  =========================================================//
