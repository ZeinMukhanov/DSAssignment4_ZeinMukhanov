#include "flighthashtable.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>


using namespace std;


long FlightHASHTABLE::hashCode(string key) {
  long res = 0; //variable with the hashCode
	long mult = 31; //the number we multiply the character's number with
	for (char it : key) {
		res += mult * (int(it) + 1); //adding the next character multiplied by the number 31 to the power of the current index
		mult *= 31; //increasing the power
		res %= 1000000007; //taking modulo to avoid exceeding the boundaries
		mult %= 1000000007; //taking modulo to avoid exceeding the boundaries
	}
	return res;
}

long FlightHASHTABLE::hashCode2(string key) {
  long res = 0; //variable with the hashCode
  for (char it : key) {
    res = (res << 5 | (res >> 27)); //bitwise shift to the left by 5 bits while saving 5 leftmost bits
    res += int(it) + 1; //adding current character
    res %= 1000000007; //taking modulo to avoid exceeding the boundaries
  }
  return res;
}

long FlightHASHTABLE::hashCode3(string key) {
  long res = 0; //variable with the hashCode
  long mult = 7; //the number we multiply the character's number with
  for (char it : key) {
    res += mult * (int(it) + 1); //adding the next character multiplied by the number 31 to the power of the current index
    mult *= 7; //increasing the power
    res %= 1000000007; //taking modulo to avoid exceeding the boundaries
    mult %= 1000000007; //taking modulo to avoid exceeding the boundaries
  }
  return res;
}


int FlightHASHTABLE:: add(Flight_Ticket* data) {
  string key = data->companyName + "," + to_string(data->flightNumber); //getting the key
  HashNode add(key, *data); //creating the HashNode with the given key and data
  for (int i = 0; i < key.size(); ++i) key[i] = tolower(key[i]); //now all letters are lowercase
  long hash = hashCode(key); //calculating its index (hash) in the buckets list
	hash %= capacity; // not to exceed the boundaries
	bool flag = 0; //whether already exists
  Node* it = buckets[hash].head;
  while (it != NULL) {
    if (it->val.value == *data) { //if found the same Flight Tickets in the system
      cout << "The record already exists in the system!!!\n";
			flag = 1;
      return -1; //didn't add
		}
    it = it->next;
  }

	if (!flag) { // if didn't occurr in the table
		buckets[hash].add(add); //putting the new node on an empty slot
		++size; //and increasing the size of the table
	}
  return 1; // added the ticket
}

FlightHASHTABLE:: ~FlightHASHTABLE()	{	//destructor
  capacity = size = 0;
}
int FlightHASHTABLE::importCSV(string path) {
  ifstream fin(path);
  if (!fin) return -1; //if the path is bad;
  int ret = 0;
  
  string companyName;
  int flightNumber;
  string country_of_origin;
  string country_of_destination;
  string stopOver;
  string price;
  string time_of_departure;
  string time_of_arrival;
  string date;

  string str;
  bool fir = 1; //whether the line is first
  while (getline(fin, str)) {
    if (fir) { //making sure to skip the first line
      fir = 0;
      continue;
    }
    string cur;
    int i = 0;
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    companyName = cur;
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    flightNumber = atoi(cur.c_str());
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    country_of_origin = cur;
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    country_of_destination = cur;
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    stopOver = cur;
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    price = cur;
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    time_of_departure = cur;
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the next comma
    time_of_arrival = cur;
    ++i; //skipping comma
    cur = "";
    while (i < str.size() and str[i] != ',') cur += str[i++]; //reading until the end of the string
    date = cur;
    date.pop_back(); //removing extra symbol
    Flight_Ticket* add = new Flight_Ticket(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
    this->add(add); //adding the flight ticket to the hashtable
    ++ret; //one more value read;
  }
  
  fin.close(); //not forgetting to close
  return ret;
}

int FlightHASHTABLE::exportCSV(string path) {
  ofstream fout(path);
  int ret = 0;
  if (!fout) return -1; //file cannot be created
  fout << "companyName,flightNumber, country-of-origin,country-of-destination,stopover,price,time-of-departure,time-of-arrival,date\n"; //first line to be consistent;
  for (int hash = 0; hash <= capacity; ++hash) {
    Node* it = buckets[hash].head;
    while (it != NULL) {
      fout << it->val.value.companyName << "," << //printing the flight in the form we imported it
        it->val.value.flightNumber << ","<<
        it->val.value.country_of_origin << "," <<
        it->val.value.country_of_destination << "," <<
        it->val.value.stopOver << "," <<
        it->val.value.price << "," <<
        it->val.value.time_of_departure << "," <<
        it->val.value.time_of_arrival << "," <<
        it->val.value.date << " \n";
      ++ret; //one more printed value
      it = it->next; //going further
    }
  }
  return ret;
}

int FlightHASHTABLE:: count_collisions() { //counts how many different keys have the same hash
  int res = 0;
  for (int hash = 0; hash <= capacity; ++hash) {
    Node* it = buckets[hash].head;
    while (it != NULL) {
      Node* it2 = buckets[hash].head;
      bool flag = 0; //whether the key has occurred before
      while (it2 != it) {
        if (it2->val.key == it->val.key) {
          flag = 1;
          break; //no need to waste time
        }
        it2 = it2->next;
      }
      if (!flag) { //if it is the first occurrence of the key
        ++res; //one more distinct key with the current hash
      }
      it = it->next;
    }
    if (!buckets[hash].empty()) { //if there was at least one key
      --res; //to find the number of different keys with the same hash for the current hash
    }
  }
  return res;
}

void FlightHASHTABLE::removeRecord(string key) {
  for (int i = 0; i < key.size(); ++i) key[i] = tolower(key[i]); //now all letters are lowercase
  int hash = hashCode(key); //hash for the key
  hash %= capacity;
  Node* it = buckets[hash].head;
  int records = 0; //number of records;
  while (it != NULL) {
    if (it->val.key != key) { //if we encountered the different key with the same hash
      it = it->next;
      continue;
    }
    ++records;
    it = it->next;
  }

  if (records == 0) { //if no record with the given key
    cout << "Not found!\n";
    return;
  }

  cout << records << " records found:\n";
  it = buckets[hash].head;
  int num = 0; //number of the record;
  while (it != NULL) {
    if (it->val.key != key) { //if we encountered the different key with the same hash
      it = it->next;
      continue;
    }
    ++num;
    cout << " " << num << ". ";
    cout << it->val.value.companyName << "," << //printing the flight ticket
      it->val.value.flightNumber << ","<<
      it->val.value.country_of_origin << "," <<
      it->val.value.country_of_destination << "," <<
      it->val.value.stopOver << ", " <<
      it->val.value.price << "," <<
      it->val.value.time_of_departure << "," <<
      it->val.value.time_of_arrival << "," <<
      it->val.value.date << "\n";
    it = it->next;
  }
  cout << "Please select the record you want to delete: ";
  int del;
  cin >> del; //which record to delete
  num = 0;
  it = buckets[hash].head;
  while (it != NULL) {
    if (it->val.key != key) { //if we encountered the different key with the same hash
      it = it->next;
      continue;
    }
    ++num;
    if (num == del) { //if we found the record to delete
      if (it == buckets[hash].head) { //if the node is the head
        buckets[hash].head = it->next;
      }
      if (it->next) it->next->prev = it->prev; //next node will have a new neighbour
      if (it->prev) it->prev->next = it->next; //previous node will have a new neighbour
      delete it;
      break; //the task is completed
    }
    it = it->next;
  }
  cout << "The flight-ticket record has been successfully deleted!\n"; 
}

void FlightHASHTABLE::find(string key) {
  for (int i = 0; i < key.size(); ++i) key[i] = tolower(key[i]); //now all letters are lowercase
  long hash = hashCode(key); //hash for the current key
  hash %= capacity;
  Node* it = buckets[hash].head;
  int records = 0; //number of records;
  while (it != NULL) {
    if (it->val.key != key) { //if we encountered the different key with the same hash
      it = it->next;
      continue;
    }
    ++records;
    it = it->next;
  }

  if (records == 0) { //if no record with the given key
    cout << "Not found!\n";
    return;
  }

  cout << records << " records found:\n";

  double st = time(NULL); //initial time
  
  it = buckets[hash].head;
  int num = 0; //number of the record;
  while (it != NULL) {
    if (it->val.key != key) { //if we encountered the different key with the same hash
      it = it->next;
      continue;
    }
    ++num;
    cout << " " << num << ". ";
    cout << "Company Name: " << it->val.value.companyName << "\n"<< "Flight Number: " << it->val.value.flightNumber << "\n"<<
      "Country of Origin: " << it->val.value.country_of_origin << "\n" << 
      "Country of Destination: " << it->val.value.country_of_destination << "\n" <<
      "Stopover: " <<
      it->val.value.stopOver << "\n" <<
        "Price: " << it->val.value.price << "\n" <<
       "Time of Departure: " << it->val.value.time_of_departure << "\n" << "Time of Arrival: " <<
      it->val.value.time_of_arrival << "\n" <<
      "Date: " <<
      it->val.value.date << "\n"; //printing the info about the ticket
    it = it->next;
  }
  
  double en = time(NULL); //ending time
  cout << "Time Taken: " << fixed << setprecision(3) << (en - st) << "\n";
}

void FlightHASHTABLE::allinday(string date) {
  int total = 0; //how many records with the given date
  for (int hash = 0; hash <= capacity; ++hash) {
    Node* it = buckets[hash].head;
    while (it != NULL) { 
      if (it->val.value.date != date) { //if not what we need
        it = it->next;
        continue; //skipping
      }
      ++total; //one more record found
      it = it->next;
    }
  }
  if (!total) { //if no record were found
    cout << "Not Found!\n"; 
    return;
  }
  cout << total << " records found:\n";
  int num = 0; //number of the record
  for (int hash = 0; hash <= capacity; ++hash) {
    Node* it = buckets[hash].head;
    while (it != NULL) {
      if (it->val.value.date != date) { //if not what we need
        it = it->next;
        continue; //skipping
      }
      ++num;
      cout << " " << num << ". ";
      cout << it->val.value.companyName << "," <<
        it->val.value.flightNumber << ","<<
        it->val.value.country_of_origin << "," <<
        it->val.value.country_of_destination << "," <<
        it->val.value.stopOver << "," <<
        it->val.value.price << "," <<
        it->val.value.time_of_departure << "," <<
        it->val.value.time_of_arrival << "," <<
        it->val.value.date << "\n"; //printing the info about the ticket with the needed date
      it = it->next;
    }
  }
}

void FlightHASHTABLE::printASC(string key) { 
  for (int i = 0; i < key.size(); ++i) key[i] = tolower(key[i]); //now all letters are lowercase
  long hash = hashCode(key); //hash for the current key
  hash %= capacity;

  for (int i = 0; i < buckets[hash].sz; ++i) { //performing sorting
    Node* it = buckets[hash].head;
    while (it != NULL) {
      if (it->next and it->val.value.country_of_destination > 
          it->next->val.value.country_of_destination) { //bubble sort
          swap(it->val, it->next->val);
      }
      it = it->next;
    }
  }
  
  Node* it = buckets[hash].head;
  bool flag = 0; //whether at least one record with the given key
  while (it != NULL) {
    if (it->val.key != key) { //if we encountered the different key with the same hash
      it = it->next;
      continue;
    }
    flag = 1;
    cout << it->val.value.companyName << "," <<
        it->val.value.flightNumber << ","<<
        it->val.value.country_of_origin << "," <<
        it->val.value.country_of_destination << "," <<
        it->val.value.stopOver << ", " <<
        it->val.value.price << "," <<
        it->val.value.time_of_departure << "," <<
        it->val.value.time_of_arrival << "," <<
        it->val.value.date << "\n";
    it = it->next;
  }
  
  if (!flag) { //if no record with the given key
    cout << "Not found!\n";
    return;
  }
}