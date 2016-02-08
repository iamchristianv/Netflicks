#ifndef MAPH_H
#define MAPH_H

#include <iostream>
#include <exception>
#include <string>
using namespace std; 

template<class T>
struct QueueItem {
  T value;
  QueueItem<T>* next;
};

template<class T>
class Queue {
 public:
  Queue();
  ~Queue();
  void enqueue(const T& item);
  void dequeue();
  const T& peekFront();
  bool isEmpty();
  void printHT();
 private:
  QueueItem<T>* head;
  QueueItem<T>* tail;
  int itemCount;
};

class NoSuchElementException {
 public:
  string error;
  NoSuchElementException(string error) {
    this->error = error;
  }
};

template<class firstType, class secondType>
struct Pair {
  firstType first;
  secondType second;
  Pair(firstType first, secondType second) {
    this->first = first;
    this->second = second;
  }
};

template<class keyType, class valueType>
struct MapItem {
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev;
  MapItem<keyType, valueType> *next;
};

template<class keyType, class valueType>
class Map {
 public:
  Map();
  ~Map();
  Map(const Map<keyType, valueType> &other);
  const Map<keyType, valueType>& operator=(const Map<keyType, valueType>& other);
  class Iterator {
  public: // create returnFirst, returnSecond
    Pair<keyType, valueType> operator*() const;
    Map<keyType, valueType>::Iterator operator++();
    Map<keyType, valueType>::Iterator operator++(int dummy);
    Map<keyType, valueType>::Iterator operator=(const Map<keyType, valueType>::Iterator& other);
    bool operator==(const Map<keyType, valueType>::Iterator& other) const;
    bool operator!=(const Map<keyType, valueType>::Iterator& other) const;
    friend class Map;
    Iterator(const Map<keyType, valueType>::Iterator& other);
    Iterator();
  private:
    Iterator(const Map<keyType, valueType>* m, MapItem<keyType, valueType>* i);
    MapItem<keyType, valueType>* current;
    const Map<keyType, valueType>* whoIBelongTo;
  };
  Map<keyType, valueType>::Iterator begin() const;
  Map<keyType, valueType>::Iterator end() const;
  const int size() const;
  void add(const keyType& key, const valueType& value);
  void remove(const keyType& key);
  const bool contains(const keyType& key) const;
  void merge(const Map<keyType, valueType>& other);
  valueType& get(const keyType& key);
  void print();
  void printHT(); 
 private:
  int itemCount;
  MapItem<keyType, valueType> *head;
  MapItem<keyType, valueType> *tail;
  MapItem<keyType, valueType> *tracker;
};

#include "MapCPP.h"

#endif
