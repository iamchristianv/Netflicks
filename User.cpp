#include "User.h"
#include <cstdlib>

// constructor
User::User(string ID, string name) {
  this->ID = ID; 
  this->name = name;
  this->charges = "0";
  this->userMovie = NULL;
  this->userMovieQueue = new Queue<Movie*>;
  this->userMovieRatings = new Map<string, string>;
}

// copy constructor
User::User(const User &other) {
  this->ID = other.ID;
  this->name = other.name;
  this->userMovie = other.userMovie;
}

// destructor
User::~User() {
  
}
 
// getID()
string User::getID() const {
  return this->ID;
}

// getName()
string User::getName() const {
  return this->name;
}

// movieQueue()
Queue<Movie*>* User::movieQueue() {
  return this->userMovieQueue;
}

// rentMovie()
void User::rentMovie(Movie* m) {
  this->userMovie = m;
}

// returnMovie() 
void User::returnMovie() {
  this->userMovie = NULL;
}

// currentMovie()
Movie* User::currentMovie() {
  if(this->userMovie != NULL) {
    return this->userMovie;
  } else if(this->userMovie == NULL) {
    return NULL;
  }
}

// movieRatings() 
Map<string, string>* User::movieRatings() {
  return this->userMovieRatings;
}

// setName()
void User::setName(string n) {
  this->name = n;
}

// setAddress()
void User::setAddress(string a) {
  this->address = a;
}

// setNumber()
void User::setNumber(string n) {
  this->number = n;
}

// setCharges()
void User::setCharges(string c) {
  double oldCharge = atof(this->charges.c_str());
  double newCharge = atof(c.c_str());

  oldCharge = oldCharge + newCharge;

  stringstream ss;
  ss << oldCharge;
  ss >> this->charges;
}

// setPassword()
void User::setPassword(string p) {
  this->password = p;
}

// getPassword()
string User::getPassword() {
  return this->password;
}

// getCharges()
string User::getCharges() {
  return this->charges;
}

// getNumber()
string User::getNumber() {
  return this->number;
}

// getAddress()
string User::getAddress() {
  return this->address;
}
