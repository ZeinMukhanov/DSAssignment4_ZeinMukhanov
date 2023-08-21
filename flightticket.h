#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
	public:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date) : companyName(companyName), flightNumber(flightNumber), country_of_origin(country_of_origin), country_of_destination(country_of_destination), stopOver(stopOver), price(price), time_of_departure(time_of_departure), time_of_arrival(time_of_arrival), date(date) {};
		// Please add additional methods, contructor if needed
    Flight_Ticket() { //empty constructor
      flightNumber = -1;
      companyName = country_of_origin = country_of_destination = stopOver = price = time_of_departure = time_of_arrival = date = "";
    }
    bool operator== (Flight_Ticket other) const { //overriding the == operator
      return (companyName == other.companyName and
        flightNumber == other.flightNumber and 
        country_of_origin == other.country_of_origin and
        country_of_destination == other.country_of_destination and
          stopOver == other.stopOver and 
          price == other.price and
          time_of_departure == other.time_of_departure and
          time_of_arrival == other.time_of_arrival and 
          date == other.date);
    }
};

#endif
