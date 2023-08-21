#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include "flightticket.h"

// include additional header files if needed

using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+","+flightNumber
		Flight_Ticket value;
	public:
		HashNode(string key, Flight_Ticket value)
		{
			this->key = key;
			this->value = value;
		}
		friend class FlightHASHTABLE;
    friend class MyList;
};

#include "mylist.h"
//=============================================================================

class FlightHASHTABLE
{
	private:
		MyList *buckets;				//List of Buckets, Please create your own List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
	public:
    FlightHASHTABLE(int capacity = 100019) {
      this->capacity = 100019; //the least prime number greater than 10^5
      buckets = new MyList[capacity]; //allocating memory
      size = 0;
    }
    ~FlightHASHTABLE(); //destructor
		long hashCode(string); 						//implement and test different hash functions 
		long hashCode2(string); 						//implement and test different hash functions 
		long hashCode3(string); 						//implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order
		int count_collisions();					//return the number of collisions on the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		void removeRecord (string key);	//Delete a record with key from the hashtable
		void find(string key);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string key);  		//display the collisions for the entered key in an ascending order 

		//Add more methods and contructors, destructors if needed	
};

#endif
