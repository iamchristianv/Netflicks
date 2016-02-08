#ifndef RATINGSCREEN_H
#define RATINGSCREEN_H

#include <QCloseEvent>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <string>
#include "Netflicks.h"

class RatingScreen : public QMainWindow {
 Q_OBJECT

 public:
  RatingScreen(QMainWindow* mainScreen, Netflicks* netflicks, string title, bool rated) {
    this->mainScreen = mainScreen;
    this->netflicks = netflicks;
    this->title = title;

    mainWindow = new QWidget;
    mainGridLayout = new QGridLayout;

    if(rated == true) {
      infoLabel = new QLabel("How would you rate the movie from 1 to 5?");
    } else {
      infoLabel = new QLabel("Would you like to rate the movie again?");
    }

    oneLabel = new QLabel("Really Bad");
    fiveLabel = new QLabel("Really Good");
    
    oneButton = new QPushButton("1");
    twoButton = new QPushButton("2");
    threeButton = new QPushButton("3");
    fourButton = new QPushButton("4");
    fiveButton = new QPushButton("5");

    if(rated == true) {
      notNowButton = new QPushButton("Not Now");
    } else {
      notNowButton = new QPushButton("Not Again");
    }

    infoLabel->setAlignment(Qt::AlignCenter);

    mainGridLayout->addWidget(infoLabel, 1, 1, 1, 5);
    mainGridLayout->addWidget(oneLabel, 2, 1, 1, 1);
    mainGridLayout->addWidget(fiveLabel, 2, 5, 1, 1);
    mainGridLayout->addWidget(oneButton, 3, 1, 1, 1);
    mainGridLayout->addWidget(twoButton, 3, 2, 1, 1);
    mainGridLayout->addWidget(threeButton, 3, 3, 1, 1);
    mainGridLayout->addWidget(fourButton, 3, 4, 1, 1);
    mainGridLayout->addWidget(fiveButton, 3, 5, 1, 1);
    mainGridLayout->addWidget(notNowButton, 4, 3, 1, 1);

    mainWindow->setLayout(mainGridLayout);
    setCentralWidget(mainWindow);

    QObject::connect(oneButton, SIGNAL(clicked()), SLOT(oneButtonClicked()));
    QObject::connect(twoButton, SIGNAL(clicked()), SLOT(twoButtonClicked()));
    QObject::connect(threeButton, SIGNAL(clicked()), SLOT(threeButtonClicked()));
    QObject::connect(fourButton, SIGNAL(clicked()), SLOT(fourButtonClicked()));
    QObject::connect(fiveButton, SIGNAL(clicked()), SLOT(fiveButtonClicked()));
    QObject::connect(notNowButton, SIGNAL(clicked()), SLOT(notNowButtonClicked()));
  }

  ~RatingScreen() {
    delete infoLabel;
    delete oneLabel;
    delete fiveLabel;
    delete oneButton;
    delete twoButton;
    delete threeButton;
    delete fourButton;
    delete fiveButton;
    delete notNowButton;
    delete mainGridLayout;
    delete mainWindow;
  }

  void closeEvent() {
    mainScreen->show();
    close();
  }

 private slots:
  void oneButtonClicked() {
    string rating = "1";
    netflicks->rateMovie(title, rating);

    QMessageBox thanksMessage;
    thanksMessage.information(0, "Thank You", "Thank you for rating the movie!");
    thanksMessage.setFixedSize(300, 120);

    mainScreen->show();
    close();
  }

  void twoButtonClicked() {   
    string rating = "2";
    netflicks->rateMovie(title, rating); 

    QMessageBox thanksMessage;
    thanksMessage.information(0, "Thank You", "Thank you for rating the movie!");
    thanksMessage.setFixedSize(300, 120);

    mainScreen->show();
    close();
  }

  void threeButtonClicked() {
    string rating = "3";
    netflicks->rateMovie(title, rating);

    QMessageBox thanksMessage;
    thanksMessage.information(0, "Thank You", "Thank you for rating the movie!");
    thanksMessage.setFixedSize(300, 120);

    mainScreen->show();
    close();
  }

  void fourButtonClicked() {
    string rating = "4";
    netflicks->rateMovie(title, rating);

    QMessageBox thanksMessage;
    thanksMessage.information(0, "Thank You", "Thank you for rating the movie!");
    thanksMessage.setFixedSize(300, 120);

    mainScreen->show();
    close();
  } 

  void fiveButtonClicked() {
    string rating = "5";
    netflicks->rateMovie(title, rating);

    QMessageBox thanksMessage;
    thanksMessage.information(0, "Thank You", "Thank you for rating the movie!");
    thanksMessage.setFixedSize(300, 120);

    mainScreen->show();
    close();
  }

  void notNowButtonClicked() {
    mainScreen->show();
    close();
  }

 private:
  QWidget *mainWindow;
  QGridLayout *mainGridLayout;

  QLabel *infoLabel;
  QLabel *oneLabel;
  QLabel *fiveLabel;

  QPushButton *oneButton;
  QPushButton *twoButton;
  QPushButton *threeButton;
  QPushButton *fourButton;
  QPushButton *fiveButton;
  QPushButton *notNowButton;

  string title;

  QMainWindow *mainScreen;
  Netflicks *netflicks;
};

#endif
