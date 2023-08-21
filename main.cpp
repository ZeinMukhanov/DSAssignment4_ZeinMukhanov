
//=================================================================================
// Name         : DS Assignment#4 
// Author       : Zein Mukhanov
// Version      : 1.0
// Description  : Starter Code for Contact Travel Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "flightticket.h"
#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print Number of Collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

// to be completed with all the necessary method definitions


//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;

	while(true)
	{
	  listCommands();
	  cout<<">";
    
		//to be completed 
    string command, parameter;
    cin >> command;

    if (command == "import" || command == "export" ||
        command == "delete" || command == "find" || 
        command == "allinday" || command == "printASC") { //if it has to take another parameter
        cin.ignore(); //to skip extra symbol
        getline(cin, parameter);
      }
    if (command == "import") {
//      parameter = "flight-ticket1k.csv"; //change
      cout << myFlightHASHTABLE.importCSV(parameter) << "\n"; //print the number read
    } else if (command == "export") {
//      parameter = "check.csv";
      cout << myFlightHASHTABLE.exportCSV(parameter) << "\n"; //print the number written
    } else if (command == "count_collisions") {
      cout << "Total Number of Collisions is " << myFlightHASHTABLE.count_collisions() << "\n";
    } else if (command == "add") {
      string companyName;
      int flightNumber;
      string country_of_origin;
      string country_of_destination;
      string stopOver;
      string price;
      string time_of_departure;
      string time_of_arrival;
      string date;
      string cur;
      cout << "Please enter the details of the flight-ticket:\n";
      cout << "Company Name: ";
      cin.ignore();
      getline(cin,companyName);
      cout << "Flight Number: ";
      cin >> flightNumber;
      cout << "Country of Origin: ";
      cin.ignore();
      getline(cin, country_of_origin);
      cout << "Country of Destination: ";
      getline(cin, country_of_destination);
      cout << "Stopover: ";
      getline(cin, stopOver);
      cout << "Price: ";
      getline(cin, price);
      cout << "Time of Departure: ";
      getline(cin, time_of_departure);
      cout << "Time of Arrival: ";
      getline(cin, time_of_arrival);
      cout << "Date: ";
      getline(cin, date);
      //adding ticket with the given parameters
      Flight_Ticket* add = new Flight_Ticket(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
      if (~myFlightHASHTABLE.add(add)) { //if not -1
        cout << "Flight-ticket has been successfully added !!\n";
      } // otherwise, the function itself will print the message
    } else if (command == "delete") {
      myFlightHASHTABLE.removeRecord(parameter); //removing
    } else if (command == "find") {
      myFlightHASHTABLE.find(parameter); //finding
    } else if (command == "allinday") {
      myFlightHASHTABLE.allinday(parameter); //all records in the same day
    } else if (command == "printASC") {
      myFlightHASHTABLE.printASC(parameter); //printing in ascending order
    } else if (command == "exit") {
      break; //exitting
    } else {
      cout << "Invalid command!!\n";
    }
	}

	return 0;
}
