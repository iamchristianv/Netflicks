UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CC=g++-4.8
    GTEST_LL=-I /usr/local/opt/gtest/include/ -lgtest_main -lpthread 
else
    ifeq ($(UNAME_S), Darwin)
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/opt/gtest/lib/ -lgtest_main -lgtest -lpthread
    else
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/lib/ -lgtest_main -lgtest -lpthread
    endif
endif

CC=g++-4.8
LIBS=lib
BIN=bin
SRC=src
TEST=tests
CFLAGS=-std=c++11 -ggdb
GTEST_CPPFLAGS=-g -I$(LIB) -I$(SRC) -pthread -std=gnu++0x

all: $(BIN)/app

$(BIN)/Movie.o: Movie.cpp Movie.h $(LIBS)/Map* $(LIBS)/Set*
	$(CC) -c -o $(BIN)/Movie.o Movie.cpp $(CFLAGS)

$(BIN)/User.o: User.cpp User.h $(LIBS)/Map* $(LIBS)/Set*
	$(CC) -c -o $(BIN)/User.o User.cpp $(CFLAGS)

$(BIN)/MovieApp.o: MovieApp.cpp $(BIN)/Movie.o $(BIN)/User.o
	$(CC) -c -o $(BIN)/MovieApp.o MovieApp.cpp $(CFLAGS)

$(BIN)/Netflicks.o: Netflicks.cpp Netflicks.h 
	$(CC) -c -o $(BIN)/Netflicks.o Netflicks.cpp $(CFLAGS)

$(BIN)/app: $(BIN)/MovieApp.o $(BIN)/Movie.o $(BIN)/User.o $(BIN)/Netflicks.o
	$(CC) -g -o $(BIN)/app $(BIN)/Netflicks.o $(BIN)/MovieApp.o $(BIN)/Movie.o $(BIN)/User.o $(CFLAGS)

$(BIN)/%.test.o: $(TEST)/%.cpp $(LIBS)/* $(BIN)/.dirstamp
	$(CC) $(GTEST_CPPFLAGS) $(GTEST_LL) -c $< -o $@

$(BIN)/MergeSortTest: $(TEST)/merge_sort_test.cpp 
	$(CC) $(GTEST_CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN)/SetTest: $(TEST)/set_test.cpp 
	$(CC) $(GTEST_CPPFLAGS) $^ $(GTEST_LL) -o $@

.PHONY: clean
.PHONY: mergetests
.PHONY: settests

mergetests: $(BIN)/MergeSortTest
	-@$(BIN)/MergeSortTest
	-@echo "--- All Tested!---"

settests: $(BIN)/SetTest
	-@$(BIN)/SetTest
	-@echo "--- All Tested!---"

clean:
	rm -f $(BIN)/*.o $(BIN)/app *~ $(BIN)/MergeSortTest $(BIN)/SetTest
