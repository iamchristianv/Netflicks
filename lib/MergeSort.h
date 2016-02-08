#ifndef MERGESORT
#define MERGESORT
#include <iostream>
#include <vector>

class MergeSort { 
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

#endif
