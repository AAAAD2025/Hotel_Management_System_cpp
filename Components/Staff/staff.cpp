#include "staff.h"


// helper functions
bool isStaffAlreadyRegistered(Staff &staff) {
  for (const Staff &s : staffs) {
    if (s.email == staff.email) {
      return true;
    }
  }
  return false;
}

bool getStaffData(Staff &staff) {
  cleanInput();
  while (true) {
    cout << "Name: ";
    getline(cin, staff.name);
    cout << "Email: ";
    getline(cin, staff.email);
    cout << "Password: ";
    getline(cin, staff.password);
    cout << "Phone Number: ";
    getline(cin, staff.phone_number);
    cout << "Role: ";
    getline(cin, staff.role);

    if (isEmpty(staff.name) || isEmpty(staff.email) ||
        isEmpty(staff.password) || isEmpty(staff.phone_number) ||
        isEmpty(staff.role)) {
      showError("Empty fields detected. Please fill all fields correctly.");
      continue;
    }

    if(!validateEmail(staff.email)){
      showError("Enter an appropriate email please ");
    }

    if (isStaffAlreadyRegistered(staff)) {
      showWarning("Staff already registered. Please try again.");
      return false;
    }
    return true;
  }
}


// Get staff by ID
bool getStaffById(int &staff_id, Staff &staff) {
  for (Staff &s : staffs) {
    if (s.staff_id == staff_id) {
      staff = s;
      return true;
    }
  }
  return false;
}

bool getStaffByEmail(string email, Staff &staff){
  for (Staff &s : staffs) {
    if (s.email == email) {
      staff = s;
      return true;
    }
  }
  return false;
}


// main  functions

Staff addStaff() {
  Staff staff;
  if(!getStaffData(staff)){
    return Staff();
  }

  try {
    string insertQuery = "INSERT INTO Staff (name, email, password, "
                         "phone_number, role) VALUES ('" +
                         staff.name + "', '" + staff.email + "', '" +
                         staff.password + "', '" + staff.phone_number + "', '" +
                         staff.role + "');";

    if (!insertObject(insertQuery, "Staff", StaffCallback, &staffs)) {
      throw runtime_error("Failed to create staff in database");
    }

    showSuccess("Staff < " + staff.name + " > created successfully!");
    return staffs.back();
  } 
  catch (const exception &e) {
    showError("Error: " + string(e.what()));
    exitProgram();
    return Staff(); // Return an empty Staff object in case of error
  }
}

void removeStaff() {
  string email;
  cleanInput();
  cout << "Enter the email of the staff to remove: ";
  getline(cin, email);

  bool found = false;
  for (int i = 0; i < staffs.size(); ++i) {
    if (staffs.at(i).email == email) {
      staffs.erase(staffs.begin() + i);
      found = true;
      break;
    }
  }
  if (!found) {
    showError("Staff not found.");
    return;
  }

  try {
    string deleteQuery = "DELETE FROM Staff WHERE email = '" + email + "';";

    if (!deleteObject(deleteQuery)) {
      throw runtime_error("Failed to delete staff from database");
    }

    showSuccess("Staff deleted successfully!");
  }

  catch (const exception &e) {
    showError("Error: " + string(e.what()));
    exitProgram();
  }
}


void showStaffProfile(int &staff_id) {
  Staff staff;
  if (!getStaffById(staff_id, staff)) {
    showWarning("Staff not found.");
    return;
  }

  showHighlight("--- Staff Profile ---");

  cout << "\tStaff ID: " << staff.staff_id << endl;
  cout << "\tName: " << staff.name << endl;
  cout << "\tEmail: " << staff.email << endl;
  cout << "\tPhone Number: " << staff.phone_number << endl;
}


bool findStaff() {
  Staff staff;
  string email;
  cout << "Enter the email of the staff: ";
  cleanInput();
  getline(cin, email);

  if(!getStaffByEmail(email, staff)){
    showWarning("Staff not found.");
    return false;
  }

  showStaffProfile(staff.staff_id);
  return true;
}

void showStaffs() {
  if (staffs.empty()) {
    showWarning("No staffs registered.");
    return;
  }

  showHighlight("--- Staff List ---");
  cout << left << setw(15) << "Staff ID" << setw(20) << "Name" << setw(30)
       << "Email" << setw(15) << "Phone" << setw(15) << "Role" << endl;

  cout << string(77, '-') << endl;

  for (int i = staffs.size() - 1; i > -1; --i) {
    const Staff &staff = staffs.at(i);

    cout << left << setw(15) << staff.staff_id << setw(20) << staff.name
         << setw(30) << staff.email << setw(20) << staff.phone_number
         << setw(15) << staff.role << endl;
  }
}




// database functions

// Retrieve all the staffs from the database
void getStaffs() {
  try {
    string query = "SELECT * FROM Staff;";

    if (!getObjects(query, StaffCallback, &staffs)) {
      throw runtime_error("Error when retrieving all the staffs");
    }

  } catch (const exception &e) {
    showError("Error: " + string(e.what()));
    exitProgram();
  }
}

int StaffCallback(void *data, int columns, char **values, char **column_names) {
  vector<Staff> *staffs = static_cast<vector<Staff> *>(data);
  Staff staff;

  staff.staff_id = atoi(values[0]);
  staff.name = values[1] ? values[1] : "";
  staff.role = values[2] ? values[2] : "";
  staff.phone_number = values[3] ? values[3] : "";
  staff.email = values[4] ? values[4] : "";
  staff.password = values[5] ? values[5] : "";

  staffs->push_back(staff);
  return 0;
}
