#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

#include "../../Structures/structures.h"
#include "../../Features/Messages/messages.h"
#include "../../Database/database.h"

#include "../Payment/payment.h"
#include "../Customer/customer.h"
#include "../Room/room.h"
#include "../Staff/staff.h"


struct Date {
    int year, month, date; 
};

bool validateDate(Date date);
bool getBookingById(int &booking_id, Booking &booking);
void findBooking();
Booking addBooking(int room_number = -1);
void showBookingDetails(int &booking_id);
void showCustomerBookings();
void showRoomBookings();
void showBookings();
void getBookings();
int BookingCallback(void *data, int columns, char** values, char **column_names);

#endif
