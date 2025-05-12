#include "payment.h"

// Get payment by ID
bool getPaymentById(int &payment_id, Payment &payment) {
  for (Payment p : payments) {
    if (p.payment_id == payment_id) {
      payment = p;
      return true;
    }
  }
  return false;
}

bool getPaymentByBookingId(int &booking_id, Payment &payment) {
  for (Payment p : payments) {
    if (p.booking_id == booking_id) {
      payment = p;
      return true;
    }
  }
  return false;
}

// Add payment to the database
Payment addPayment() {
  Payment payment;
  Booking booking;

  cout << "Booking Id: "; cin >> payment.booking_id;
  cout << "Amount: "; cin >> payment.amount;
  
  if (cin.fail()) {
    showInputError();
    return Payment(); 
  }

  if(payment.amount < 0){
    showError("Invalid amount ");
    return Payment();
  }

  if(getPaymentByBookingId(payment.booking_id, payment)){
    showWarning("Payment already exists for this Booking. ");
    return Payment();
  }

  if(!getBookingById(payment.booking_id, booking)){
    showWarning("Booking not found.");
    return Payment();
  }

  try {
    string insertQuery =
        "INSERT INTO Payments (booking_id, amount) VALUES (" +
        to_string(payment.booking_id) + ", " + to_string(payment.amount) + ");";

    // Use g_database instance to call insertObject
    if (!insertObject(insertQuery, "Payments", PaymentCallback, &payments)) {
      throw runtime_error("Failed to create payment in database");
    }

    showSuccess("Payment of $" + to_string(payment.amount) + " received for Booking ID " + to_string(payment.booking_id));
    return payments.back();
  } 
  catch (const exception &e) {
    showError("Error: " + string(e.what()));
    exitProgram();
    return Payment(); // Return an empty Payment object in case of error
  }
}

void showPaymentByBookingId(){
  int booking_id;
  cout << "Enter the booking id: ";
  cin >> booking_id;
  if (cin.fail()) {
    showInputError();
    return;
  }

  Payment payment;
  if(!getPaymentByBookingId(booking_id, payment)){
      showWarning("Payment not found for this booking.");
      return;
  }
  
  cout << "Payment ID: " << payment.payment_id << endl;
  cout << "Booking ID: " << payment.booking_id << endl;
  cout << "Amount: $" << payment.amount << endl;
  cout << "Payment Date: " << payment.payment_date << endl;
}

void showPaymentHistory() {
  if (payments.empty()) {
    showWarning("No payments recorded.");
    return;
  }

  showHighlight("--- Payment History ---");
  cout << left << setw(15) << "Payment ID" << setw(15) << "Booking ID" << setw(15)
       << "Amount" << setw(15) << "Payment Date" << endl;
  for (int i = payments.size() - 1; i > -1; --i) {
    const Payment &payment = payments.at(i);
    cout << left << setw(15) << payment.payment_id << 
            setw(15) << payment.booking_id << 
            setw(15) << payment.amount << setw(15) << payment.payment_date << endl;
  }
}

void generateInvoice() {
  int payment_id;
  cout << "Enter the payment id: ";
  cin >> payment_id;

  if(cin.fail()) {
    showInputError();
    return;
  }

  Payment payment;
  Booking booking;
  Customer customer;
  Room room;
  RoomType roomtype;
  Staff staff;

  if (!getPaymentById(payment_id, payment)) {
    showWarning("Payment not found");
    return;
  }
  if (!getBookingById(payment.booking_id, booking)) {
    showWarning("Booking not found");
    return;
  }
  if(!getRoomById(booking.room_id, room)){
    showWarning("Room not found ");
    return;
  }
  if(!getRoomTypeById(room.room_type_id, roomtype)){
     showWarning("Room Type not found ");
     return;
  }

  if(!getCustomerById(booking.customer_id, customer)){
    showWarning("Customer not found");
  }

  if (booking.staff_id != - 1 && !getStaffById(booking.staff_id, staff)) {
    showWarning("Staff not found");
    return;
  }

  showHighlight("----- Invoice -----");
  cout << "(Service Provider) Staff ID: " << (staff.staff_id != -1 ? to_string(staff.staff_id) : " - ") << endl;
  cout << "Staff Name: " << (staff.staff_id != -1 ? staff.name : " - ") << endl;
  cout << "Staff Email: " << (staff.staff_id != -1 ? staff.email : " - ") << endl << endl << endl;

  cout << "Payment ID: " << payment.payment_id << endl;
  cout << "Booking ID: " << payment.booking_id << endl << endl;

  cout << "Customer ID: " << booking.customer_id << endl;
  cout << "Customer Name: " << customer.name << endl;
  cout << "Customer Email: " << customer.email << endl << endl << endl;

  cout << "Room Number: " << room.room_number << endl;
  cout << "Room Type: " << roomtype.type_name << endl << endl << endl;

  cout << "Check-in Date: " << booking.check_in << endl;
  cout << "Check-out Date: " << booking.check_out << endl << endl << endl;

  cout << "Price: $" << payment.amount << endl;
  cout << "Payment Date: " << payment.payment_date << endl;
}



// database functions 
void getPayments() {
  try {
    string query = "SELECT * FROM Payments;";
    if (!getObjects(query, PaymentCallback, &payments)) {
      throw runtime_error("Error when retrieving all the payments");
    }
  } catch (const exception &e) {
    showError("Error: " + string(e.what()));
    exitProgram();
  }
}

int PaymentCallback(void *data, int columns, char **values,
                    char **column_names) {
  vector<Payment> *payments = static_cast<vector<Payment> *>(data);

  Payment payment;

  payment.payment_id = values[0] ? atoi(values[0]) : -1;
  payment.booking_id = values[1] ? atoi(values[1]) : -1;
  payment.amount = values[2] ? atof(values[2]) : -1;
  payment.payment_date = values[3] ? values[3] : "";

  payments->push_back(payment);

  return 0;
}
