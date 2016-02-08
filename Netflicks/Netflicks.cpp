#include "Netflicks.h"

// Netflicks()
Netflicks::Netflicks(int argc, char** argv) {
  mainDataFile = argv[1];
  readMainDataFile();
  readUserDataFile();
  readMovieDataFile();
}

// ~Netflicks()
Netflicks::~Netflicks() {
  if(userData.size() != 0) {
    for(Map<string, User*>::Iterator mi = userData.begin(); mi != userData.end(); mi++) {
      Pair<string, User*> pair = *mi;
      User* user = pair.second;
      Queue<Movie*>* userQueue = user->movieQueue();
      
      while(!userQueue->isEmpty()) {
	Movie* movie = userQueue->peekFront();
	userQueue->dequeue();
	
	if(movie != NULL) {
	  delete movie;
	}
      }
      
      Movie* movie = user->currentMovie();
      
      if(movie != NULL) {
	delete movie;
      }
      
      if(userQueue != NULL) {
	delete userQueue;
      }
      
      if(user != NULL) {
	delete user; 
      }
    }
  }

  if(movieData.size() != 0) {
    for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
      Pair<string, Movie*> pair = *mi;
      Movie* movie = pair.second;
      if(movie != NULL) {
	delete movie;
      }
    }
  }

  if(keywordData.size() != 0) {
    for(Map<string, Set<Movie*>* >::Iterator mi = keywordData.begin(); mi != keywordData.end(); mi++) {
      Pair<string, Set<Movie*>* > pair = *mi;
      Set<Movie*>* set = pair.second;
      if(set != NULL) {
      delete set;
      }
    }
  }
}

// readMainDataFile()
void Netflicks::readMainDataFile() {
  ifstream file;
  file.open(mainDataFile.c_str());
  string line;

  while(getline(file, line)) {
    if(userDataFile == "") {
      userDataFile = line;
    } else {
      movieDataFile = line;
    }
  }

  file.close();
}

// readUserDataFile()
void Netflicks::readUserDataFile() {
  ifstream file;
  file.open(userDataFile.c_str());
  string line;
  string userID;
  string userName;
  string argument;
  User* user;
  Movie* movie;
  Queue<Movie*>* queue;
  bool queueStarted = false;
  bool ratingsStarted = false;
  Map<string, string>* map;

  while(getline(file, line)) {
    stringstream ss(line);

    if(line == "BEGIN QUEUE") {
      queueStarted = true;
    } else if(line == "END QUEUE") {
      queueStarted = false;
    } else if(line == "BEGIN RATINGS") {
      ratingsStarted = true;
    } else if(line == "END RATINGS") {
      ratingsStarted = false;
    } else if(queueStarted == true) {
      movie = new Movie(line);
      queue->enqueue(movie);
    } else if(ratingsStarted == true) {
      string rating;
      ss >> rating;
      string title;
      title = returnContents(line);
      
      map->add(title, rating);
    } else {
      ss >> argument;

      if(argument == "BEGIN") {
	userID = returnContents(line);
      } else if(argument == "NAME:") {
	userName = returnContents(line);
	user = new User(userID, userName);
	queue = user->movieQueue();
	map = user->movieRatings();
	userData.add(returnLowercase(userID), user);
      } else if(argument == "MOVIE:") {
	movie = new Movie(returnContents(line));
	user->rentMovie(movie);
      } else if(argument == "ADDRESS:") {
	string address = returnContents(line);
	user->setAddress(address);
      } else if(argument == "NUMBER:") {
	string number = returnContents(line);
	user->setNumber(number);
      } else if(argument == "CHARGES:") {
	string charges = returnContents(line);
	user->setCharges(charges);
      } else if(argument == "PASSWORD:") {
	string password = returnContents(line);
	user->setPassword(password);
      }
    }
  }

  file.close();
}

// readMovieDataFile()
void Netflicks::readMovieDataFile() {
  ifstream file;
  file.open(movieDataFile.c_str()); 
  string line;
  string movieTitle;
  string movieKeyword;
  string command;
  string data;
  Movie *m;
  Set<Movie*> *s;
  
  while(getline(file, line)) {
    stringstream ss(line);
    ss >> command;

    if(command == "BEGIN") {
      movieTitle = returnContents(line);
      m = new Movie(movieTitle);
    } else if(command == "KEYWORD:") {
      movieKeyword = returnContents(line);
      m->addKeyword(movieKeyword);
      data = returnLowercase(movieKeyword);
      
      if(keywordData.contains(data)) { 
	for(Map<string, Set<Movie*>* >::Iterator mi = keywordData.begin(); mi != keywordData.end(); mi++) {
	  Pair<string, Set<Movie*>* > item = *mi;

	  if(item.first == data) {
	    Set<Movie*> *tempMovieSet = item.second;
	    tempMovieSet->add(m);
	    break;
	  }
	}
      } else if(!keywordData.contains(data)) {
	s = new Set<Movie*>;
	s->add(m); 
	keywordData.add(data, s);
      }
    } else if(command == "PRICE:") {
      string price = returnContents(line);
      m->setPrice(price);
    } else if(command == "END") {
      movieData.add(returnLowercase(movieTitle), m);
    }
  }
  
  file.close();
}

// loginUser()
bool Netflicks::loginUser(string userID, string userPassword) {
  // checks user ID for white spaces
  for(string::size_type i = 0; i < userID.length(); i++) {
    if(userID[i] == ' ') { 
      return false;
    }
  }

  // checks if user ID exists
  if(userData.contains(returnLowercase(userID))) {
    currentUser = userData.get(returnLowercase(userID));

    string hashOne = md5(userPassword);
    string hashTwo = currentUser->getPassword();
    
    if(hashOne == hashTwo) {
      return true;
    }

    return false;
  } else if(!userData.contains(returnLowercase(userID))) {
    return false;
  }
}

// createNewUser() 
bool Netflicks::createNewUser(string ID, string name, string address, string number, string password) {
  // checks user ID for white spaces
  for(string::size_type i = 0; i < ID.length(); i++) {
    if(ID[i] == ' ') {
      return false;
    }
  }
  
  if(!userData.contains(returnLowercase(ID))) {   
    User* user = new User(ID, name);
    userData.add(returnLowercase(ID), user);
    user->setAddress(address);
    user->setNumber(number);
    user->setPassword(md5(password));
    
    ofstream file;
    file.open(userDataFile.c_str(), ios::app); 
    file << "BEGIN " << user->getID() << "\n";
    file << "NAME: " << user->getName() << "\n";
    file << "ADDRESS: " << user->getAddress() << "\n";
    file << "NUMBER: " << user->getNumber() << "\n";
    file << "CHARGES: " << user->getCharges() << "\n";
    file << "PASSWORD: " << user->getPassword() << "\n";
    file << "BEGIN QUEUE\n";
    file << "END QUEUE\n";
    file << "BEGIN RATINGS\n";
    file << "END RATINGS\n";
    file << "END\n";
    file.close();
    
    return true;
  } else if(userData.contains(returnLowercase(ID))) {
    return false;
  }
}

// returnCheckedOutMovie()
Movie* Netflicks::returnCheckedOutMovie() {
  Movie* checkedOutMovie = currentUser->currentMovie();

  if(checkedOutMovie != NULL) {
    return checkedOutMovie;
  } else {
    return NULL;
  }
}

// returnCheckedOutMovieTitle()
string Netflicks::returnCheckedOutMovieTitle() {
  Movie* checkedOutMovie = currentUser->currentMovie();
  string movieTitle;

  if(checkedOutMovie != NULL) {
    movieTitle = checkedOutMovie->getTitle();
    return movieTitle;
  } else {
    movieTitle = "No Movie Rented";
    return movieTitle;
  }
}

// returnNextMovieInQueue()
Movie* Netflicks::returnNextMovieInQueue() {
  Queue<Movie*>* userQueue = currentUser->movieQueue();

  if(!userQueue->isEmpty()) {
    Movie* nextMovie = userQueue->peekFront();
    return nextMovie;
  } else {
    return NULL;
  }
}

// returnNextMovieInQueueTitle()
string Netflicks::returnNextMovieInQueueTitle() {
  Queue<Movie*>* userQueue = currentUser->movieQueue();
  string movieTitle;

  if(!userQueue->isEmpty()) {
    Movie* nextMovie = userQueue->peekFront();
    movieTitle = nextMovie->getTitle();
    return movieTitle;
  } else {
    movieTitle = "No Movie In Queue";
    return movieTitle;
  }
}

// returnKeywordsForMovie()
Set<string> Netflicks::returnKeywordsForMovie(string movieTitle) {
  if(movieData.contains(returnLowercase(movieTitle))) {
    for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
      Pair<string, Movie*> pair = *mi;
      
      if(pair.first == returnLowercase(movieTitle)) {
	Movie* movie = pair.second;
	Set<string> keywords = movie->getAllKeywords();
	return keywords;
      }
    }
  } else {
    Set<string> keywords;
    return keywords;
  }
}

// returnKeywordStringForMovie()
string Netflicks::returnKeywordStringForMovie(string movieTitle) {
  Set<string> keywordSet = returnKeywordsForMovie(movieTitle);
  string keywords;

  if(keywordSet.size() != 0) {
    for(Set<string>::Iterator si = keywordSet.begin(); si != keywordSet.end(); si++) {
      string keyword = *si;
      keywords += keyword + "\n";
    }

    return keywords;
  } else {
    keywords = "No Keywords";
    return keywords;
  }
}

// searchByTitle()
Movie* Netflicks::searchByTitle(string movieTitle) {
  if(movieData.contains(returnLowercase(movieTitle))) {
    for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
      Pair<string, Movie*> pair = *mi;

      if(pair.first == returnLowercase(movieTitle)) {
	Movie* movie = pair.second;
	return movie;
      }
    }
  } else {
    return NULL;
  }
}

// returnTitleSearch() 
vector<string> Netflicks::returnTitleSearch(string movieTitle) {
  Movie* movie = searchByTitle(movieTitle);
  vector<string> title;

  if(movie != NULL) {
    title.push_back(movie->getTitle());
    return title;
  } else {
    title.push_back("No Movie Found");
    return title;
  }
}

// searchByKeyword()
Set<Movie*> Netflicks::searchByKeyword(string keyword) {
  if(keywordData.contains(returnLowercase(keyword))) {
    for(Map<string, Set<Movie*>* >::Iterator mi = keywordData.begin(); mi != keywordData.end(); mi++) {
      Pair<string, Set<Movie*>* > pair = *mi;

      if(pair.first == returnLowercase(keyword)) {
	Set<Movie*>* movieSet = pair.second;
	Set<Movie*> movies = *movieSet;
	return movies;
      }
    }
  } else if(movieData.contains(returnLowercase(keyword))) {
    for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
      Pair<string, Movie*> pair = *mi;

      if(pair.first == returnLowercase(keyword)) {
	Movie* movie = pair.second;
	Set<Movie*> movies;
	movies.add(movie);
	return movies;
      }
    }
  } else {
    Set<Movie*> movies;
    return movies;
  }
}

// returnKeywordSearch()
vector<string> Netflicks::returnKeywordSearch(string movieTitle) {
  Set<Movie*> movieSet = searchByKeyword(movieTitle);
  vector<string> keywords;

  if(movieSet.size() != 0) {
    for(Set<Movie*>::Iterator si = movieSet.begin(); si != movieSet.end(); si++) {
      Movie* movie = *si;
      keywords.push_back(movie->getTitle());
    }

    return keywords;
  } else {
    keywords.push_back("No Movie Found");
    return keywords;
  }
}

// orderMovieFromQueue()
bool Netflicks::orderMovieFromQueue() {
  Queue<Movie*>* userQueue = currentUser->movieQueue();

  if(userQueue->isEmpty()) {
    return false;
  } else if(currentUser->currentMovie() != NULL) {
    return false;
  } else {
    Movie* movie = userQueue->peekFront();
    userQueue->dequeue();
    currentUser->rentMovie(movie);
    return true;
  }
}

// removeMovieFromQueue()
bool Netflicks::removeMovieFromQueue() {
  Queue<Movie*>* userQueue = currentUser->movieQueue();

  if(!userQueue->isEmpty()) {
    userQueue->dequeue();
    return true;
  } else {
    return false;
  }
}

// moveMovieToBackQueue()
bool Netflicks::moveMovieToBackQueue() {
  Queue<Movie*>* userQueue = currentUser->movieQueue();

  if(!userQueue->isEmpty()) {
    Movie* movie = userQueue->peekFront();
    userQueue->dequeue();
    userQueue->enqueue(movie);
    return true;
  } else {
    return false;
  }
}

// addMovieToQueue()
bool Netflicks::addMovieToQueue(string movieTitle) {
  Queue<Movie*>* userQueue = currentUser->movieQueue();

  if(movieData.contains(returnLowercase(movieTitle))) {
    for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
      Pair<string, Movie*> pair = *mi;

      if(pair.first == returnLowercase(movieTitle)) {
	Movie* movie = pair.second;
	userQueue->enqueue(movie);
	return true;
      }
    }
  } else {
    return false;
  }
}

// writeDataToUserFile()
void Netflicks::writeDataToUserFile() {
  ofstream file;
  file.open(userDataFile.c_str()); 
  Queue<Movie*>* tempQueue = new Queue<Movie*>;
  
  for(Map<string, User*>::Iterator mi = userData.begin(); mi != userData.end(); mi++) {
    Pair<string, User*> pair = *mi;
    User* user = pair.second;
    Queue<Movie*>* userQueue = user->movieQueue();
    Map<string, string>* userRatings = user->movieRatings();

    file << "BEGIN " << user->getID() << "\n";
    file << "NAME: " << user->getName() << "\n";
    
    if(user->currentMovie() != NULL) {
      Movie* userMovie = user->currentMovie();
      file << "MOVIE: " << userMovie->getTitle() << "\n";
    }

    file << "ADDRESS: " << user->getAddress() << "\n";
    file << "NUMBER: " << user->getNumber() << "\n";
    file << "CHARGES: " << user->getCharges() << "\n";
    file << "PASSWORD: " << user->getPassword() << "\n";

    file << "BEGIN QUEUE\n";
    
    if(!userQueue->isEmpty()) {
      while(!userQueue->isEmpty()) {
	Movie* userMovie = userQueue->peekFront();
	file << userMovie->getTitle() << "\n";
	tempQueue->enqueue(userMovie);
	userQueue->dequeue();
      }

      while(!tempQueue->isEmpty()) {
	Movie* tempMovie = tempQueue->peekFront();
	userQueue->enqueue(tempMovie);
	tempQueue->dequeue();
      }
    }

    file << "END QUEUE\n";

    file << "BEGIN RATINGS\n";

    if(userRatings->size() != 0) {
      for(Map<string, string>::Iterator mi = userRatings->begin(); mi != userRatings->end(); mi++) {
	Pair<string, string> pair = *mi;
	string userRatedMovie = pair.first;
	string userRating = pair.second;
	file << userRating << " " << userRatedMovie << "\n";
      }
    }

    file << "END RATINGS\n";

    file << "END\n";
  }
  
  file.close();
}

// returnContents()
string Netflicks::returnContents(string line) {
  string contents;
  
  for(string::size_type i = 0; i < line.length(); i++) { 
    if(line[i] == ' ' and line[i + 1] != ' ') {
      contents = line.substr((i + 1), (line.length() - i));
      break;
    }
  }
  
  return contents;
}

// returnLowercase()
string Netflicks::returnLowercase(string line) {
  string lowercase;

  for(string::size_type i = 0; i < line.length(); i++) {
    if(isalpha(line[i])) {
      lowercase += tolower(line[i]);
    } else if(isdigit(line[i])) {
      lowercase += line[i];
    } else if(line[i] == ' ') {
      lowercase += ' ';
    }
  }

  return lowercase;
}

// userReturnMovie()
bool Netflicks::userReturnMovie() {
  Movie* checkedOutMovie = returnCheckedOutMovie();
  
  if(checkedOutMovie != NULL) {
    currentUser->returnMovie();
    return true;
  } else {
    return false;
  }
}

// returnUserID()
string Netflicks::returnUserID() {
  return currentUser->getID();
}

// returnUserName() 
string Netflicks::returnUserName() {
  return currentUser->getName();
}

// movieHasBeenRated()
bool Netflicks::movieHasBeenRated(string movieTitle) {
  string title = movieTitle;

  if(movieData.contains(returnLowercase(title))) {
    Map<string, string>* userRatings = currentUser->movieRatings();
    
    if(userRatings->contains(title)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// rateMovie()
void Netflicks::rateMovie(string movieTitle, string rating) {
  string title = movieTitle;

  if(movieData.contains(returnLowercase(title))) {
    Map<string, string>* userRatings = currentUser->movieRatings();
    
    if(userRatings->contains(title)) {
      userRatings->remove(title);
      userRatings->add(title, rating);
    } else {
      userRatings->add(title, rating);
    }
  }
}

// setUserName()
void Netflicks::setUserName(string n) {
  currentUser->setName(n);
}

// setUserAddress()
void Netflicks::setUserAddress(string a) {
  currentUser->setAddress(a);
}

// setUserNumber()
void Netflicks::setUserNumber(string n) {
  currentUser->setNumber(n);
}

// setUserPassword()
void Netflicks::setUserPassword(string p) {
  currentUser->setPassword(md5(p));
}

// setUserCharges()
void Netflicks::setUserCharges(string c) {
  currentUser->setCharges(c);
}

// getUserCharges()
string Netflicks::getUserCharges() {
  return currentUser->getCharges();
}

// getMovieTitles()
vector<string> Netflicks::getMovieTitles() {
  Map<string, string>* userMap = currentUser->movieRatings();
  vector<string> titles;

  if(userMap->size() != 0) {
    for(Map<string, string>::Iterator mi = userMap->begin(); mi != userMap->end(); mi++) {
      Pair<string, string> pair = *mi;
      titles.push_back(pair.first);
    }

    return titles;
  } else {
    titles.push_back("No Movies Rated");
    return titles;
  }
}

// getMovieRatings()
vector<string> Netflicks::getMovieRatings() {
  Map<string, string>* userMap = currentUser->movieRatings();
  vector<string> ratings;
  
  if(userMap->size() != 0) {
    for(Map<string, string>::Iterator mi = userMap->begin(); mi != userMap->end(); mi++) {
      Pair<string, string> pair = *mi;
      ratings.push_back(pair.second);
    }
    
    return ratings;
  } else {
    ratings.push_back("No Movies Rated");
    return ratings;
  }
}
