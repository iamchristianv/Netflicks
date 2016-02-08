#ifndef SETCPP_H
#define SETCPP_H

#include <iostream> 
#include <string>
#include <vector>
using namespace std; 
#include "MergeSort.h"

// constructor for set
template<class T>
Set<T>::Set() {
  
}

// destructor for set
template<class T>
Set<T>::~Set() {
  
}

// copy constructor for set
template<class T>
Set<T>::Set(const Set<T> &other) {
  internalStorage.merge(other.internalStorage);
}

// operator=(set) for set
template<class T>
const Set<T>& Set<T>::operator=(const Set<T> &other) {
  internalStorage = other.internalStorage;
  return *this;
}

// operator*() for iterator
template<class T>
T Set<T>::Iterator::operator*() const {
  Pair<T, T> pair = *internalIterator;
  return pair.first;
}

// operator++() for iterator
template<class T>
typename Set<T>::Iterator Set<T>::Iterator::operator++() {
  ++internalIterator;
  return *this;
}

// operator++(int dummy) for iterator
template<class T>
typename Set<T>::Iterator Set<T>::Iterator::operator++(int dummy) {
  ++internalIterator;
  return *this;
}

// operator=() for iterator
template<class T>
typename Set<T>::Iterator Set<T>::Iterator::operator=(const Set<T>::Iterator& other) {
  this->internalIterator = other.internalIterator;
  return *this;
}

// operator==() for iterator
template<class T>
bool Set<T>::Iterator::operator==(const Set<T>::Iterator& other) const {
  return (this->internalIterator == other.internalIterator);
}

// operator!=() for iterator
template<class T>
bool Set<T>::Iterator::operator!=(const Set<T>::Iterator& other) const {
  return (this->internalIterator != other.internalIterator);
}

// constructor for iterator (without arguments)
template<class T>
Set<T>::Iterator::Iterator() {
  
}

// constructor for iterator (with arguments)
template<class T>
Set<T>::Iterator::Iterator(const typename Map<T, T>::Iterator mi) : internalIterator(mi) {
  
}

// begin() for set
template<class T>
typename Set<T>::Iterator Set<T>::begin() const {
  Set<T>::Iterator si(internalStorage.begin());
  return si;
}

// end() for set
template<class T>
typename Set<T>::Iterator Set<T>::end() const {
  Set<T>::Iterator si(internalStorage.end());
  return si;
}

// size() for set
template<class T>
const int Set<T>::size() const {
  return internalStorage.size();
}

// add(item) for set
template<class T>
void Set<T>::add(const T& item) {
  internalStorage.add(item, item);
}

// remove(item) for set
template<class T>
void Set<T>::remove(const T& item) {
  internalStorage.remove(item);
}

// contains(item) for set
template<class T>
const bool Set<T>::contains(const T& item) const {
  return internalStorage.contains(item);
}

// merge(set) for set
template<class T>
void Set<T>::merge(const Set<T>& other) {
  internalStorage.merge(other.internalStorage);
}

// setUnion(set) for set
template<class T>
Set<T> Set<T>::setUnion(const Set<T>& other) const {
  vector<T> thisSet;
  vector<T> otherSet;
  vector<T> newSet;
  Set<T> setUnion;
  
  for(Set<T>::Iterator si = this->begin(); si != this->end(); si++) {
    thisSet.push_back(*si);
  }

  for(Set<T>::Iterator si = other.begin(); si != other.end(); si++) {
    otherSet.push_back(*si);
  }

  thisSet = MergeSort::sort(thisSet);
  otherSet = MergeSort::sort(otherSet);

  for(typename vector<T>::iterator vi = otherSet.begin(); vi != otherSet.end(); ++vi) {
    thisSet.push_back(*vi);
  }

  newSet = MergeSort::sort(thisSet);

  for(typename vector<T>::iterator vi = newSet.begin(); vi != newSet.end(); ++vi) {
    setUnion.add(*vi);
  }

  return setUnion;
}

// setIntersection(set) for set
template<class T>
Set<T> Set<T>::setIntersection(const Set<T>& other) const {
  vector<T> thisSet;
  vector<T> otherSet;
  vector<T> newSet;
  Set<T> setIntersection;

  for(Set<T>::Iterator si = this->begin(); si != this->end(); si++) {
    thisSet.push_back(*si);
  }

  for(Set<T>::Iterator si = other.begin(); si != other.end(); si++) {
    otherSet.push_back(*si);
  }

  thisSet = MergeSort::sort(thisSet);
  otherSet = MergeSort::sort(otherSet);
  
  for(int i = 0, k = 0; i < thisSet.size() and k < otherSet.size();) {
    if(thisSet[i] == otherSet[k]) {
      newSet.push_back(thisSet[i]);
      i++;
      k++;
    } else if(thisSet[i] > otherSet[k]) {
      k++;
    } else {
      i++;
    }
  }

  for(typename vector<T>::iterator vi = newSet.begin(); vi != newSet.end(); ++vi) {
    setIntersection.add(*vi);
  }

  return setIntersection;
}

// print() for set
template<class T>
void Set<T>::print() {
  internalStorage.print();
}

// printHT() for set
template<class T>
void Set<T>::printHT() {
  internalStorage.printHT();
}

#endif
