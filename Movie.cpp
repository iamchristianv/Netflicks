#include "Movie.h"
#include <cstdlib>

// constructor 
Movie::Movie(string title) {
  this->title = title;
  this->price = "0";
}

// copy constructor
Movie::Movie(const Movie &other) {
  this->keywordStorage.merge(other.keywordStorage);
}

// destructor
Movie::~Movie() {
  
}

// getTitle()
string Movie::getTitle() const {
  return this->title;
}

// addKeyword(keyword)
void Movie::addKeyword(string keyword) {
  this->keywordStorage.add(keyword);
}

// getAllKeywords() 
Set<string> Movie::getAllKeywords() const {
  Set<string> keywords(this->keywordStorage);
  return keywords;
}

// getPrice()
string Movie::getPrice() {
  return this->price;
}

// setPrice()
void Movie::setPrice(string p) {
  this->price = p;
}
