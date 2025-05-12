#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include "../../Structures/structures.h"
#include "../../Features/Messages/messages.h"
#include "../../Database/database.h"

// Components 
#include "../Booking/booking.h"
#include "../Customer/customer.h"
#include "../Room/room.h"
#include "../Staff/staff.h"

using namespace std;


bool getPaymentById(int& payment_id, Payment& payment);
bool getPaymentByBookingId(int& booking_id, Payment& payment);

Payment addPayment();
void updatePaymentStatus();
void showPaymentHistory();
void generateInvoice();
void showPaymentByBookingId();
void getPayments();
int PaymentCallback(void*, int, char**, char**);

#endif
