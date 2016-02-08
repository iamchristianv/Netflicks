#include <iostream>
#include <vector>
#include "gtest/gtest.h"
using namespace std;

class MergeSort : public::testing::Test {
public:
  template<class T>
  static vector<T> sort(vector<T> A) {
    subsort(A, 0, A.size()-1);
    return A;
  }
  
  template<class T>
  static void subsort(vector<T> &A, int L, int R) {
    if(L < R) {
      int M = (L + R) / 2;
      subsort(A, L, M);
      subsort(A, M + 1, R);
      merge(A, L, R, M);
    }
  }
  
  template<class T>
  static void merge(vector<T> &A, int L, int R, int M) {
    int I = L;
    int J = M + 1;
    int K = 0;
    
    vector<T> T((R - L + 1), 0);

    while(I <= M or J <= R) {
      if(((A[I] <= A[J]) or (J > R)) and (I <= M)) {
	T[K] = A[I];
	I++;
	K++;
      } else {
	T[K] = A[J];
	J++;
	K++;
      }
    }

    for(K = 0; K < (R - L + 1); K++) {
      A[K + L] = T[K];
    }
  }
};

TEST(MergeSortTests, BasicCase) {
  vector<int> unsorted;
  unsorted.push_back(1);
  unsorted.push_back(5);
  unsorted.push_back(3);
  unsorted.push_back(2);
  unsorted.push_back(4);

  vector<int> sorted = MergeSort::sort(unsorted);

  for(unsigned int i = 0; i < unsorted.size(); i++) {
    EXPECT_EQ(sorted.at(i), i + 1);
  }
}

TEST(MergeSortTests, SortedCase) {
  vector<int> unsorted;
  unsorted.push_back(1);
  unsorted.push_back(3);
  unsorted.push_back(5);
  unsorted.push_back(7);
  unsorted.push_back(9);

  int* actual = new int[5];
  actual[0] = 1;
  actual[1] = 3;
  actual[2] = 5;
  actual[3] = 7;
  actual[4] = 9;

  vector<int> sorted = MergeSort::sort(unsorted);

  for(unsigned int i = 0; i < unsorted.size(); i++) {
    EXPECT_EQ(sorted.at(i), actual[i]);
  }

  delete [] actual;
}

TEST(MergeSortTests, ReverseCase) {
  vector<int> unsorted;
  unsorted.push_back(8);
  unsorted.push_back(6);
  unsorted.push_back(4);
  unsorted.push_back(2);
  unsorted.push_back(0);

  int* actual = new int[5];
  actual[0] = 0;
  actual[1] = 2;
  actual[2] = 4;
  actual[3] = 6;
  actual[4] = 8;

  vector<int> sorted = MergeSort::sort(unsorted);
  for(unsigned int i = 0; i < unsorted.size(); i++) {
    EXPECT_EQ(sorted.at(i), actual[i]);
  }
  
  delete [] actual;
}

TEST(MergeSortTests, DuplicateCase) {
  vector<int> unsorted;
  unsorted.push_back(3);
  unsorted.push_back(2);
  unsorted.push_back(8);
  unsorted.push_back(8);
  unsorted.push_back(5);
  unsorted.push_back(5);
  unsorted.push_back(10);
  unsorted.push_back(14);

  int* actual = new int[8];
  actual[0] = 2;
  actual[1] = 3;
  actual[2] = 5;
  actual[3] = 5;
  actual[4] = 8;
  actual[5] = 8;
  actual[6] = 10;
  actual[7] = 14;

  vector<int> sorted = MergeSort::sort(unsorted);

  for(unsigned int i = 0; i < unsorted.size(); i++) {
    EXPECT_EQ(sorted.at(i), actual[i]);
  }
  
  delete [] actual;
}
