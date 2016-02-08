#ifndef USER_H
#define USER_H

#include <sstream>
#include "lib/MapH.h"
#include "Movie.h"
#include "md5.h"

class User {
 public:
  User(string ID, string name);
  User(const User &other);
  ~User(); 
  string getID() const;
  string getName() const;
  Queue<Movie*>* movieQueue();
  void rentMovie(Movie* m);
  void returnMovie();
  Movie* currentMovie();
  Map<string, string>* movieRatings();
  void setName(string n);
  void setAddress(string a);
  void setNumber(string n);
  void setCharges(string c);
  void setPassword(string p);
  string getPassword();
  string getCharges();
  string getNumber();
  string getAddress();
 private:
  string ID;
  string name;
  string address;
  string number;
  string charges;
  string password;
  Movie* userMovie;
  Queue<Movie*>* userMovieQueue;
  Map<string, string>* userMovieRatings;
};
 
#endif
