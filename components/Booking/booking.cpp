#include "booking.h"

bool validDate(Date date){   
    bool lower_limits = date.year > 2000 && date.month > 0 && date.date > 0; 
    bool upper_limits = date.year < 3000 && date.month <= 12 && date.date <= 31;
    return lower_limits && upper_limits;
}

bool compareDates(Date date1, Date date2){ // compares if the first date is less than the second date 

    if(date1.year < date2.year){
        return true;
    }
    
    if(date1.year > date2.year){
        return false;
    }

    // reaches here if the years are equal
    if(date1.month < date2.month){
        return true;
    }

    if(date1.month > date2.month){
        return false;
    }

    // reaches here if the months are equal 
    if(date1.date <=  date2.date){
        return true;
    }

    if(date1.date > date2.date){
        return false;
    }
    return false;
}



bool getBookingById(int &booking_id, Booking &booking) {
    for(Booking &b : bookings) {
        if(b.booking_id == booking_id) {
            booking = b;
            return true;
        }
    }
    return false;
}

// find booking using customer email and room number
void findBooking() {
    Room room;
    Customer customer;
    string email;
    int room_number;

    cout << "Enter customer email: ";
    cleanInput();
    getline(cin, email);

    cout << "Enter the room number: ";
    cin >> room_number;

    if(cin.fail()) {
        showInputError();
        return;
    }

    if(!getRoomByRoomNumber(room_number, room)) {
        showWarning("Room not found.");
        return;
    }
    
    if(!getCustomerByEmail(email, customer)) {
        showWarning("Customer not found.");
        return;
    }

    bool found = false;
    for(Booking &b : bookings) {
        if(b.customer_id == customer.customer_id && b.room_id == room.room_id) {
            showBookingDetails(b.booking_id);
            found = true;
            break;
        }
    }
    
    if(!found) {
        showWarning("Booking not found");
    }
}


Booking addBooking(int room_number){
    Customer customer;
    Room room;

    string customer_email; 
    Date check_in, check_out;

    if(current_user.isStaff){
        cleanInput();
        cout << "Enter customer email: ";
        getline(cin, customer_email);

        if(!getCustomerByEmail(customer_email, customer)){
            showWarning("Customer not found.");
            return Booking();
        }
    }

    if(room_number == -1){
        cout << "Enter the room number: ";
        cin >> room_number;
    }

    if(!getRoomByRoomNumber(room_number, room)){
        showWarning("Room not found.");
        return Booking();
    }

    if(room.is_available){
        showWarning("Room is still not booked");
        return Booking();
    }

    cout << "Enter check_in year (yyyy) : "; cin >> check_in.year;
    cout << "Enter check_in month (mm) : "; cin >> check_in.month;
    cout << "Enter check_in date (dd) : "; cin >> check_in.date;

    cout << endl << "Enter check_out year (yyyy): "; cin >> check_out.year;
    cout << "Enter check_out month (mm): "; cin >> check_out.month;
    cout << "Enter check_out date (dd): "; cin >> check_out.date;
    
    if(cin.fail()){
        showInputError();
        return Booking();
    }

    if(!validDate(check_in) || !validDate(check_out)){
        showError("Invalid Date");
        return Booking();
    }
    if(!compareDates(check_in, check_out)){
        showError("The dates must be correct relative to each other");
        return Booking();
    }

    try{

        string check_in_date = to_string(check_in.year) + "-" + to_string(check_in.month) + "-" + to_string(check_in.date);
        string check_out_date = to_string(check_out.year) + "-" + to_string(check_out.month) + "-" + to_string(check_out.date);

        string insertQuery;
        if(current_user.isStaff){
            insertQuery = 
            "INSERT INTO Bookings (room_id, customer_id, staff_id, check_in, check_out) VALUES (" + 
            to_string(room.room_id) + "," + to_string(customer.customer_id) + "," + to_string(current_user.staff_id) + ",'" + check_in_date + "' , '" + check_out_date + "');";
        }
        else{ // if the customer is registering by themselves
            insertQuery = 
            "INSERT INTO Bookings (room_id, customer_id, check_in, check_out) VALUES (" + 
            to_string(room.room_id) + "," + to_string(current_user.customer_id) + ",'" + check_in_date + "' , '" + check_out_date + "');";
        }

        if(!insertObject(insertQuery, "Bookings", BookingCallback, &bookings)){
            throw runtime_error("Failed to add booking");
        }
        if(current_user.isStaff){
            showSuccess("Booking succcessfully added");
        }
        return bookings.back();
    }
    catch(const exception& e){
        showError("Error: " + string(e.what()));
        exitProgram();
    }
    return Booking();
}

void showBookingDetails(int &booking_id) {
    Booking booking;

    if(!getBookingById(booking_id, booking)) {
        showWarning("Booking not found.");
        return;
    }

    Customer customer;
    Room room;
    RoomType roomtype;
    Staff staff;

    getCustomerById(booking.customer_id, customer);
    getStaffById(booking.staff_id, staff);
    getRoomById(booking.room_id, room);
    getRoomTypeById(room.room_type_id, roomtype);

    showHighlight("--- Booking Details ---");
    cout << "Booking Id: " << booking.booking_id << endl;
    cout << "Customer(Id): " << customer.name << " ("<< customer.customer_id << ")" << endl; 
    cout << "Room Number: " << room.room_number << endl;
    cout << "Room Type: " << roomtype.type_name << endl;
    if(staff.staff_id != -1){
        cout << "Staff(Id): " << staff.name << " ("<< staff.staff_id << ")" << endl << endl; 
    }
    else{
        cout << "Staff(Id): - " << endl << endl;
    }

    cout << "Check In: " << booking.check_in << endl;
    cout << "Check Out: " << booking.check_out << endl;
}


void showCustomerBookings(){
    Customer customer;
    string email;
    cout << "Enter the customer email: ";
    cleanInput();
    getline(cin, email);
    if(cin.fail()){
        showInputError();
        return;
    }

    if(!getCustomerByEmail(email, customer)){
        cout << "Customer not found " << endl;
        return;
    }

    showHighlight("--- Customer Bookings --- ( Customer " +  to_string(customer.customer_id) + " ) ");
    cout << left << setw(15) << "Booking Id" << setw(15) << "Room No" << setw(15) << "Room Type" << setw(15) << "Check In" << setw(15) << "Check Out" << endl;
    string(100, '-');

    bool found = false;
    for(Booking &b : bookings){
        if(b.customer_id == customer.customer_id){
            Room room;
            RoomType roomtype;
            getRoomById(b.room_id, room);
            getRoomTypeById(room.room_type_id, roomtype);

            cout <<  left << setw(15) << b.booking_id << setw(15) << room.room_number << setw(15) << roomtype.type_name << setw(15) << b.check_in << setw(15) << b.check_out << endl;
            found = true;
        }
    }
    if(!found){
        showWarning("Customer has no previous bookings.");
    }
}

void showRoomBookings(){
    int room_number;
    cout << "Enter the room number: ";
    cin >> room_number;

    if(cin.fail()){
        showInputError();
        return;
    }

    Room room;
    if(!getRoomByRoomNumber(room_number, room)){
        showWarning("Room not found.");
        return;
    }

    bool found = false;
    showHighlight("--- Room Bookings --- ( Room " + to_string(room_number) + " )") ;
    cout << left << setw(15) << "Booking Id" << setw(15) << "Customer" << setw(15) << "Room Type" << setw(15) << "Check In" << setw(15) << "Check Out" << endl;

    for(Booking &b : bookings){
        if(b.room_id == room.room_id){
            Customer customer;
            RoomType roomtype;
            getCustomerById(b.customer_id, customer);
            getRoomTypeById(room.room_type_id, roomtype);

            cout << left << setw(15) << b.booking_id << setw(15) << customer.name << setw(15) << roomtype.type_name << setw(15) << b.check_in << setw(15) << b.check_out << endl;
            found = true;
        }
    }

    if(!found){
        showWarning("Room has no previous bookings");
    }
}

void showBookings(){
    if(bookings.empty()){
        showWarning("No Bookings yet");
        return;
    }

    showHighlight("--- Bookings List --- ");
    cout << left << setw(15) << "Booking Id" << setw(15) << "Customer" 
        << setw(15) << "Room No" << setw(15) << "Room Type" << setw(15) 
        << "Staff" << setw(15) << "Check In" << setw(15) << "Check Out" << endl;

    for(Booking &b : bookings){
        Customer customer;
        Room room;
        RoomType roomtype;
        Staff staff;

        getCustomerById(b.customer_id, customer);
        getRoomById(b.room_id, room);
        getRoomTypeById(room.room_type_id, roomtype);
        getStaffById(b.staff_id, staff);

        cout << left << setw(15) << b.booking_id << setw(15) << customer.name << 
            setw(15) << room.room_number << setw(15) << roomtype.type_name <<
            setw(15) << (staff.staff_id != -1 ? staff.name : " - ") << setw(15) << b.check_in << setw(15) << b.check_out << endl;
    }
}





// database functions
void getBookings(){
    try{
        string selectQuery = "SELECT * FROM Bookings";
        if(!getObjects(selectQuery, BookingCallback, &bookings)){
            throw runtime_error("Failed to fetch all bookings");
        }
    }
    catch(const exception &e){
        showError("Error: " + string(e.what()));
        exitProgram();
    }
}


int BookingCallback(void *data, int columns, char **values, char **column_names){
    vector<Booking> *bookings = static_cast<vector<Booking> *>(data);

    Booking booking;

    booking.booking_id = values[0] ? atoi(values[0]) : -1;
    booking.customer_id = values[1] ? atoi(values[1]) : -1;
    booking.room_id = values[2]  ? atoi(values[2]) : -1;
    booking.staff_id = values[3] ? atoi(values[3]) : -1;
    booking.check_in = values[4] ? values[4] : "";
    booking.check_out = values[5] ? values[5] : "";

    bookings->push_back(booking);
    return 0;
}
