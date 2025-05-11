#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "../Components/Customer/customer.h"
#include "../Components/Staff/staff.h"
#include "../Structures/structures.h"
#include "../Features/Messages/messages.h"
#include <iostream>
#include <vector>
#include <string>

#include <stdexcept>
using namespace std;

bool signUp();
bool logIn();
void logOut(void (*startProgram)());

#endif
