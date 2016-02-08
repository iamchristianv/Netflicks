#ifndef MOVIE_H
#define MOVIE_H

#include "lib/SetH.h"
 
class Movie {
 public:
  Movie(string title);
  Movie(const Movie &other);
  ~Movie();
  string getTitle() const;
  void addKeyword(string keyword);
  Set<string> getAllKeywords() const;
  string getPrice();
  void setPrice(string p);
 private:
  string title;
  string price;
  Set<string> keywordStorage;
};

#endif
