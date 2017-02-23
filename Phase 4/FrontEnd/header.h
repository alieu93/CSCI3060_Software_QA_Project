#include <iostream>

using namespace std;

#ifndef HEADER_H_
#define HEADER_H_

struct User{
    string name;
    string accountType;
    int credit;
    bool login;
};

struct Event{
    string event;
    string seller;
    int numOfTickets;
    double priceOfTickets;
};
#endif
