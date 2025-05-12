#ifndef STAFF_H
#define STAFF_H

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

bool isStaffAlreadyRegistered(Staff &staff);
bool getStaffData(Staff &staff);
bool getStaffById(int& staff_id, Staff& staff);
bool getStaffByEmail(string email, Staff& staff);
Staff addStaff();
void removeStaff();
bool findStaff();
void showStaffs();
void showStaffProfile(int& staff_id = current_user.staff_id);
void getStaffs();
int StaffCallback(void*, int, char**, char**);

#endif
