#ifndef MAINSCREEN_H
#define MAINSCREEN_H

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
#include <QVBoxLayout>
#include <string>
#include "Netflicks.h"
#include "MovieScreen.h"
#include "RatingScreen.h"
#include "NewUserScreen.h"
#include "UpdateRatingsScreen.h"

class MainScreen : public QMainWindow {
  Q_OBJECT

 public:
  MainScreen(QMainWindow* loginScreen, Netflicks* netflicks) {
    this->loginScreen = loginScreen;
    this->netflicks = netflicks;

    mainWindow = new QWidget;
    mainVBoxLayout = new QVBoxLayout;
    QString welcomeLabelText = "WELCOME TO NETFLICKS, " + QString::fromUtf8(netflicks->returnUserName().c_str()) + " (" + QString::fromUtf8(netflicks->returnUserID().c_str()) + ")";
    welcomeLabel = new QLabel(welcomeLabelText);
    blankLabel = new QLabel("");
    currentMovieGridLayout = new QGridLayout;
    currentMovieLabel = new QLabel("YOUR CURRENT MOVIE");
    QString movieLabelText = QString::fromUtf8(netflicks->returnCheckedOutMovieTitle().c_str());
    movieLabel = new QLabel(movieLabelText);
    returnMovieButton = new QPushButton("Return Movie");
    movieQueueGridLayout = new QGridLayout;
    movieQueueLabel = new QLabel("YOUR MOVIE QUEUE");
    Movie* movie = netflicks->returnNextMovieInQueue();
    string moviePrice;
    if(movie == NULL) {
      moviePrice = "0";
    } else {
      moviePrice = movie->getPrice();
    }
    QString frontMovieLabelText = "Next: " + QString::fromUtf8(netflicks->returnNextMovieInQueueTitle().c_str()) + ",  Price: $" + QString::fromUtf8(moviePrice.c_str());
    frontMovieLabel = new QLabel(frontMovieLabelText);
    rentMovieButton = new QPushButton("Rent Movie");
    removeMovieButton = new QPushButton("Remove Movie");
    moveMovieButton = new QPushButton("Move Movie To Back");
    searchGridLayout = new QGridLayout;
    searchMovieLabel = new QLabel("SEARCH FOR A MOVIE");
    searchLineEdit = new QLineEdit;
    searchFormLayout = new QFormLayout;
    searchTitleButton = new QPushButton("Search by Title");
    searchKeywordButton = new QPushButton("Search by Keyword");
    searchActorButton = new QPushButton("Search by Actor");
    logoutButton = new QPushButton("Logout");
    refreshButton = new QPushButton("Refresh");
    viewRatingsButton = new QPushButton("View Ratings");
    actionGridLayout = new QGridLayout;
    accountButton = new QPushButton("Update Account");

    searchFormLayout->addRow("Search: ", searchLineEdit);
    welcomeLabel->setAlignment(Qt::AlignCenter);

    currentMovieGridLayout->addWidget(currentMovieLabel, 1, 1, 1, 1);
    currentMovieGridLayout->addWidget(movieLabel, 2, 1, 1, 1);
    currentMovieGridLayout->addWidget(returnMovieButton, 3, 1, 1, 1);

    movieQueueGridLayout->addWidget(movieQueueLabel, 1, 1, 1, 3);
    movieQueueGridLayout->addWidget(frontMovieLabel, 2, 1, 1, 2);
    movieQueueGridLayout->addWidget(rentMovieButton, 3, 1, 1, 1);
    movieQueueGridLayout->addWidget(removeMovieButton, 3, 2, 1, 1);
    movieQueueGridLayout->addWidget(moveMovieButton, 3, 3, 1, 1);

    searchGridLayout->addWidget(searchMovieLabel, 1, 1, 1, 3);
    searchGridLayout->addLayout(searchFormLayout, 2, 1, 1, 3);
    searchGridLayout->addWidget(searchTitleButton, 3, 1, 1, 1);
    searchGridLayout->addWidget(searchKeywordButton, 3, 2, 1, 1);
    searchGridLayout->addWidget(searchActorButton, 3, 3, 1, 1);

    actionGridLayout->addWidget(refreshButton, 1, 1, 1, 1);
    actionGridLayout->addWidget(viewRatingsButton, 1, 2, 1, 1);
    actionGridLayout->addWidget(accountButton, 1, 3, 1, 1);

    mainVBoxLayout->addWidget(welcomeLabel);
    mainVBoxLayout->addWidget(blankLabel);
    mainVBoxLayout->addLayout(currentMovieGridLayout);
    mainVBoxLayout->addWidget(blankLabel);
    mainVBoxLayout->addLayout(movieQueueGridLayout);
    mainVBoxLayout->addWidget(blankLabel);
    mainVBoxLayout->addLayout(searchGridLayout);
    mainVBoxLayout->addWidget(blankLabel);
    mainVBoxLayout->addLayout(actionGridLayout);
    mainVBoxLayout->addWidget(blankLabel);
    mainVBoxLayout->addWidget(logoutButton);

    mainWindow->setLayout(mainVBoxLayout);
    setCentralWidget(mainWindow);
    
    QObject::connect(returnMovieButton, SIGNAL(clicked()), SLOT(returnMovieButtonClicked()));
    QObject::connect(rentMovieButton, SIGNAL(clicked()), SLOT(rentMovieButtonClicked()));
    QObject::connect(removeMovieButton, SIGNAL(clicked()), SLOT(removeMovieButtonClicked()));
    QObject::connect(moveMovieButton, SIGNAL(clicked()), SLOT(moveMovieButtonClicked()));
    QObject::connect(searchTitleButton, SIGNAL(clicked()), SLOT(searchTitleButtonClicked()));
    QObject::connect(searchKeywordButton, SIGNAL(clicked()), SLOT(searchKeywordButtonClicked()));
    QObject::connect(searchActorButton, SIGNAL(clicked()), SLOT(searchKeywordButtonClicked()));
    QObject::connect(logoutButton, SIGNAL(clicked()), SLOT(logoutButtonClicked()));
    QObject::connect(refreshButton, SIGNAL(clicked()), SLOT(refreshButtonClicked()));
    QObject::connect(searchLineEdit, SIGNAL(returnPressed()), SLOT(searchTitleButtonClicked()));
    QObject::connect(accountButton, SIGNAL(clicked()), SLOT(accountButtonClicked()));
    QObject::connect(viewRatingsButton, SIGNAL(clicked()), SLOT(viewRatingsButtonClicked()));
  }

  ~MainScreen() {
    delete currentMovieLabel;
    delete movieLabel;
    delete returnMovieButton;
    delete currentMovieGridLayout;
    delete movieQueueLabel;
    delete frontMovieLabel;
    delete rentMovieButton;
    delete removeMovieButton;
    delete moveMovieButton;
    delete movieQueueGridLayout;
    delete searchMovieLabel;
    delete searchLineEdit;
    delete searchFormLayout;
    delete searchTitleButton;
    delete searchKeywordButton;
    delete searchGridLayout;
    delete logoutButton;
    delete refreshButton;
    delete blankLabel;
    delete welcomeLabel;
    delete mainVBoxLayout;
    delete mainWindow;	    
  }

  void closeEvent(QCloseEvent *event) {
    netflicks->writeDataToUserFile();
    loginScreen->show();
    close();
  }

 private slots:
  void returnMovieButtonClicked() {
    string title = netflicks->returnCheckedOutMovieTitle();

    if(netflicks->userReturnMovie()) {
      QString movieLabelText = QString::fromUtf8(netflicks->returnCheckedOutMovieTitle().c_str());
      movieLabel->setText(movieLabelText);

      if(!(netflicks->movieHasBeenRated(title))) {
	RatingScreen *rs = new RatingScreen(this, netflicks, title, true);
	hide();
	rs->show();
      } else {
	RatingScreen *rs = new RatingScreen(this, netflicks, title, false);
	hide();
	rs->show();
      }
    } else {
      QMessageBox errorMessage;
      errorMessage.critical(0, "Error", "You do not have a movie to return.");
      errorMessage.setFixedSize(300, 120);
    }
  }

  void rentMovieButtonClicked() {
    Movie* rentedMovie = netflicks->returnNextMovieInQueue();

    if(netflicks->orderMovieFromQueue()) {
      QString movieLabelText = QString::fromUtf8(netflicks->returnCheckedOutMovieTitle().c_str());
      movieLabel->setText(movieLabelText);
      Movie* newMovie = netflicks->returnNextMovieInQueue();

      string newPrice;

      if(newMovie == NULL) {
	newPrice = "0";
      } else {
	newPrice = newMovie->getPrice();
      }

      QString newPriceText = QString::fromUtf8(newPrice.c_str());
      
      QString frontMovieLabelText = "Next: " + QString::fromUtf8(netflicks->returnNextMovieInQueueTitle().c_str()) + ",  Price: $" + newPriceText;
      frontMovieLabel->setText(frontMovieLabelText);

      string price = rentedMovie->getPrice();
      QString priceText = QString::fromUtf8(price.c_str());

      netflicks->setUserCharges(price);

      QString balanceText = QString::fromUtf8(netflicks->getUserCharges().c_str());

      QMessageBox chargesMessage;
      chargesMessage.information(0, "Balance Update", "You have been charged $" + priceText + " for renting this movie.\nCurrent Balance: $" + balanceText);
      chargesMessage.setFixedSize(400, 120);
    } else {
      QMessageBox errorMessage;
      errorMessage.critical(0, "Error", "You cannot rent a movie because your queue is empty or you already rented a movie.");
      errorMessage.setFixedSize(300, 120);
    }
  }

  void removeMovieButtonClicked() {
    if(netflicks->removeMovieFromQueue()) {
      QString movieLabelText = QString::fromUtf8(netflicks->returnCheckedOutMovieTitle().c_str());
      movieLabel->setText(movieLabelText);
      Movie* movie = netflicks->returnNextMovieInQueue();

      string price;

      if(movie == NULL) {
	price = "0";
      } else {
	price = movie->getPrice();
      }

      QString priceText = QString::fromUtf8(price.c_str());
      
      QString frontMovieLabelText = "Next: " + QString::fromUtf8(netflicks->returnNextMovieInQueueTitle().c_str()) + ",  Price: $" + priceText;
      frontMovieLabel->setText(frontMovieLabelText);
    } else {
      QMessageBox errorMessage;
      errorMessage.critical(0, "Error", "You do not have a movie in your queue to remove.");
      errorMessage.setFixedSize(300, 120);
    }
  }

  void moveMovieButtonClicked() {
    if(netflicks->moveMovieToBackQueue()) {
      QString movieLabelText = QString::fromUtf8(netflicks->returnCheckedOutMovieTitle().c_str());
      movieLabel->setText(movieLabelText);
      Movie* movie = netflicks->returnNextMovieInQueue(); 

      string price;

      if(movie == NULL) {
	price = "0";
      } else {
	price = movie->getPrice();
      }

      QString priceText = QString::fromUtf8(price.c_str());
      
      QString frontMovieLabelText = "Next: " + QString::fromUtf8(netflicks->returnNextMovieInQueueTitle().c_str()) + ",  Price: $" + priceText;
      frontMovieLabel->setText(frontMovieLabelText);
    } else {
      QMessageBox errorMessage;
      errorMessage.critical(0, "Error", "You do not have a movie in your queue to move to the back.");
      errorMessage.setFixedSize(300, 120);
    }
  }

  void searchTitleButtonClicked() {
    MovieScreen *ms = new MovieScreen(this, netflicks, searchLineEdit, true);
    hide();
    ms->show();
  }

  void searchKeywordButtonClicked() {
    MovieScreen *ms = new MovieScreen(this, netflicks, searchLineEdit, false);
    hide();
    ms->show();
  }

  void logoutButtonClicked() {
    netflicks->writeDataToUserFile();
    loginScreen->show();
    close();
  }

  void refreshButtonClicked() {
    Movie* movie = netflicks->returnNextMovieInQueue();

    QString movieLabelText = QString::fromUtf8(netflicks->returnCheckedOutMovieTitle().c_str());
    movieLabel->setText(movieLabelText);

    string price;

    if(movie == NULL) {
      price = "0";
    } else {
      price = movie->getPrice();
    }

    QString priceText = QString::fromUtf8(price.c_str());

    QString frontMovieLabelText = "Next: " + QString::fromUtf8(netflicks->returnNextMovieInQueueTitle().c_str()) + ",  Price: $" + priceText;
    frontMovieLabel->setText(frontMovieLabelText);
  }

  void accountButtonClicked() {
    NewUserScreen *nus = new NewUserScreen(this, netflicks, true);
    hide();
    nus->show();
  }

  void viewRatingsButtonClicked() {
    UpdateRatingsScreen *urs = new UpdateRatingsScreen(this, netflicks);
    hide();
    urs->show();
  }
  
 private:
  QWidget *mainWindow;
  QVBoxLayout *mainVBoxLayout;
  QLabel *welcomeLabel;
  QLabel *blankLabel;

  QGridLayout *currentMovieGridLayout;
  QLabel *currentMovieLabel;
  QLabel *movieLabel;
  QPushButton *returnMovieButton;

  QGridLayout *movieQueueGridLayout;
  QLabel *movieQueueLabel;
  QLabel *frontMovieLabel;
  QPushButton *rentMovieButton;
  QPushButton *removeMovieButton;
  QPushButton *moveMovieButton;

  QGridLayout *searchGridLayout;
  QLabel *searchMovieLabel;
  QLineEdit *searchLineEdit;
  QFormLayout *searchFormLayout;
  QPushButton *searchTitleButton;
  QPushButton *searchKeywordButton;
  QPushButton *searchActorButton;

  QGridLayout *actionGridLayout;
  QPushButton *refreshButton;
  QPushButton *viewRatingsButton;
  QPushButton *accountButton;

  QPushButton *logoutButton;

  QMainWindow *loginScreen;
  Netflicks *netflicks;
};

#endif
