#ifndef NETFLICKS_H
#define NETFLICKS_H

#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;
#include "../lib/SetH.h"
#include "../User.h"
#include "../Movie.h"
#include "md5.h"

class Netflicks {
 public:
  Netflicks(int argc, char** argv);

  ~Netflicks();

  // readMainDataFile()
  void readMainDataFile();

  // readUserDataFile()
  void readUserDataFile();

  // readMovieDataFile()
  void readMovieDataFile();

  // loginUser()
  bool loginUser(string userID, string userPassword);

  // createNewUser()
  bool createNewUser(string ID, string name, string address, string number, string password);

  // returnCheckedOutMovie()
  Movie* returnCheckedOutMovie();

  // returnCheckedOutMovieTitle()
  string returnCheckedOutMovieTitle();

  // returnNextMovieInQueue()
  Movie* returnNextMovieInQueue();

  // returnNextMovieInQueueTitle()
  string returnNextMovieInQueueTitle();

  // returnKeywordsForMovie()
  Set<string> returnKeywordsForMovie(string movieTitle); 

  // returnKeywordStringForMovie()
  string returnKeywordStringForMovie(string movieTitle);

  // searchByTitle()
  Movie* searchByTitle(string movieTitle);

  // returnTitleSearch()
  vector<string> returnTitleSearch(string movieTitle);

  // searchByKeyword()
  Set<Movie*> searchByKeyword(string keyword);

  // returnKeywordSearch()
  vector<string> returnKeywordSearch(string movieTitle);

  // orderMovieFromQueue()
  bool orderMovieFromQueue();

  // removeMovieFromQueue()
  bool removeMovieFromQueue();

  // moveMovieToBackQueue()
  bool moveMovieToBackQueue();

  // addMovieToQueue()
  bool addMovieToQueue(string movieTitle);

  // writeDataToUserFile
  void writeDataToUserFile();

  // returnContents()
  string returnContents(string line);

  // returnLowercase()
  string returnLowercase(string line);

  // userReturnMovie()
  bool userReturnMovie();

  // returnUserID()
  string returnUserID();

  // returnUserName()
  string returnUserName();

  // movieHasBeenRated()
  bool movieHasBeenRated(string movieTitle);

  // rateMovie()
  void rateMovie(string movieTitle, string rating);

  // setUserName()
  void setUserName(string n);

  // setUserAddress()
  void setUserAddress(string a);

  // setUserNumber()
  void setUserNumber(string n);
  
  // setUserPassword()
  void setUserPassword(string p);

  // setUserCharges()
  void setUserCharges(string c);

  // getUserCharges()
  string getUserCharges();

  // getMovieTitles()
  vector<string> getMovieTitles();

  // getMovieRatings() 
  vector<string> getMovieRatings();
  
 private:
  Map<string, User*> userData;
  Map<string, Movie*> movieData;
  Map<string, Set<Movie*>* > keywordData;
  string mainDataFile;
  string userDataFile;
  string movieDataFile;
  User* currentUser;
};

#endif
