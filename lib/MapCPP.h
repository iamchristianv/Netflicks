#ifndef MAPCPP_H
#define MAPCPP_H

// constructor for queue 
template<class T>
Queue<T>::Queue() {
  this->head = NULL;
  this->tail = NULL;
  this->itemCount = 0;
}

// destructor for queue
template<class T>
Queue<T>::~Queue() {
  QueueItem<T>* host = this->head;
  QueueItem<T>* guest = NULL;

  while(host != NULL) {
    guest = host->next;
    delete host;
    host = guest;
  }

  this->head = NULL;
  this->tail = NULL;
  this->itemCount = 0;
}

// enqueue(item) for queue
template<class T>
void Queue<T>::enqueue(const T& item) {
  if(this->itemCount == 0) {
    QueueItem<T>* newQueueItem = new QueueItem<T>;

    newQueueItem->value = item;
    newQueueItem->next = NULL;

    this->head = newQueueItem;
    this->tail = newQueueItem;

    this->itemCount++;
  } else if(this->itemCount > 0) {
    QueueItem<T>* newQueueItem = new QueueItem<T>;

    newQueueItem->value = item;
    newQueueItem->next = NULL;
    
    this->tail->next = newQueueItem;
    this->tail = newQueueItem;

    this->itemCount++;
  }
}

// dequeue() for queue
template<class T>
void Queue<T>::dequeue() {
  if(this->itemCount > 0) {
    QueueItem<T>* itemToRemove = this->head;
    
    this->head = itemToRemove->next;

    delete itemToRemove;
    this->itemCount--;
  }
}

// peekFront() for queue
template<class T>
const T& Queue<T>::peekFront() {
  if(this->itemCount > 0) {
    return this->head->value;
  } 
}

// isEmpty() for queue
template<class T>
bool Queue<T>::isEmpty() {
  if(this->itemCount == 0) {
    return true;
  } else if(this->itemCount > 0) {
    return false;
  }
}

// printHT() for queue
template<class T>
void Queue<T>::printHT() {
  QueueItem<T>* item = this->head;

  while(item != NULL) {
    cout << item->value->getTitle();

    if(item == head) {
      cout << " (HEAD)";
    }

    if(item == tail) {
      cout << " (TAIL)";
    }

    cout << endl;

    item = item->next;
  }
}

// constructor for map
template<class keyType, class valueType>
Map<keyType, valueType>::Map() {
  this->head = NULL;
  this->tail = NULL;
  this->tracker = NULL;
  this->itemCount = 0;
}

// destructor for map
template<class keyType, class valueType>
Map<keyType, valueType>::~Map() {
  if(this->head != NULL) {
    MapItem<keyType, valueType> *mi = this->head;
    MapItem<keyType, valueType> *temp = NULL;
    
    while(mi != NULL) {
      temp = mi->next;
      delete mi;
      mi = temp;
    }
    
    this->head = NULL;
    this->tail = NULL;
    this->tracker = NULL;
    this->itemCount = 0;
  }
}

// copy constructor for map
template<class keyType, class valueType>
Map<keyType, valueType>::Map(const Map<keyType, valueType>& other) {
  this->head = NULL;
  this->tail = NULL;
  this->tracker = NULL;
  this->itemCount = 0;
  
  if(other.head != NULL) {
    MapItem<keyType, valueType> *temp = other.head;
    
    while(temp != NULL) {
      this->add(temp->key, temp->value);
      temp = temp->next;
    }
  }
}

// operator=(map) for map
template<class keyType, class valueType>
const Map<keyType, valueType>& Map<keyType, valueType>::operator=(const Map<keyType, valueType>& other) {
  if(this == &other) { 
    return *this;
  }
  
  if(this->head != NULL) { 
    MapItem<keyType, valueType> *mi = this->head;
    MapItem<keyType, valueType> *temp = NULL;
    
    while(mi != NULL) {
      temp = mi->next;
      delete mi;
      mi = temp;
    }
    
    this->head = NULL;
    this->tail = NULL;
    this->tracker = NULL;
    this->itemCount = 0;
  }

  if(other.head != NULL) { 
    this->merge(other);
  }

  return *this;
}

// operator*() for iterator
template<class keyType, class valueType>
Pair<keyType, valueType> Map<keyType, valueType>::Iterator::operator*() const {
  Pair<keyType, valueType> pair(this->current->key, this->current->value);
  return pair;
}

// operator++() for iterator
template<class keyType, class valueType>
typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::Iterator::operator++() {
  this->current = this->current->next;
  return *this;
}

// operator++(dummy) for iterator
template<class keyType, class valueType>
typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::Iterator::operator++(int dummy) {
  return ++(*this);
}

// operator=(iterator) for iterator
template<class keyType, class valueType>
typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::Iterator::operator=(const Map<keyType, valueType>::Iterator& other) {
  if(this == &other) {
    return *this;
  }

  this->current = other.current;
  this->whoIBelongTo = other.whoIBelongTo;
  
  return *this;
}

// operator==(iterator) for iterator
template<class keyType, class valueType>
bool Map<keyType, valueType>::Iterator::operator==(const Map<keyType, valueType>::Iterator& other) const {
  return ((this->current == other.current) and (this->whoIBelongTo == other.whoIBelongTo));
}

// operator!=(iterator) for iterator
template<class keyType, class valueType>
bool Map<keyType, valueType>::Iterator::operator!=(const Map<keyType, valueType>::Iterator& other) const {
  return !(*this == other);
}

// copy constructor for iterator
template<class keyType, class valueType>
Map<keyType, valueType>::Iterator::Iterator(const Map<keyType, valueType>::Iterator& other) {
  this->whoIBelongTo = other.whoIBelongTo;
  this->current = other.current;
}

// constructor for iterator (without arguments)
template<class keyType, class valueType>
Map<keyType, valueType>::Iterator::Iterator() {
  this->whoIBelongTo = NULL;
  this->current = NULL;
}

// constructor for iterator (with arguments)
template<class keyType, class valueType>
Map<keyType, valueType>::Iterator::Iterator(const Map<keyType, valueType>* m, MapItem<keyType, valueType>* i) {
  this->whoIBelongTo = m;
  this->current = i;
}

// begin() for map
template<class keyType, class valueType>
typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::begin() const {
  Map<keyType, valueType>::Iterator mi(this, head);
  return mi;
}

// end() for map
template<class keyType, class valueType>
typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::end() const {
  Map<keyType, valueType>::Iterator mi(this, NULL);
  return mi;
}

// size() for map
template<class keyType, class valueType>
const int Map<keyType, valueType>::size() const {
  return itemCount;
}

// add(key, value) for map
template<class keyType, class valueType>
void Map<keyType, valueType>::add(const keyType& key, const valueType& value) {  
  if(this->head == NULL) { 
    MapItem<keyType, valueType> *mi = new MapItem<keyType, valueType>;

    this->head = mi;
    this->tail = mi;

    mi->key = key;
    mi->value = value;
    mi->next = NULL;
    mi->prev = NULL;
    
    this->itemCount++;
  } else { 
    MapItem<keyType, valueType> *temp = this->head;

    while(temp != NULL) { 
      if(temp->key == key) {
	return;
      }

      temp = temp->next;
    }
    
    MapItem<keyType, valueType> *mi = new MapItem<keyType, valueType>;
    
    mi->prev = this->tail; 
    this->tail->next = mi;
    this->tail = mi; 
    
    mi->key = key;
    mi->value = value;
    mi->next = NULL;
    
    this->itemCount++;
  }
}

// remove(key) for map
template<class keyType, class valueType> 
void Map<keyType, valueType>::remove(const keyType& key) { 
  if(this->head != NULL) { 
    MapItem<keyType, valueType> *temp = this->head;
    
    while(temp != NULL) {
      if(temp->key == key) {
	if(temp != this->head) { 
	  temp->prev->next = temp->next;
	} else {
	  this->head = temp->next; 
	}
	
	if(temp != this->tail) { 
	  temp->next->prev = temp->prev;
	} else {
	  this->tail = temp->prev;
	}
	
	delete temp;
	this->itemCount--;
	return;
      }
      
      temp = temp->next;
    }
  }
}

// contains(key) for map
template<class keyType, class valueType>
const bool Map<keyType, valueType>::contains(const keyType& key) const {
  if(this->head != NULL) {
    MapItem<keyType, valueType> *temp = this->head;
    
    while(temp != NULL) {
      if(temp->key == key) {
	return true;
      }

      temp = temp->next;
    }
  }

  return false;
}

// merge(map) for map
template<class keyType, class valueType>
void Map<keyType, valueType>::merge(const Map<keyType, valueType>& other) {
  if(other.head != NULL) {
    MapItem<keyType, valueType> *host = this->head; 
    MapItem<keyType, valueType> *guest = other.head;
    bool keyExists = false;
    
    while(guest != NULL) {
      host = this->head;
      keyExists = false;
      
      while(host != NULL) { 
	if(guest->key == host->key) {
	  keyExists = true;
	  break;
	}
	
	host = host->next;
      }
      
      if(keyExists == false) { 
	this->add(guest->key, guest->value);
      }
      
      guest = guest->next;
    }
  }
}

// get(key) for map
template<class keyType, class valueType>
valueType & Map<keyType, valueType>::get(const keyType& key) {   
  if(this->head != NULL) {
    MapItem<keyType, valueType> *temp = this->head;

    while(temp != NULL) {
      if(temp->key == key) {
	return temp->value;
      }
      
      temp = temp->next;
    }
  } else {
    throw NoSuchElementException("No such element exists!");
  }
}

// print() for map
template<class keyType, class valueType>
void Map<keyType, valueType>::print() {
  if(this->head != NULL) {
    MapItem<keyType, valueType> *temp = head;
    
    while(temp != NULL) {
      cout << temp->key << endl;
      temp = temp->next;
    }
  } 
}

// printHT() for map
template<class keyType, class valueType>
void Map<keyType, valueType>::printHT() {
  if(this->head != NULL) {
    MapItem<keyType, valueType> *temp = head;
    
    while(temp != NULL) {
      cout << temp->key << " : " << temp->value;
      if(temp == head) {
	cout << " (HEAD)";
      } 
      
      if(temp == tail) {
	cout << " (TAIL)";
      } 
      
    cout << endl;
    
    temp = temp->next;
    }
  } else {
    cout << "MAP IS EMPTY" << endl;
  }
}

#endif
