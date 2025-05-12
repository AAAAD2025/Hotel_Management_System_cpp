#include "menus.h"

void showRegistrationMenu() {
  int choice;

  showHighlight("********** Registration Menu **********");

userType:
// choose the type of the user
	while(!current_user.isCustomer && !current_user.isStaff) {
		cout << "0, Exit" << endl;
		cout << "1, Staff" << endl;
		cout << "2, Customer" << endl;
		cout << "Choice the type of user: ";
		cin >> choice;
		
		if (cin.fail()) {
			showInputError();
			continue;
		}
		
		switch (choice) {
		case 0:
			exitProgram();
		case 1:
			current_user.isCustomer = false;
			current_user.isStaff = true;
			break;
		case 2:
			current_user.isCustomer = true;
			current_user.isStaff = false;
			break;
		default:
			showInputError();
			continue;
		}
	}

authentication:
// choose the method of registration (sign up or log in)
	while(current_user.customer_id == -1 && current_user.staff_id == -1) {
		cout << "0, Previous menu" << endl;
		cout << "1, Log In " << endl;
		if(current_user.isCustomer){
			cout << "2, Sign Up " << endl;
		}

		cout << "Choose from the above: ";
		cin >> choice;

		if (cin.fail()) {
			showInputError();
			continue;
		}

		switch (choice) {
		case 0:
			current_user.isCustomer = false;
			current_user.isStaff = false;
			goto userType;
		case 1: {
			logIn();
			break;
		}
		case 2: {
			if (current_user.isCustomer) {
				signUp();
			}
			else{
				showInputError();
			}
			break;
		}
		default:
		showInputError();
		}
	}
}


void showCustomerMenu(void (*startProgram)(), void (*retrieveDatabaseData)()) {

  int choice;

  while (true) {
	retrieveDatabaseData();
	showHighlight("********** Customer Menu **********");
	cout << "1, Book a Room" << endl;
	cout << "2, See Room Types" << endl;
	cout << "3, See Available Rooms" << endl;
	cout << "4, See Booked Rooms " << endl;
	cout << "5, Display Room Details" << endl;
	cout << "6, Leave Room" << endl;
	cout << "7, Show User Profile" << endl;
	cout << "8, Logout" << endl;
	cout << "9, Exit" << endl;

	cout << "Enter your choice: ";
	cin >> choice;

	if (cin.fail() || choice < 1 || choice > 8) {
	  showInputError();
	  continue;
	}

	switch (choice) {
	case 1:
	  bookRoom();
	  break;
	case 2:
	  showRoomTypes();
	  break;
	case 3:
	  showAvailableRooms(); 
	  break;
	case 4: 
		showBookedRooms();
		break;
	case 5:
		{
			int room_number;
			cout << "Enter the room number: ";
			cin >> room_number;
			if(cin.fail()){
				showInputError();
				return;
			}
			showRoomDetails(room_number);
		}
	  break;
	case 6:
	  leaveRoom();
	  break;
	case 7:
	  showCustomerProfile();
	  break;
	case 8:
	  leaveRoom();
	  logOut(startProgram);
	  break;
	case 9:
	  leaveRoom();
	  exitProgram();
	default:
	  showInputError();
	}
  }
}


void showStaffMenu(void (*startProgram)(), void (*retrieveDatabaseData)()) {
	int choice;
  while(true){
	retrieveDatabaseData();
	  showHighlight("********* Staff Menu **********");
	  cout << "1, Customers" << endl;
	  cout << "2, Staffs" << endl;
	  cout << "3, Rooms" << endl;
	  cout << "4, Bookings" << endl;
	  cout << "5, Payments" << endl;
	  cout << "6, Show User Profile" << endl;
	  cout << "7, Logout" << endl;
	  cout << "8, Exit" << endl;
	  cout << "Enter your choice: ";
	  cin >> choice;

	  if (cin.fail()) {
		showInputError();
		continue;
	  }

	  switch (choice) {
	  case 1:
		CustomersMenu();
		break;
	  case 2:
		  if(current_user.isAdmin){
			  StaffsMenu();
		  }
		  else{
			showWarning("You are not allowed to view this menu ");
		  }
		break;
	  case 3:
		RoomsMenu();
		break;
	  case 4:
		BookingsMenu();
		break;
	  case 5:
		PaymentsMenu();
		break;
	  case 6:
		  showStaffProfile();
		  break;
	  case 7:
		logOut(startProgram);
		break;
	  case 8:
		exitProgram();
		break;
	  default:
		showInputError();
	  }
  }
}




void CustomersMenu() {
  int choice;
  while (true) {
    showHighlight("********** Customers Menu **********");
    cout << "0, Previous menu" << endl;
    cout << "1, Add Customer" << endl;
    cout << "2, Remove Customer" << endl;
    cout << "3, Show Customers" << endl;
    cout << "4, Find Customer by email" << endl;
    cout << "5, Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
      showInputError();
      continue;
    }

    switch (choice) {
    case 0:
      return;
    case 1:
      addCustomer();
      break;
    case 2:
      removeCustomer();
      break;
    case 3:
      showCustomers();
      break;
    case 4: {
		findCustomer();
		break;
      };
    break;
    case 5:
      exitProgram();
    default:
      showInputError();
    }
  }
}

void StaffsMenu() {
  int choice;
  while (true) {
    showHighlight("********** Staffs Menu **********");
    cout << "0, Previous menu" << endl;
    cout << "1, Add Staff " << endl;
    cout << "2, Remove Staff" << endl;
    cout << "3, Show Staffs" << endl;
    cout << "4, Find Staff by email" << endl;
    cout << "5, Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
      showInputError();
      continue;
    }

    switch (choice) {
    case 0:
      return; // go back to previous menu
    case 1:
      addStaff();
      break;
    case 2:
      removeStaff();
      break;
    case 3:
      showStaffs();
      break;
    case 4: {
		findStaff();
    } break;
    case 5:
      exitProgram();
    default:
      showInputError();
    }
  }
}

void RoomsMenu(){
	int choice;
	  while(true){
		showHighlight("********** Rooms Menu **********");
		cout << "0, Previous menu" << endl;
		cout << "1, Add Room" << endl;
		cout << "2, Remove Room" << endl;
		cout << "3, Book Room for customer " << endl;
		cout << "4, Show Available Rooms" << endl;
		cout << "5, Show Booked Rooms " << endl;
		cout << "6, Show Rooms" << endl; // show all rooms
		cout << "7, Show Room By Types" << endl; // show rooms of a specific room type
		cout << "8, Add Room Type" << endl;
		cout << "9, Remove Room Type" << endl;
		cout << "10, Show Room Types" << endl;
		cout << "11, Exit" << endl;

		cout << "Enter your choice: ";
		cin >> choice;

		if (cin.fail()) {
		  showInputError();
		  continue;
		}

		switch (choice) {
		case 0:
			return;
		case 1:
		  addRoom();
		  break;
		case 2:
		  removeRoom();
		  break;
		case 3:
			bookRoom();
			break;
		case 4:
			showAvailableRooms();
			break;
		case 5:
			showBookedRooms();
			break;
		case 6:
			showRooms();
		break;
		case 7:
			showRoomsByTypes();
			break;
		case 8:
			addRoomType();
		break;
		case 9:
			removeRoomType();
			break;
		case 10:
			showRoomTypes();
		  break;
		case 11:
		  exitProgram();
		  break;
		default:
		  showInputError();
		}
	  }
}

void BookingsMenu() {
  int choice;
  while (true) {
    showHighlight("********** Bookings Menu **********");
	cout << "0, Previous Menu" << endl;
    cout << "1, Add Booking" << endl;
    cout << "2, Show All Bookings" << endl;
	cout << "3, Show Customer Bookings" << endl;
	cout << "4, Show Room Bookings" << endl;
    cout << "5, Find Booking by Customer email and Room number" << endl;
	cout << "6, Show Booking Details " << endl;
    cout << "7, Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
      showInputError();
      continue;
    }

    switch (choice) {
	case 0:
		return;
    case 1:
      addBooking();
      break;
    case 2:
      showBookings();
      break;
	case 3:
		showCustomerBookings();
		break;
	case 4:
		showRoomBookings();
		break;
    case 5:
      findBooking();
      break;
    case 6:
		{
			int booking_id;
			cout << "Enter the booking id: ";
			cin >> booking_id;
			showBookingDetails(booking_id);
		}
      break;
    case 7:
      exitProgram();
      break;
    default:
      showInputError();
    }
  }
}

void PaymentsMenu(){
	int choice;
	  while(true){
		showHighlight("********** Payments Menu **********");
		cout << "0, Previous menu" << endl;
		cout << "1, Add Payment" << endl;
		cout << "2, Show Payments History" << endl;
		cout << "3, Show Payment by Booking ID" << endl;
		cout << "4, Generate Invoice" << endl;
		cout << "5, Exit" << endl;

		cout << "Enter your choice: ";
		cin >> choice;

		if (cin.fail()) {
		  showInputError();
		  continue;
		}

		switch (choice) {
		case 0:
			return;
		case 1:
		  addPayment();
		  break;
		case 2:
		  showPaymentHistory();
		  break;
		case 3:
			showPaymentByBookingId();
			break;
		case 4:
			generateInvoice();
			break;
		case 5:
		  exitProgram();
		  break;
		default:
		  showInputError();
		}
	  }
}