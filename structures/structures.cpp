#include "structures.h"
#include "../Features/Messages/messages.h"
#include <iostream>

using namespace std;

User current_user;

vector<Staff> staffs;
vector<RoomType> roomtypes;
vector<Room> rooms;
vector<Customer> customers;
vector<Booking> bookings;
vector<Payment> payments;

// helper functions 
bool isEmpty(const string &str) {
    for(char c : str) {
        if (!isspace(c)) {
            return false; // Found a non-space character
        }
    }
    return str.empty();
}

bool validateEmail(string email){
  for(char c : email){
    if(c == '@'){
      return true;
    }
  }
  return false;
}

void cleanInput(){
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

void showInputError() {
    showError("Invalid input, please try again.");
    cleanInput();
}

string to_lower(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}