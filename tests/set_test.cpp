#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
using namespace std;
#include "../lib/SetH.h"

TEST(SetTests, UnionTestUno) {
  Set<int> set1, set2, set3;
  set1.add(1);
  set1.add(2);  
  set1.add(3);
  set1.add(4);
  set1.add(5);

  set2.add(3);  
  set2.add(4);
  set2.add(5);
  set2.add(6);
  set2.add(7);
  set2.add(8);

  bool actual[5];
  actual[0] = false;
  actual[1] = true;
  actual[2] = true;
  actual[3] = true;
  actual[4] = true;
  actual[5] = true;
  actual[6] = true;
  actual[7] = true;
  actual[8] = true;
  actual[9] = false;


  set3 = set1.setUnion(set2);
  
  for(int i = 0; i < 10; i++) {
    try {
      EXPECT_EQ(set3.contains(i), actual[i]);
    } catch(const NoSuchElementException& e){

    }
  }
}

TEST(SetTests, UnionTestDos) {
  Set<int> set1, set2, set3;
  set2.add(0);  
  set2.add(1);
  set2.add(2);
  set2.add(3);
  set2.add(4);

  bool actual[5];
  actual[0] = true;
  actual[1] = true;
  actual[2] = true;
  actual[3] = true;
  actual[4] = true;

  set3 = set1.setUnion(set2);
  
  for(int i = 0; i < 5; i++) {
    try {
      EXPECT_EQ(set3.contains(i), actual[i]);
    } catch(const NoSuchElementException& e){
      
    }
  }
}

TEST(SetTests, UnionTestTres) {
  Set<int> set1, set2, set3;
  set1.add(5);
  set1.add(4);  
  set1.add(3);
  set1.add(2);
  set1.add(1);

  set2.add(1);  
  set2.add(2);
  set2.add(3);
  set2.add(4);
  set2.add(5);

  bool actual[7];
  actual[0] = false;
  actual[1] = true;
  actual[2] = true;
  actual[3] = true;
  actual[4] = true;
  actual[5] = true;
  actual[6] = false;


  set3 = set1.setUnion(set2);
  
  for(int i = 0; i < 7; i++) {
    try {
      EXPECT_EQ(set3.contains(i), actual[i]);
    } catch(const NoSuchElementException& e){

    }
  }
}

TEST(SetTests, IntersectionTestUno) {
  Set<int> set1, set2, set3;
  set1.add(1);
  set1.add(2);  
  set1.add(3);
  set1.add(4);
  set1.add(5);
  set1.add(0);

  set2.add(3);  
  set2.add(4);
  set2.add(5);
  set2.add(6);
  set2.add(7);

  bool actual[10];
  actual[0] = false;
  actual[1] = false;
  actual[2] = false;
  actual[3] = true;
  actual[4] = true;
  actual[5] = true;
  actual[6] = false;
  actual[7] = false;

  set3 = set1.setIntersection(set2);
  
  for(int i = 0; i < 8; i++) {
    try {
      EXPECT_EQ(set3.contains(i), actual[i]);
    } catch(const NoSuchElementException& e){

    }
  }
}

TEST(SetTests, IntersectionTestDos) {
  Set<int> set1, set2, set3;
  set1.add(0);
  set1.add(9);  
  set1.add(8);
  set1.add(1);
  set1.add(2);

  set2.add(3);  
  set2.add(4);
  set2.add(5);
  set2.add(6);
  set2.add(7);

  bool actual[10];
  actual[0] = false;
  actual[1] = false;
  actual[2] = false;
  actual[3] = false;
  actual[4] = false;
  actual[5] = false;
  actual[6] = false;
  actual[7] = false;
  actual[8] = false;
  actual[9] = false;

  set3 = set1.setIntersection(set2);

  for(int i = 0; i < 10; i++) {
    try {
      EXPECT_EQ(set3.contains(i), actual[i]);
    } catch(const NoSuchElementException& e){

    }
  }
}

TEST(SetTests, IntersectionTestTres) {
  Set<int> set1, set2, set3;
  set1.add(1); 
  set1.add(3);  
  set1.add(5);
  set1.add(7);
  set1.add(9);

  set2.add(6);  
  set2.add(5);
  set2.add(4);
  set2.add(3);
  set2.add(2);
  set2.add(1);
  set2.add(0);

  bool actual[10];
  actual[0] = false;
  actual[1] = true;
  actual[2] = false;
  actual[3] = true;
  actual[4] = false;
  actual[5] = true;
  actual[6] = false;
  actual[7] = false;
  actual[8] = false;
  actual[9] = false;

  set3 = set1.setIntersection(set2);
  
  for(int i = 0; i < 10; i++) {
    try {
     EXPECT_EQ(set3.contains(i), actual[i]);
    } catch(const NoSuchElementException& e){

    }
  }
}
