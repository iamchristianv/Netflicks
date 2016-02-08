#ifndef MOVIESCREEN_H
#define MOVIESCREEN_H

#include <QCloseEvent>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <string>
#include <vector>
#include "Netflicks.h"

class MovieScreen : public QMainWindow {
 Q_OBJECT

 public:
  MovieScreen(QMainWindow* mainScreen, Netflicks* netflicks, QLineEdit* searchLineEdit, bool titleSearch) {
    this->mainScreen = mainScreen;
    this->netflicks = netflicks;
    this->searchLineEdit = searchLineEdit;

    mainWindow = new QWidget;
    mainGridLayout = new QGridLayout;

    string keyword = searchLineEdit->text().toStdString();

    if(titleSearch == true) {
      titles = netflicks->returnTitleSearch(keyword);
    } else {
      titles = netflicks->returnKeywordSearch(keyword);
    }

    movieLabel = new QLabel(QString::fromUtf8(titles.back().c_str()));
    movieInfoLabel = new QLabel("MOVIE INFORMATION");

    QString keywordLabelText = QString::fromUtf8(netflicks->returnKeywordStringForMovie(titles.back()).c_str());
    keywordLabel = new QLabel(keywordLabelText);
    
    nextMovieButton = new QPushButton("Next Movie");
    addMovieButton = new QPushButton("Add Movie to Queue");
    returnMainMenuButton = new QPushButton("Return to Main Menu");

    movieLabel->setAlignment(Qt::AlignCenter);

    mainGridLayout->addWidget(movieLabel, 1, 1, 1, 3);
    mainGridLayout->addWidget(movieInfoLabel, 2, 1, 1, 3);
    mainGridLayout->addWidget(keywordLabel, 3, 1, 1, 3);
    mainGridLayout->addWidget(nextMovieButton, 4, 1, 1, 1);
    mainGridLayout->addWidget(addMovieButton, 4, 2, 1, 1);
    mainGridLayout->addWidget(returnMainMenuButton, 4, 3, 1, 1);

    if(titles.size() <= 1) {
      nextMovieButton->hide();
    }

    if(movieLabel->text() == "No Movie Found") {
      movieInfoLabel->hide();
      keywordLabel->hide();
      addMovieButton->hide();
    }

    mainWindow->setLayout(mainGridLayout);
    setCentralWidget(mainWindow);

    QObject::connect(nextMovieButton, SIGNAL(clicked()), SLOT(nextMovieButtonClicked()));
    QObject::connect(addMovieButton, SIGNAL(clicked()), SLOT(addMovieButtonClicked()));
    QObject::connect(returnMainMenuButton, SIGNAL(clicked()), SLOT(returnMainMenuButtonClicked()));
  }

  ~MovieScreen() {    
    delete movieLabel;
    delete movieInfoLabel;
    delete keywordLabel;
    delete nextMovieButton;
    delete addMovieButton;
    delete returnMainMenuButton;
    delete mainGridLayout;
    delete mainWindow;
  }

  void closeEvent(QCloseEvent *event) {
    mainScreen->show();
    close();
  }

 private slots:
  void nextMovieButtonClicked() {    
    titles.pop_back();
    
    movieLabel->setText(QString::fromUtf8(titles.back().c_str()));
    keywordLabel->setText(QString::fromUtf8(netflicks->returnKeywordStringForMovie(titles.back()).c_str()));
    
    if(titles.size() <= 1) {
      nextMovieButton->hide();
    }
  }

  void addMovieButtonClicked() {
    if(netflicks->addMovieToQueue(titles.back())) {
      QMessageBox confirmationMessage;
      confirmationMessage.information(0, "Confirmation", "You have added the movie to your queue.");
      confirmationMessage.setFixedSize(300, 120);
    } else {
      QMessageBox errorMessage;
      errorMessage.critical(0, "Error", "You cannot add the movie to your queue.");
      errorMessage.setFixedSize(300, 120);
    }
  }

  void returnMainMenuButtonClicked() {
    mainScreen->show();
    close();
  }
  
 private:
  QWidget *mainWindow;
  QGridLayout *mainGridLayout;

  QLabel *movieLabel;
  QLabel *movieInfoLabel;

  vector<string> titles;
  QLabel *keywordLabel;

  QPushButton *nextMovieButton;
  QPushButton *addMovieButton;
  QPushButton *returnMainMenuButton;

  QMainWindow *mainScreen;
  Netflicks *netflicks;
  QLineEdit *searchLineEdit;
};

#endif
