#include "signupui.h"
#include "ui_signupui.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QRegularExpression>

SignUpUI::SignUpUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUpUI)
{
    ui->setupUi(this);
    populateImageSelector();

    connect(ui->imageSelectorComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
                profilePicturePath = ui->imageSelectorComboBox->itemData(index).toString();
                QPixmap pixmap(profilePicturePath);
                ui->PPLabel->setPixmap(pixmap.scaled(ui->PPLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            });

}

SignUpUI::~SignUpUI()
{
    delete ui;
}

void SignUpUI::on_submitBtn_clicked()
{
    // Collect data from UI elements
    QString firstName = ui->FNEdit->text();
    QString lastName = ui->LNEdit->text();
    QDate dateOfBirth = ui->DOBEdit->date();
    QString gender = ui->genderBox->currentText();  // Assuming a QComboBox for gender
    QString username = ui->UNEdit->text();
    QString password = ui->PWEdit->text();


    // Specify the file path in a writable location
    QString filePath = QDir::homePath() + "/userInfo.txt";  // Adjust the path as needed

    // Validate Password
    if (!isValidPassword(password)) {
        QMessageBox::warning(this, "Error", "Password must be at least 8 characters long and include uppercase, lowercase, and numbers.");
        return;
    }

    // Check Username Uniqueness
    if (usernameExists(username, filePath)) {
        QMessageBox::warning(this, "Error", "Username already exists. Please choose another username.");
        return;
    }

    // Check if the directory exists; if not, create it
    QDir dir(QDir::homePath());
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Open the file to append text
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file for writing.");
        return;
    }

    // Write the collected data to the file
    QTextStream out(&file);
    out << "First Name: " << firstName << "\n";
    out << "Last Name: " << lastName << "\n";
    out << "Date of Birth: " << dateOfBirth.toString("yyyy-MM-dd") << "\n";
    out << "Gender: " << gender << "\n";
    out << "Username: " << username << "\n";
    out << "Password: " << password << "\n";  // Caution: saving passwords in plain text is insecure
    out << "Profile Picture Path: " << profilePicturePath << "\n";

    file.close();

    // Optionally notify the user that the data has been saved
    QMessageBox::information(this, "Information", "Profile data saved successfully.");
    // QMessageBox::information(nullptr, "Profile Picture Path", "Path: " + profilePicturePath);

}


void SignUpUI::populateImageSelector() {
    QStringList imageFiles = {
        ":/profile_pictures/00a8a45a0fc6-1.jpg",
        ":/profile_pictures/0e94ecedf322-1.jpg",
        ":/profile_pictures/1c1e2e106f3c-1.jpg",
        ":/profile_pictures/3d1df0e610c5-1.jpg",
        ":/profile_pictures/4c8451069107-1.jpg",
        ":/profile_pictures/4db0c552f4b2-1.jpg",
        ":/profile_pictures/4eb9085a7e26-1.jpg",
        ":/profile_pictures/4fd0dbd94424-1.jpg",
        ":/profile_pictures/6a53966fab09-1.jpg",
        ":/profile_pictures/6b30e1249c34-1.jpg",
        ":/profile_pictures/6d09bc37d694-1.jpg",
        ":/profile_pictures/6d7765802444-1.jpg",
        ":/profile_pictures/7d9abe1a0ee8-1.jpg",
        ":/profile_pictures/9b960a326fc9-1.jpg",
        ":/profile_pictures/10df6f39e685-1.jpg",
        ":/profile_pictures/22dda4ab0a99-1.jpg",
        ":/profile_pictures/28ad7d77db50-1.jpg",
        ":/profile_pictures/37fd68259f53-1.jpg",
        ":/profile_pictures/38adf339a72f-1.jpg",
        ":/profile_pictures/38f667ab232f-1.jpg",
        ":/profile_pictures/62b4fb4c59cc-1.jpg",
        ":/profile_pictures/65e9ba88e697-1.jpg",
        ":/profile_pictures/73f06f864932-1.jpg",
        ":/profile_pictures/88feec36b4ac-1.jpg",
        ":/profile_pictures/90f6165211d1-1.jpg",
        ":/profile_pictures/94ab6dc2772b-1.jpg",
        ":/profile_pictures/97df66772a11-1.jpg",
        ":/profile_pictures/264d6e171a02-1.jpg",
        ":/profile_pictures/268bdba33a8c-1.jpg",
        ":/profile_pictures/395e8c21825e-1.jpg",
        ":/profile_pictures/573a491f9a17-1.jpg",
        ":/profile_pictures/684d37aff60d-1.jpg",
        ":/profile_pictures/785cbf442598-1.jpg",
        ":/profile_pictures/912e19f87de4-1.jpg",
        ":/profile_pictures/932a73924ccd-1.jpg",
        ":/profile_pictures/2097e4f32072-1.jpg",
        ":/profile_pictures/7453f10fd3b1-1.jpg",
        ":/profile_pictures/8453df62014e-1.jpg",
        ":/profile_pictures/27599d99ab90-1.jpg",
        ":/profile_pictures/35045dc1112b-1.jpg",
        ":/profile_pictures/41782e913184-1.jpg",
        ":/profile_pictures/735929c6dcbb-1.jpg",
        ":/profile_pictures/868605c2ea73-1.jpg",
        ":/profile_pictures/1682475db634-1.jpg",
        ":/profile_pictures/03419146a1f8-1.jpg",
        ":/profile_pictures/25615398f777-1.jpg",
        ":/profile_pictures/595706784222-1.jpg",
        ":/profile_pictures/a9fb5245072e-1.jpg",
        ":/profile_pictures/b7f8656af090-1.jpg",
        ":/profile_pictures/b36dfa69507f-1.jpg",
        ":/profile_pictures/c8db9a78051a-1.jpg",
        ":/profile_pictures/c9b47d71709d-1.jpg",
        ":/profile_pictures/d3d9ddb15481-1.jpg",
        ":/profile_pictures/d7272cb0a91d-1.jpg",
        ":/profile_pictures/e2d8d2b4b06f-1.jpg",
        ":/profile_pictures/e89db0dc4721-1.jpg",
        ":/profile_pictures/e5096a207bd8-1.jpg",
        ":/profile_pictures/f3ff4e7c4380-1.jpg",
        ":/profile_pictures/f9c0b27825ce-1.jpg",
        ":/profile_pictures/f304e79d47eb-1.jpg",
        ":/profile_pictures/f9837eaf06fa-1.jpg",
        ":/profile_pictures/f32753e1f140-1.jpg",
        ":/profile_pictures/fa66ceb01814-1.jpg",
        ":/profile_pictures/ff31d56b4501-1.jpg"
    };

    for (const QString &filePath : imageFiles) {
        QPixmap pixmap(filePath);
        ui->imageSelectorComboBox->addItem(QIcon(pixmap.scaled(50, 50, Qt::KeepAspectRatio)), QString(), QVariant(filePath));
    }
}

bool SignUpUI::isValidPassword(const QString &password) {
    return password.length() >= 8 &&
           password.contains(QRegularExpression("[A-Z]")) &&
           password.contains(QRegularExpression("[a-z]")) &&
           password.contains(QRegularExpression("[0-9]"));
}

bool SignUpUI::usernameExists(const QString &username, const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "userInof.txt was created. User information was stored in your home directory.");
        return false;
    }

    QTextStream in(&file);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        if (line.contains("Username: " + username)) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
