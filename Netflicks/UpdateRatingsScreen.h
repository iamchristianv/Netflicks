#ifndef UPDATERATINGSSCREEN_H
#define UPDATERATINGSSCREEN_H

#include <QCloseEvent>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <string>
#include <vector>
#include "Netflicks.h"
#include "RatingScreen.h"

class UpdateRatingsScreen : public QMainWindow {
 Q_OBJECT

 public:
  UpdateRatingsScreen(QMainWindow* mainScreen, Netflicks* netflicks) {
    this->mainScreen = mainScreen;
    this->netflicks = netflicks;
    
    mainWindow = new QWidget;
    mainGridLayout = new QGridLayout;
    
    titles = netflicks->getMovieTitles();
    ratings = netflicks->getMovieRatings();

    titleText = QString::fromUtf8(titles.back().c_str());
    ratingText = QString::fromUtf8(ratings.back().c_str());

    QString infoText;

    if(titles.back() == "No Movies Rated" and ratings.back() == "No Movies Rated") {
      infoText = "You have not rated any movies yet.";	  
    } else {
      infoText = "You rated " + titleText + " a " + ratingText + " out of 5.";
    }

    infoLabel = new QLabel(infoText);

    nextRatingButton = new QPushButton("Next Rating");
    changeRatingButton = new QPushButton("Change this Rating");
    returnMainMenuButton = new QPushButton("Return to Main Menu");

    infoLabel->setAlignment(Qt::AlignCenter);

    mainGridLayout->addWidget(infoLabel, 1, 1, 1, 3);
    mainGridLayout->addWidget(nextRatingButton, 2, 1, 1, 1);
    mainGridLayout->addWidget(changeRatingButton, 2, 2, 1, 1);
    mainGridLayout->addWidget(returnMainMenuButton, 2, 3, 1, 1);

    if(titles.size() <= 1 and ratings.size() <= 1) {
      nextRatingButton->hide();
    }

    if(infoText == "You have not rated any movies yet.") {
      changeRatingButton->hide();
    }

    mainWindow->setLayout(mainGridLayout);
    setCentralWidget(mainWindow);

    QObject::connect(nextRatingButton, SIGNAL(clicked()), SLOT(nextRatingButtonClicked()));
    QObject::connect(changeRatingButton, SIGNAL(clicked()), SLOT(changeRatingButtonClicked()));
    QObject::connect(returnMainMenuButton, SIGNAL(clicked()), SLOT(returnMainMenuButtonClicked()));
  }

  ~UpdateRatingsScreen() {

  }

  void closeEvent(QCloseEvent *event) {
    mainScreen->show();
    close();
  }

 private slots:
  void nextRatingButtonClicked() {
    titles.pop_back();
    ratings.pop_back();

    titleText = QString::fromUtf8(titles.back().c_str());
    ratingText = QString::fromUtf8(ratings.back().c_str());
    QString infoText = "You rated " + titleText + " a " + ratingText + " out of 5.";

    infoLabel->setText(infoText);

    if(titles.size() <= 1) {
      nextRatingButton->hide();
    }
  }

  void changeRatingButtonClicked() {
    string title = titleText.toStdString();
    
    RatingScreen *rs = new RatingScreen(this, netflicks, title, true);
    hide();
    rs->show();
  }

  void returnMainMenuButtonClicked() {
    mainScreen->show();
    close();
  }
  
 private:
  QWidget *mainWindow;
  QGridLayout *mainGridLayout;

  vector<string> titles;
  vector<string> ratings;

  QString titleText;
  QString ratingText;
  QLabel *infoLabel;

  QPushButton *nextRatingButton;
  QPushButton *changeRatingButton;
  QPushButton *returnMainMenuButton;

  QMainWindow *mainScreen;
  Netflicks *netflicks;
};

#endif
