#ifndef NEWUSERSCREEN_H
#define NEWUSERSCREEN_H

#include <QCloseEvent>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <string>
#include "Netflicks.h"

class NewUserScreen : public QMainWindow {
  Q_OBJECT

  public:
  NewUserScreen(QMainWindow* loginScreen, Netflicks* netflicks, bool update) {
    this->loginScreen = loginScreen;
    this->netflicks = netflicks;
    this->update = update;

    mainWindow = new QWidget;
    mainGridLayout = new QGridLayout;
    signUpLabel = new QLabel("Please enter your information");
    userIDLineEdit = new QLineEdit;
    userIDFormLayout = new QFormLayout;
    userNameLineEdit = new QLineEdit;
    userNameFormLayout = new QFormLayout;
    userAddressLineEdit = new QLineEdit;
    userAddressFormLayout = new QFormLayout;
    userNumberLineEdit = new QLineEdit;
    userNumberFormLayout = new QFormLayout;
    userPasswordLineEdit = new QLineEdit;
    userPasswordFormLayout = new QFormLayout;
    confirmButton = new QPushButton("Confirm");
    cancelButton = new QPushButton("Cancel");

    userIDFormLayout->addRow("User ID: ", userIDLineEdit);
    userNameFormLayout->addRow("Name: ", userNameLineEdit);
    userAddressFormLayout->addRow("Address: ", userAddressLineEdit);
    userNumberFormLayout->addRow("Credit Card Number: ", userNumberLineEdit);
    userPasswordFormLayout->addRow("Password: ", userPasswordLineEdit);
    signUpLabel->setAlignment(Qt::AlignCenter);

    mainGridLayout->addWidget(signUpLabel, 1, 1, 1, 2);
    mainGridLayout->addLayout(userIDFormLayout, 2, 1, 1, 2);
    mainGridLayout->addLayout(userNameFormLayout, 3, 1, 1, 2);
    mainGridLayout->addLayout(userAddressFormLayout, 4, 1, 1, 2);
    mainGridLayout->addLayout(userNumberFormLayout, 5, 1, 1, 2);
    mainGridLayout->addLayout(userPasswordFormLayout, 6, 1, 1, 2);
    mainGridLayout->addWidget(confirmButton, 7, 1, 1, 1);
    mainGridLayout->addWidget(cancelButton, 7, 2, 1, 1);

    if(update == true) {
      userIDLineEdit->hide();
    }

    mainWindow->setLayout(mainGridLayout);
    setCentralWidget(mainWindow);
    setFixedSize(300, 250);

    QObject::connect(confirmButton, SIGNAL(clicked()), SLOT(confirmButtonClicked()));
    QObject::connect(cancelButton, SIGNAL(clicked()), SLOT(cancelButtonClicked()));
    QObject::connect(userPasswordLineEdit, SIGNAL(returnPressed()), SLOT(confirmButtonClicked()));
  }

  ~NewUserScreen() {
    delete signUpLabel;
    delete userIDLineEdit;
    delete userIDFormLayout;
    delete userNameLineEdit;
    delete userNameFormLayout;
    delete confirmButton;
    delete cancelButton;
    delete mainGridLayout;
    delete mainWindow;
  }

  void closeEvent(QCloseEvent *event) {
    loginScreen->show();
    close();
  }

 private slots:
  void confirmButtonClicked() {
    QString userIDInput = userIDLineEdit->text();
    string userID = userIDInput.toStdString();
    
    QString userNameInput = userNameLineEdit->text();
    string userName = userNameInput.toStdString();

    QString userAddressInput = userAddressLineEdit->text();
    string userAddress = userAddressInput.toStdString();

    QString userNumberInput = userNumberLineEdit->text();
    string userNumber = userNumberInput.toStdString();

    QString userPasswordInput = userPasswordLineEdit->text();
    string userPassword = userPasswordInput.toStdString();

    if(!(userID == "" or userName == "" or userAddress == "" or userNumber == "" or userPassword == "") and update == false) {
      if(netflicks->createNewUser(userID, userName, userAddress, userNumber, userPassword)) {
	QMessageBox confirmationMessage;
	confirmationMessage.information(0, "Confirmation", "Your account has been created.");
	confirmationMessage.setFixedSize(300, 120);
	
	loginScreen->show();
	close();
      } else {
	QMessageBox errorMessage;
	errorMessage.critical(0, "Error", "The user ID you entered is invalid.");
	errorMessage.setFixedSize(300, 120);
      }
    } else if(update == true) {
      if(userName != "") {
	netflicks->setUserName(userName);
      }

      if(userAddress != "") {
	netflicks->setUserAddress(userAddress);
      }

      if(userNumber != "") {
	netflicks->setUserNumber(userNumber);
      }
      
      if(userPassword != "") {
	netflicks->setUserPassword(userPassword);
      }

      QMessageBox confirmationMessage;
      confirmationMessage.information(0, "Confirmation", "Your account has been updated.");
      confirmationMessage.setFixedSize(300, 120);
      
      loginScreen->show();
      close();
    } else {
      QMessageBox errorMessage;
      errorMessage.critical(0, "Error", "You did not enter all of your information.");
      errorMessage.setFixedSize(300, 120);
    }
  }

  void cancelButtonClicked() {
    loginScreen->show();
    close();
  }

 private:
  QWidget *mainWindow;
  QGridLayout *mainGridLayout;
  QLabel *signUpLabel;

  QLineEdit *userIDLineEdit;
  QFormLayout *userIDFormLayout;

  QLineEdit *userNameLineEdit;
  QFormLayout *userNameFormLayout;

  QLineEdit *userAddressLineEdit;
  QFormLayout *userAddressFormLayout;

  QLineEdit *userNumberLineEdit;
  QFormLayout *userNumberFormLayout;

  QLineEdit *userPasswordLineEdit;
  QFormLayout *userPasswordFormLayout;

  bool update;
 
  QPushButton *confirmButton;
  QPushButton *cancelButton;
  QMainWindow *loginScreen;
  Netflicks *netflicks;
};

#endif
