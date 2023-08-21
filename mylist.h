#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include "flighthashtable.h"

using namespace std;

class Node { //Node in MyList class
public:
  HashNode val; //value
  Node* next; //pointer to the next
  Node* prev; //pointer to the previous
public:
  Node(HashNode val): val(val), next(NULL), prev(NULL) {};
  friend class MyList;
};

class MyList {
public:
  Node* head;
public:
  int sz;
  void add(HashNode elem) {
    for (char & d : elem.key) d = tolower(d); //all letters are lowercase now
    Node* add = new Node(elem); // creating a new node for the element we're trying to add
  	add->next = head; // because we put elem in the beginning, its next element will be the head
  	if (head) head->prev = add; //if the head existed, then now its previous element is the one we're trying to add
    head = add; // at the same time, because the new node is in the beginning now, head will now point to it
    ++sz; //one more element now;
  }
  void remove() {
    if (head) { //if there's anything to delete
      Node* del = head; //saving the reference to delete later
      head = head->next; //we have a new head
      if (head) head->prev = NULL; //deleting the old reference for the new head
      delete del; //deleting the old one
      --sz; //one less element now
    }
  }
  MyList() : head(NULL), sz(0) {};
  ~MyList() { while (sz--) remove(); }
  bool empty() {
    return (!sz); //checking whether there is any element
  }
  friend class FlightHASHTABLE;
};


#endif