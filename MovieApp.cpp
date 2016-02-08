#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;
#include "lib/SetH.h" 
#include "User.h"
#include "Movie.h"
#include "Netflicks.h"

void printMainMenu();
void printUserMenu();
void printQueueMenu();

int main(int argc, char** argv) {
  Netflicks netflicks(argc, argv);

  bool open = true;
  bool in = false;

  while(open) {
    printMainMenu();
    string mainInput;
    getline(cin, mainInput);

    if(mainInput == "1") {
      cout << "Enter User ID: ";
      string userID;
      getline(cin, userID);

      if(netflicks.loginUser(userID)) {
	cout << "Welcome back to Netflicks, " << userID << endl;
	in = true;
      } else {
	cout << "Sorry, the user ID you entered does not exist" << endl;
	in = false;
      }
    } else if(mainInput == "2") {
      cout << "Enter User ID: ";
      string userID;
      getline(cin, userID);

      cout << "Enter Name: ";
      string userName;
      getline(cin, userName);

      if(netflicks.createNewUser(userID, userName)) {
	cout << "Welcome to Netflicks, " << userID << endl;
      } else {
	cout << "Sorry, the user ID you entered is invalid or already exists" << endl;
      }
    } else if(mainInput == "3") {
      open = false;
    } else {
      cout << "Sorry, the option you entered is invalid" << endl;
    }

    while(in) {
      Movie* checkedOutMovie = netflicks.returnCheckedOutMovie();
      
      if(checkedOutMovie != NULL) {
	cout << "Checked Out Movie: " << checkedOutMovie->getTitle() << endl;
      } else {
	cout << "No Movie Checked Out" << endl;
      }

      printUserMenu();
      string userInput;
      getline(cin, userInput);

      if(userInput == "1") {
	cout << "Enter Title: ";
	string title;
	getline(cin, title);

	Movie* movie = netflicks.searchByTitle(title);

	if(movie != NULL) {
	  cout << movie->getTitle() << endl;
	  
	  Set<string> keywords = netflicks.returnKeywordsForMovie(title);
	  
	  for(Set<string>::Iterator si = keywords.begin(); si != keywords.end(); si++) {
	    string keyword = *si;
	    cout << keyword << endl;
	  }

	  bool under = true;

	  while(under) {
	    cout << "1. Add movie to queue" << endl;
	    cout << "2. Return to menu" << endl << endl;
	    cout << "Option: ";
	    
	    string movieInput;
	    getline(cin, movieInput);
	    
	    if(movieInput == "1") {
	      if(netflicks.addMovieToQueue(movie->getTitle())) {
		cout << "Movie Has Been Added To Queue" << endl;
	      }
	    } else if(movieInput == "2") {
	      under = false;
	    } else {
	      cout << "Sorry, the option you entered is invalid" << endl;
	    }
	  }
	} else {
	  cout << "No Movie Found" << endl;
	}
      } else if(userInput == "2") {
	cout << "Enter Keyword: ";
	string keyword;
	getline(cin, keyword);
	
	Set<Movie*> keywords = netflicks.searchByKeyword(keyword);

	int matches = keywords.size();

	cout << "Number of Matches: " << matches << endl;
	
	for(Set<Movie*>::Iterator si = keywords.begin(); si != keywords.end(); si++) {
	  Movie* movie = *si;
	  
	  cout << movie->getTitle() << endl;

	  Set<string> kkeywords = netflicks.returnKeywordsForMovie(movie->getTitle());
	  
	  for(Set<string>::Iterator ssi = kkeywords.begin(); ssi != kkeywords.end(); ssi++) {
	    string kkeyword = *ssi;
	    cout << kkeyword << endl;
	  }

	  bool out = true;
	  bool menu = false;

	  if(matches > 1) {
	    while(out) {
	      cout << "1. Next movie" << endl;
	      cout << "2. Add movie to queue" << endl;
	      cout << "3. Return to menu" << endl << endl;
	      cout << "Option: ";

	      string movieInput;
	      getline(cin, movieInput);
	      
	      if(movieInput == "1") {
		out = false;
	      } else if(movieInput == "2") {
		if(netflicks.addMovieToQueue(movie->getTitle())) {
		  cout << "Movie Has Been Added To Queue" << endl;
		}
	      } else if(movieInput == "3") {
		out = false;
		menu = true;
	      } else {
		cout << "Sorry, the option you entered is invalid" << endl;
	      }
	    }

	    if(menu) {
	      break;
	    }
	  } else {
	    while(out) {
	      cout << "1. Add movie to queue" << endl;
	      cout << "2. Return to menu" << endl << endl;
	      cout << "Option: ";

	      string movieInput;
	      getline(cin, movieInput);

	      if(movieInput == "1") {
		netflicks.addMovieToQueue(movie->getTitle());
	      } else if(movieInput == "2") {
		out = false;
		menu = true;
	      } else {
		cout << "Sorry, the option you entered is invalid" << endl;
	      }
	    }

	    if(menu) {
	      break;
	    }
	  }

	  matches--;
	}
      } else if(userInput == "3") {
	if(netflicks.userReturnMovie()) {
	  cout << "Movie Returned" << endl;
	} else {
	  cout << "No Movie To Return" << endl;
	}
      } else if(userInput == "4") {
	bool over = true;
	
	while(over) {
	  Movie* nextMovieInQueue = netflicks.returnNextMovieInQueue();
	  
	  if(nextMovieInQueue != NULL) {
	    cout << "Next Movie In Queue: " << nextMovieInQueue->getTitle() << endl;
	  } else {
	    cout << "No Movies In Queue" << endl;
	  }
	  
	  printQueueMenu();
	  string queueInput;
	  getline(cin, queueInput);
	  
	  if(queueInput == "1") {
	    if(netflicks.orderMovieFromQueue()) {
	      cout << "Movie Has Been Ordered" << endl;
	    } else {
	      cout << "Movie Cannot Be Ordered" << endl;
	    }
	  } else if(queueInput == "2") {
	    if(netflicks.removeMovieFromQueue()) {
	      cout << "Movie Has Been Removed From Queue" << endl;
	    } else {
	      cout << "No Movie To Remove From Queue" << endl;
	    }
	  } else if(queueInput == "3") {
	    if(netflicks.moveMovieToBackQueue()) {
	      cout << "Movie Has Been Moved To Back Of Queue" << endl;
	    } else {
	      cout << "No Movie To Move To Back Of Queue" << endl;
	    }
	  } else if(queueInput == "4") {
	    over = false;
	  } else {
	    cout << "Sorry, the option you entered is invalid" << endl;
	  }
	}
      } else if(userInput == "5") {
	in = false;
	netflicks.writeDataToUserFile();
      } else {
	cout << "Sorry, the option you entered is invalid" << endl;
      }
    }
  }

  return 0;
}

void printMainMenu() {
  cout << "1. Login" << endl;
  cout << "2. Create a new user" << endl;
  cout << "3. Quit" << endl;
  cout << endl << "Option: ";
}

void printUserMenu() {
  cout << "1. Search for a movie by title" << endl;
  cout << "2. Search for a movie by keyword" << endl;
  cout << "3. Return the current movie" << endl;
  cout << "4. View queue" << endl;
  cout << "5. Logout" << endl;
  cout << endl << "Option: ";
}

void printQueueMenu() {
  cout << "1. Order movie" << endl;
  cout << "2. Remove movie from queue" << endl;
  cout << "3. Move movie to back of queue" << endl;
  cout << "4. Return to user menu" << endl;
  cout << endl << "Option: ";
}

// // main menu functions
// void loginUser(Map<string, User*> &userData, bool &access, User* &currentUser);
// void createNewUser(string &userFile, Map<string, User*> &userData);

// // user menu functions
// void searchByTitle(Map<string, Movie*> &movieData, User* currentUser);
// void searchByKeyword(Map<string, Set<Movie*>* > &keywordData, Map<string, Movie*> &movieData, User* currentUser);

// // queue functions
// void showQueueMenu();
// void showNextMovie(User* currentUser);
// void orderMovieFromQueue(User* currentUser);
// void removeMovieFromQueue(User* currentUser);
// void moveMovieToBackQueue(User* currentUser);
// void addMovieToQueue(User* currentUser, Movie* movieToBeAdded);

// // memory deallocation functions
// void deleteUserData(Map<string, User*> &userData);
// void deleteMovieData(Map<string, Movie*> &movieData);
// void deleteKeywordData(Map<string, Set<Movie*>* > &keywordData);

// // data file functions
// void readMainDataFile(string &mainFile, string &userFile, string &movieFile);
// void readUserDataFile(string &userFile, Map<string, User*> &userData);
// void readMovieDataFile(string &movieFile, Map<string, Movie*> &movieData, Map<string, Set<Movie*>* > &keywordData);
// void writeDataToUserFile(Map<string, User*> userData, string userFile);

// // output functions
// void showMainMenu();
// void showUserMenu();
// void showCheckedOutMovie(User* currentUser);
// void showMovieInformation(Movie* movie, Set<string> tempKeywordSet);

// // string functions
// string contents(string line);
// string lowercase(string line);

// // main()
// int main(int argc, char **argv) {
//   Map<string, User*> userData;
//   Map<string, Movie*> movieData;
//   Map<string, Set<Movie*>* > keywordData;
  
//   string mainFile = argv[1];
//   string userFile;
//   string movieFile;

//   readMainDataFile(mainFile, userFile, movieFile);
//   readUserDataFile(userFile, userData);
//   readMovieDataFile(movieFile, movieData, keywordData);

//   int input;
//   bool access = false;
//   User* currentUser;

//   while(true) { 
//     showMainMenu();
//     cin >> input;
    
//     if(cin.fail() or input < 1 or input > 3) {
//       cout << endl << "Invalid Input" << endl << endl;
//       cin.clear();
//       cin.ignore(500, '\n');
//     } else if(input == 1) {
//       cin.ignore(500, '\n');
//       loginUser(userData, access, currentUser);
//     } else if(input == 2) {
//       cin.ignore(500, '\n');
//       createNewUser(userFile, userData);
//     } else if(input == 3) {
//       break;
//     }

//     while(access != false) {
//       showCheckedOutMovie(currentUser);
//       showUserMenu();
//       cin >> input;

//       if(cin.fail() or input < 1 or input > 5) {
// 	cout << endl << "Invalid Input" << endl << endl;
// 	cin.clear();
// 	cin.ignore(500, '\n');
//       } else if(input == 1) {
// 	cin.ignore(500, '\n');
// 	searchByTitle(movieData, currentUser);
//       } else if(input == 2) {
// 	cin.ignore(500, '\n');
// 	searchByKeyword(keywordData, movieData, currentUser);
//       } else if(input == 3) {
// 	currentUser->returnMovie();
//       } else if(input == 4) {
// 	cin.ignore(500, '\n');
// 	bool insideQueueMenu = true;
	
// 	while(insideQueueMenu) {
// 	  showNextMovie(currentUser);
// 	  showQueueMenu();
// 	  cin >> input;
	  
// 	  if(cin.fail() or input < 1 or input > 4) {
// 	    cout << endl << "Invalid Input" << endl << endl;
// 	    cin.clear();
// 	    cin.ignore(500, '\n');
// 	  } else if(input == 1) {
// 	    orderMovieFromQueue(currentUser);
// 	  } else if(input == 2) {
// 	    removeMovieFromQueue(currentUser);
// 	  } else if(input == 3) {
// 	    moveMovieToBackQueue(currentUser);
// 	  } else if(input == 4) {
// 	    insideQueueMenu = false;
// 	  }
// 	}
//       } else if(input == 5) {
// 	cout << endl;
// 	access = false;
// 	writeDataToUserFile(userData, userFile); 
// 	break;
//       }
//     } 
//   }
  
//   deleteUserData(userData);
//   deleteMovieData(movieData);
//   deleteKeywordData(keywordData);

//   return 0;
// }

// // contents()
// // returns the string after a command in a file
// string contents(string line) { 
//   string temp;
//   for(string::size_type i = 0; i < line.length(); i++) { 
//     if(line[i] == ' ' and line[i + 1] != ' ') {
//       temp = line.substr((i + 1), (line.length() - i));
//       break;
//     }
//   }
//   return temp;
// }

// // lowercase()
// // returns a lowercase version of the string
// string lowercase(string line) { 
//   string temp;

//   for(string::size_type i = 0; i < line.length(); i++) {
//     if(isalpha(line[i])) {
//       temp += tolower(line[i]);
//     } else if(isdigit(line[i])) {
//       temp += line[i];
//     } else if(line[i] == ' ') {
//       temp += ' ';
//     }
//   }

//   return temp;
// }

// // readMainDataFile()
// // reads what the user data file and movie data file are called
// void readMainDataFile(string &mainFile, string &userFile, string &movieFile) {
//   ifstream file;
//   file.open(mainFile.c_str());
//   string line;
  
//   while(getline(file, line)) {
//     if(userFile == "") {
//       userFile = line;
//     } else if(movieFile == "") {
//       movieFile = line;
//     }
//   }

//   file.close(); 
// }

// // readUserDataFile
// // reads the data for each user in the user data file
// void readUserDataFile(string &userFile, Map<string, User*> &userData) {
//   ifstream file;
//   file.open(userFile.c_str()); 
//   string line;
//   string userID;
//   string userName;
//   string command;
//   User* u;
//   Movie* m;
//   Queue<Movie*>* q;
//   bool queueStarted = false;
  
//   while(getline(file, line)) { 
//     stringstream ss(line);
    
//     if(line == "BEGIN QUEUE") {
//       queueStarted = true;
//     } else if(line == "END QUEUE") {
//       queueStarted = false;
//     } else if(queueStarted == true) {
//       m = new Movie(line);
//       q->enqueue(m);
//     } else {
//       ss >> command;
      
//       if(command == "BEGIN") {
// 	userID = contents(line);
//       } else if(command == "NAME:") {
// 	userName = contents(line);
// 	u = new User(userID, userName);
// 	q = u->movieQueue();
// 	userData.add(lowercase(userID), u);
//       } else if(command == "MOVIE:") {
// 	m = new Movie(contents(line)); 
// 	u->rentMovie(m);
//       } else if(command == "END") {
	
//       }
//     }
//   }
  
//   file.close();
// }

// // readMovieDataFile()
// // reads the data for each movie in the movie data file
// void readMovieDataFile(string &movieFile, Map<string, Movie*> &movieData, Map<string, Set<Movie*>* > &keywordData) {
//   ifstream file;
//   file.open(movieFile.c_str()); 
//   string line;
//   string movieTitle;
//   string movieKeyword;
//   string command;
//   string data;
//   Movie *m;
//   Set<Movie*> *s;
  
//   while(getline(file, line)) {
//     stringstream ss(line);
//     ss >> command;

//     if(command == "BEGIN") {
//       movieTitle = contents(line);
//       m = new Movie(movieTitle);
//     } else if(command == "KEYWORD:") {
//       movieKeyword = contents(line);
//       m->addKeyword(movieKeyword);
//       data = lowercase(movieKeyword);
      
//       if(keywordData.contains(data)) { // checks if another movie has the same keyword
// 	for(Map<string, Set<Movie*>* >::Iterator mi = keywordData.begin(); mi != keywordData.end(); mi++) {
// 	  Pair<string, Set<Movie*>* > item = *mi;

// 	  if(item.first == data) {
// 	    Set<Movie*> *tempMovieSet = item.second;
// 	    tempMovieSet->add(m);
// 	    break;
// 	  }
// 	}
//       } else if(!keywordData.contains(data)) {
// 	s = new Set<Movie*>;
// 	s->add(m); // adds the movie with the unique keyword
// 	keywordData.add(data, s);
//       }
//     } else if(command == "END") {
//       movieData.add(lowercase(movieTitle), m);
//     }
//   }
  
//   file.close();
// }

// // loginUser()
// void loginUser(Map<string, User*> &userData, bool &access, User* &currentUser) {
//   string dataInput;
  
//   cout << endl << "Login ID: ";
//   getline(cin, dataInput);
  
//   bool exit = false;
  
//   for(string::size_type i = 0; i < dataInput.length(); i++) {
//     if(dataInput[i] == ' ') { // checks if the login ID has spaces
//       cout << endl << "Invalid Input" << endl << endl;
//       access = false;
//       exit = true;
//       break;
//     }
//   }
  
//   if(userData.contains(lowercase(dataInput)) and exit != true) {
//     access = true;
//     currentUser = userData.get(lowercase(dataInput));
//   } else if(!userData.contains(lowercase(dataInput)) and exit != true) {
//     cout << endl << "ID does not exist" << endl << endl;
//     access = false;
//   }
// }

// // createNewUser()
// void createNewUser(string &userFile, Map<string, User*> &userData) {
//   string dataInput;
  
//   while(true) {
//     cout << endl << "Login ID: ";
//     getline(cin, dataInput);
    
//     bool exit = false;
    
//     for(string::size_type i = 0; i < dataInput.length(); i++) {
//       if(dataInput[i] == ' ') { // checks if the login ID has spaces
// 	cout << endl << "Invalid Input" << endl;
// 	exit = true;
// 	break;
//       }
//     }
    
//     if(!userData.contains(lowercase(dataInput)) and exit != true) {
//       cout << endl << "Name: ";
//       string name;
//       getline(cin, name);
      
//       User* u = new User(dataInput, name);
//       userData.add(lowercase(dataInput), u);
      
//       ofstream file;
//       file.open(userFile.c_str(), ios::app); 
//       file << "BEGIN " << dataInput << "\n";
//       file << "NAME: " << name << "\n";
//       file << "END\n";
//       file.close();

//       cout << endl;
//       break;
//     } else if(userData.contains(lowercase(dataInput)) and exit != true) {
//       cout << endl << "ID already exists" << endl;
//     }
//   }
// }

// // searchByTitle()
// void searchByTitle(Map<string, Movie*> &movieData, User* currentUser) {
//   string dataInput;
  
//   cout << endl << "Title: ";
//   getline(cin, dataInput);
  
//   if(movieData.contains(lowercase(dataInput))) {
//     for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
//       Pair<string, Movie*> pair = *mi;

//       if(pair.first == lowercase(dataInput)) {
// 	Movie* tempMovie = pair.second;
// 	Set<string> tempSet = tempMovie->getAllKeywords();

// 	int tempInput = 0;

// 	while(true) {
// 	  cout << endl << tempMovie->getTitle() << endl;
// 	  tempSet.print();
// 	  cout << endl;
// 	  cout << "1. Add movie to queue" << endl;
// 	  cout << "2. Return to menu" << endl << endl;
// 	  cout << "Option: ";
// 	  cin >> tempInput;
	  
// 	  if(cin.fail() or tempInput < 1 or tempInput > 2) {
// 	    cout << endl << "Invalid input" << endl;
// 	    cin.clear();
// 	    cin.ignore(500, '\n');
// 	  } else if(tempInput == 1) {
// 	    addMovieToQueue(currentUser, tempMovie);
// 	  } else if(tempInput == 2) {
// 	    break; // breaks out of while(true)
// 	  }
// 	}
	
// 	break;
//       }
//     }
//   } else if(!movieData.contains(lowercase(dataInput))) {
//     cout << endl << "No movie found" << endl;
//   }
// }

// // searchByKeyword()
// void searchByKeyword(Map<string, Set<Movie*>* > &keywordData, Map<string, Movie*> &movieData, User* currentUser) {
//   string dataInput;

//   cout << endl << "Keyword: ";
//   getline(cin, dataInput);
  
//   if(keywordData.contains(lowercase(dataInput))) {
//     for(Map<string, Set<Movie*>* >::Iterator mi = keywordData.begin(); mi != keywordData.end(); mi++) {
//       Pair<string, Set<Movie*>* > item = *mi;

//       if(item.first == lowercase(dataInput)) {
// 	Set<Movie*> *tempMovieSet = item.second;
// 	Movie *tempMovie;
// 	Set<string> tempKeywordSet;
// 	int matches = tempMovieSet->size();
	
// 	cout << endl << "Number of matches: " << matches << endl;
	
// 	// iterates through each movie (set of movies)
// 	for(Set<Movie*>::Iterator si = tempMovieSet->begin(); si != tempMovieSet->end(); si++) {
// 	  int tempInput;
// 	  bool exit = false;
	  
// 	  tempMovie = *si;
	  
// 	  if(matches > 1) {
// 	    while(true) {
// 	      showMovieInformation(tempMovie, tempKeywordSet);
	      
// 	      cout << "1. Next movie" << endl;
// 	      cout << "2. Add movie to queue" << endl;
// 	      cout << "3. Return to menu" << endl << endl;
// 	      cout << "Option: ";
// 	      cin >> tempInput;
	      
// 	      if(cin.fail() or tempInput < 1 or tempInput > 3) {
// 		cout << endl << "Invalid input" << endl << endl;
// 		cin.clear();
// 		cin.ignore(500, '\n');
// 	      } else if(tempInput == 1) {
// 		break; // breaks out of while(true)
// 	      } else if(tempInput == 2) {
// 		addMovieToQueue(currentUser, tempMovie);
// 	      } else if(tempInput == 3) {
// 		exit = true;
// 		break;
// 	      }
// 	    }
	    
// 	    if(exit == true) {
// 	      break; // breaks out of for(k)
// 	    }
// 	  } else if(matches == 1) {
// 	    while(true) {
// 	      showMovieInformation(tempMovie, tempKeywordSet);

// 	      cout << "1. Add movie to queue" << endl;
// 	      cout << "2. Return to menu" << endl << endl;
// 	      cout << "Option: ";
// 	      cin >> tempInput;
	      
// 	      if(cin.fail() or tempInput < 1 or tempInput > 2) {
// 		cout << endl << "Invalid input" << endl << endl;
// 		cin.clear();
// 		cin.ignore(500, '\n');
// 	      } else if(tempInput == 1) {
// 		addMovieToQueue(currentUser, tempMovie);
// 	      } else if(tempInput == 2) {
// 		break; // breaks out of while(true)
// 	      }
// 	    }
	    
// 	    break; // breaks out of for(k)
// 	  }

// 	  matches--;
// 	}

// 	break; // breaks out of for(i)
//       }
//     }
//   } else if(movieData.contains(lowercase(dataInput))) {
//     // iterates through each movie title
//     for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
//       Pair<string, Movie*> item = *mi;

//       if(item.first == lowercase(dataInput)) {
// 	Movie *tempMovie = item.second;
// 	cout << endl << tempMovie->getTitle() << endl;

// 	Set<string> tempSet = tempMovie->getAllKeywords();
// 	tempSet.print();

// 	cout << endl;
// 	break;
//       }
//     }
//   } else if(!keywordData.contains(lowercase(dataInput))) {
//     cout << endl << "No match" << endl << endl;
//   }
// }

// // showNextMovie()
// void showNextMovie(User* currentUser) {
//   Queue<Movie*>* userQueue = currentUser->movieQueue();
  
//   if(!userQueue->isEmpty()) {
//     Movie* nextMovie = userQueue->peekFront();
//     cout << endl << "Next Movie: " << nextMovie->getTitle() << endl << endl;
//   } else if(userQueue->isEmpty()) {
//     cout << endl << "Movie Queue Empty" << endl << endl;
//   }
// }

// // showMainMenu()
// void showMainMenu() {
//   cout << "1. Login" << endl;
//   cout << "2. Create a new user" << endl;
//   cout << "3. Quit" << endl;
//   cout << endl << "Option: ";
// }

// // showUserMenu()
// void showUserMenu() {
//   cout << "1. Search for a movie by title" << endl;
//   cout << "2. Search for a movie by keyword" << endl;
//   cout << "3. Return the current movie" << endl;
//   cout << "4. View queue" << endl;
//   cout << "5. Logout" << endl;
//   cout << endl << "Option: ";
// }

// // showCheckedOutMovie()
// void showCheckedOutMovie(User* currentUser) {
//   Movie* currentUserMovie = currentUser->currentMovie();
     
//   if(currentUserMovie != NULL) {
//     cout << endl << "Checked Out Movie: " << currentUserMovie->getTitle() << endl << endl;
//   } else if(currentUserMovie == NULL) {
//     cout << endl << "No Movie Checked Out" << endl << endl;
//   }
// }

// // deleteUserData() 
// void deleteUserData(Map<string, User*> &userData) {
//   for(Map<string, User*>::Iterator mi = userData.begin(); mi != userData.end(); mi++) {
//     Pair<string, User*> item = *mi;
//     User* tempUser = item.second;
//     Queue<Movie*>* tempQueue = tempUser->movieQueue();

//     while(!tempQueue->isEmpty()) {
//       Movie* tempMovie = tempQueue->peekFront();
//       tempQueue->dequeue();

//       if(tempMovie != NULL) {
// 	delete tempMovie;
//       }
//     }

//     Movie* tempMovie = tempUser->currentMovie();

//     if(tempMovie != NULL) {
//       delete tempMovie;
//     }

//     if(tempQueue != NULL) {
//       delete tempQueue;
//     }
    
//     if(tempUser != NULL) {
//       delete tempUser; // deletes the dynamically allocated user instances
//     }
//   }
// }

// // deleteMovieData()
// void deleteMovieData(Map<string, Movie*> &movieData) {
//   for(Map<string, Movie*>::Iterator mi = movieData.begin(); mi != movieData.end(); mi++) {
//     Pair<string, Movie*> item = *mi;
//     Movie* temp = item.second;
//     if(temp != NULL) {
//       delete temp; // deletes the dynamically allocated movie instances
//     }
//   }
// }

// // deleteKeywordData()
// void deleteKeywordData(Map<string, Set<Movie*>* > &keywordData) {
//   for(Map<string, Set<Movie*>* >::Iterator mi = keywordData.begin(); mi != keywordData.end(); mi++) {
//     Pair<string, Set<Movie*>* > item = *mi;
//     Set<Movie*> *temp = item.second;
//     if(temp != NULL) {
//       delete temp;
//     }
//   }
// }

// // showQueueMenu()
// void showQueueMenu() {
//   cout << "1. Order movie" << endl;
//   cout << "2. Remove movie from queue" << endl;
//   cout << "3. Move movie to back of queue" << endl;
//   cout << "4. Return to user menu" << endl;
//   cout << endl << "Option: ";
// }

// // orderMovie()
// void orderMovieFromQueue(User* currentUser) {
//   Queue<Movie*>* userQueue = currentUser->movieQueue();

//   if(userQueue->isEmpty()) {
//     cout << endl << "You cannot order a movie because your movie queue is empty" << endl;
//   } else if(currentUser->currentMovie() != NULL) {
//     cout << endl << "You cannot order another movie until you return the movie" << endl;
//     cout << "you currently have checked out" << endl;
//   } else if(currentUser->currentMovie() == NULL) {
//     Movie* movieToBeCheckedOut = userQueue->peekFront();
//     userQueue->dequeue();
//     currentUser->rentMovie(movieToBeCheckedOut);
//     cout << endl << "Movie has been ordered" << endl;
//   }
// }

// // removeMovieFromQueue()
// void removeMovieFromQueue(User* currentUser) {
//   Queue<Movie*>* userQueue = currentUser->movieQueue();

//   if(!userQueue->isEmpty()) {
//     userQueue->dequeue();
//   }
// }

// // moveMovieToBackQueue()
// void moveMovieToBackQueue(User* currentUser) {
//   Queue<Movie*>* userQueue = currentUser->movieQueue();

//   if(!userQueue->isEmpty()) {
//     Movie* movieToBeMovedBack = userQueue->peekFront();
//     userQueue->dequeue();
//     userQueue->enqueue(movieToBeMovedBack);
//   }
// }

// // addMovieToQueue()
// void addMovieToQueue(User* currentUser, Movie* movieToBeAdded) {
//   Queue<Movie*>* userQueue = currentUser->movieQueue();
//   userQueue->enqueue(movieToBeAdded);
//   cout << endl << "Movie has been added to queue" << endl;
// }

// // showMovieInformation()
// void showMovieInformation(Movie* tempMovie, Set<string> tempKeywordSet) {
//   cout << endl << tempMovie->getTitle() << endl;	  
//   tempKeywordSet = tempMovie->getAllKeywords();
//   tempKeywordSet.print();
//   cout << endl;
// }

// // writeDataToUserFile()
// void writeDataToUserFile(Map<string, User*> userData, string userFile) {
//   ofstream file;
//   file.open(userFile.c_str()); 
  
//   for(Map<string, User*>::Iterator mi = userData.begin(); mi != userData.end(); mi++) {
//     Pair<string, User*> pair = *mi;
//     User* user = pair.second;
//     Queue<Movie*>* userQueue = user->movieQueue();
//     Queue<Movie*>* tempQueue = new Queue<Movie*>;

//     file << "BEGIN " << user->getID() << "\n";
//     file << "NAME: " << user->getName() << "\n";
    
//     if(user->currentMovie() != NULL) {
//       Movie* userMovie = user->currentMovie();
//       file << "MOVIE: " << userMovie->getTitle() << "\n";
//     }

//     file << "BEGIN QUEUE\n";
    
//     if(!userQueue->isEmpty()) {
//       while(!userQueue->isEmpty()) {
// 	Movie* userMovie = userQueue->peekFront();
// 	file << userMovie->getTitle() << "\n";
// 	tempQueue->enqueue(userMovie);
// 	userQueue->dequeue();
//       }

//       while(!tempQueue->isEmpty()) {
// 	Movie* tempMovie = tempQueue->peekFront();
// 	userQueue->enqueue(tempMovie);
// 	tempQueue->dequeue();
//       }
//     }

//     file << "END QUEUE\n";
//     file << "END\n";

//     if(tempQueue != NULL) {
//       delete tempQueue;
//     }
//   }
  
//   file.close();
// }
