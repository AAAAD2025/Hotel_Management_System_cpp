#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include "../../Structures/structures.h"
#include "../../Features/Messages/messages.h"
#include "../../Database/database.h"

using namespace std;

bool isCustomerAlreadyRegistered(Customer &customer);
bool getCustomerData(Customer &customer);
bool findCustomer();
bool getCustomerById(int& customer_id, Customer& customer);
bool getCustomerByEmail(string email, Customer& customer);
void getCustomers();
Customer addCustomer();
void removeCustomer();
void showCustomers();
void showCustomerProfile(int& customer_id = current_user.customer_id);
int CustomerCallback(void*, int, char**, char**);

#endif