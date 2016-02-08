#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

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
#include "NewUserScreen.h"
#include "MainScreen.h"

class LoginScreen : public QMainWindow {
  Q_OBJECT
    
  public:
  LoginScreen(Netflicks* netflicks) {
    this->netflicks = netflicks;
    
    mainWindow = new QWidget;
    mainGridLayout = new QGridLayout;
    welcomeLabel = new QLabel("Welcome to Netflicks");
    loginLineEdit = new QLineEdit;
    loginFormLayout = new QFormLayout;
    passLineEdit = new QLineEdit;
    passFormLayout = new QFormLayout;
    loginButton = new QPushButton("Login");
    newUserButton = new QPushButton("New User");
    quitButton = new QPushButton("Quit");

    loginFormLayout->addRow("User ID: ", loginLineEdit);
    passFormLayout->addRow("Password: ", passLineEdit);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    
    mainGridLayout->addWidget(welcomeLabel, 1, 1, 1, 3);
    mainGridLayout->addLayout(loginFormLayout, 2, 1, 1, 3);
    mainGridLayout->addLayout(passFormLayout, 3, 1, 1, 3);
    mainGridLayout->addWidget(loginButton, 4, 1, 1, 1);
    mainGridLayout->addWidget(newUserButton, 4, 2, 1, 1);
    mainGridLayout->addWidget(quitButton, 4, 3, 1, 1);

    mainWindow->setLayout(mainGridLayout);
    setCentralWidget(mainWindow);
    setFixedSize(300, 150);

    QObject::connect(loginButton, SIGNAL(clicked()), SLOT(loginButtonClicked()));
    QObject::connect(newUserButton, SIGNAL(clicked()), SLOT(newUserButtonClicked()));
    QObject::connect(quitButton, SIGNAL(clicked()), SLOT(quitButtonClicked()));
    QObject::connect(passLineEdit, SIGNAL(returnPressed()), SLOT(loginButtonClicked()));
  }
  
  ~LoginScreen() {
    delete welcomeLabel;
    delete loginLineEdit;
    delete loginFormLayout;
    delete loginButton;
    delete newUserButton;
    delete quitButton;
    delete mainGridLayout;
    delete mainWindow;
  }
  
 private slots:
  void loginButtonClicked() {
    QString userID = loginLineEdit->text();
    string ID = userID.toStdString();

    QString userPassword = passLineEdit->text();
    string password = userPassword.toStdString();

    if(!(ID == "" or password == "")) {
      if(netflicks->loginUser(ID, password)) {
	MainScreen *ms = new MainScreen(this, netflicks);
	loginLineEdit->setText("");
	passLineEdit->setText("");
	hide();
	ms->show();
      } else {
	QMessageBox errorMessage;
	errorMessage.critical(0, "Error", "Invalid ID or Password.");
	errorMessage.setFixedSize(300, 120);
      }
    } else {
      QMessageBox errorMessage;
      errorMessage.critical(0, "Error", "You did not enter an ID or Password.");
      errorMessage.setFixedSize(300, 120);
    }
  }
  
  void newUserButtonClicked() {
    NewUserScreen *nus = new NewUserScreen(this, netflicks, false);
    loginLineEdit->setText("");
    passLineEdit->setText("");
    hide();
    nus->show();
  }
  
  void quitButtonClicked() {
    close();
  }

 private:
  QWidget *mainWindow;
  QGridLayout *mainGridLayout;
  QLabel *welcomeLabel;
  QLineEdit *loginLineEdit;
  QFormLayout *loginFormLayout;
  QLineEdit *passLineEdit;
  QFormLayout *passFormLayout;
  QPushButton *loginButton;
  QPushButton *newUserButton;
  QPushButton *quitButton;
  Netflicks *netflicks;
};

#endif
