#include "room.h"

// Helper Functions
// Functions to find the required rooms
bool getRoomById(int room_id, Room &room) {
  for (Room &r : rooms) {
    if (r.room_id == room_id) {
      room = r;
      return true;
    }
  }
  return false;
}

bool getRoomByRoomNumber(int room_number, Room &room) {
  for (Room &r : rooms) {
    if (r.room_number == room_number) {
      room = r;
      return true;
    }
  }
  return false;
}

// check if room number exists
bool validateRoomNumber(int &room_number) {
  for (Room &r : rooms) {
    if (r.room_number == room_number) {
      return true;
    }
  }
  return false;
}

// to add a room
Room addRoom() {
    Room new_room;
  int room_number;
  int room_type_id;

  while (true) {
    // enter the room number of the new room 
    cout << "Enter Room Number: ";
    cin >> room_number;

    if (cin.fail()) {
        showInputError();
        continue;
    }

    if(room_number < 0){
      showError("No negative room numbers allowed ");
      return Room();
    }

    if(getRoomByRoomNumber(room_number, new_room)){
        showWarning("Room number already exists." );
        return Room();
    }

    // display all the available room types
    showHighlight(" --- Available Room Types --  ");
    cout << left << setw(15) << "ID " << setw(15) << "Room Type name" << endl;
    for(RoomType &rt : roomtypes){
        cout << left << setw(15) << rt.room_type_id << setw(15) << rt.type_name << endl; 
    }

    cout << "Enter the room type id: ";
    cin >> room_type_id;

    // check if the room type id is valid (exists)
    if (!validateRoomTypeId(room_type_id)) {
        showWarning("Invalid room type id. Please try again.");
        continue;
    }

    break;
  }

  string insertQuery = "INSERT INTO Rooms (room_number, room_type_id) VALUES ('" + to_string(room_number) +
      "', " + to_string(room_type_id) + ");";

  if (insertObject(insertQuery, "Rooms", RoomCallback, &rooms)) {
    showSuccess("Room added successfully.");
    return rooms.back();
  }
  else {
    showError("Failed to add Room.");
    return Room();
  }
}

// to remove a room
void removeRoom() {
  int room_number;
  cout << "Enter Room Number to remove: ";
  cin >> room_number;

  if(cin.fail()) {
    showInputError();
    return;
  }

  bool found = false;
  for (int i = 0; i < rooms.size(); i++) {
    if (rooms[i].room_number == room_number) {
      rooms.erase(rooms.begin() + i);
      found = true;
      break;
    }
  }
  if(!found){
    showWarning("Room Not Found");
    return;
  }

  try{
      string deleteQuery = "DELETE FROM Rooms WHERE room_number = '" + to_string(room_number) + "';";
      if (!deleteObject(deleteQuery)) {
        throw runtime_error("Failed to remove the room!");
    } 
    showSuccess("Room removed successfully.");
  }
  catch (const exception &e) {
      showError("Error: " + string(e.what()));
      exitProgram();
  }
}

void bookRoom() {
    if(current_user.room_id != -1){
        showWarning("You already booked a room.");
        return;
    }

    int room_number;
    cout << "Enter the room number you want to book: ";
    cin >> room_number;

    if(cin.fail()) {
        showInputError();
        return;
    }

    Room room;
    if (!getRoomByRoomNumber(room_number, room)) {
        showWarning("Room not found.");
        return;
    }

    if (!room.is_available) {
        showWarning("Room is not available.");
        return;
    }

    for(Room &r : rooms){
      if(r.room_number == room_number){
        r.is_available = false;
      }
    }

    // to add the current bookin gth the database 

    Booking booking = addBooking(room_number);
    if(booking.booking_id == -1){
      return;
    }

    // update the room availability in the database
    string updateQuery = "UPDATE Rooms SET is_available = 0 WHERE room_number = '" + to_string(room_number) + "';";
    
    try{
        if (!updateObject(updateQuery)) {
            throw runtime_error("Failed to update room availability.");
        }
        
        if(current_user.isCustomer){
          current_user.room_id = room.room_id; // set the current user's room id
        }
        showSuccess("Room booked successfully.");
    }
    catch (const exception &e) {
        showError("Error: " + string(e.what()));
        exitProgram();
    }
}

// show available rooms
void showAvailableRooms() {
    
    showHighlight("--- Available Rooms ---");
    cout << left << setw(15) << "Room ID" << setw(15) << "Room No" << setw(15)
    << "Room Type" << endl;
    
  for (const Room &room : rooms) {
      if (!room.is_available) {
          continue;
      }
    
    RoomType roomtype;
    getRoomTypeById(room.room_type_id, roomtype);
    cout << left << setw(15) << room.room_id << setw(15) << room.room_number << setw(15) << roomtype.type_name << endl;
  }
}

void showBookedRooms() {
    
    showHighlight("--- Booked Rooms ---");
    cout << left << setw(15) << "Room ID" << setw(15) << "Room No" << setw(15)
    << "Room Type" << endl;
    
  for (const Room &room : rooms) {
      if (room.is_available) {
          continue;
      }
    
    RoomType roomtype;
    getRoomTypeById(room.room_type_id, roomtype);
    cout << left << setw(15) << room.room_id << setw(15) << room.room_number << setw(15) << roomtype.type_name << endl;
  }
}

void showRoomsByTypes(){
  showHighlight("Room Types");
  cout << left << setw(15) << "ID " << setw(15) << "Room Type name" << endl;
  for(RoomType &rt : roomtypes){
      cout << left << setw(15) << rt.room_type_id << setw(15) << rt.type_name << endl; 
  }

  cout << "Enter the room type id: ";
  int room_type_id;
  cin >> room_type_id;
  if(cin.fail()){
      showInputError();
      return;
  }

  RoomType roomtype;
  if(!getRoomTypeById(room_type_id, roomtype)){
      showWarning("Room Type not found.");
      return;
  }

  showHighlight(" --- Rooms of " + roomtype.type_name + " --- ");
  cout << left << setw(15) << "Room ID" << setw(15) << "Room No" << endl;
  
  for(Room &r : rooms){
      if(r.room_type_id == room_type_id){
          cout << left << setw(15) << r.room_id << setw(15) << r.room_number << endl;
      }
  }
}


// show the properties of a room
void showRoomDetails(int room_number) {
  Room room;
  if (!getRoomByRoomNumber(room_number, room)) {
    showWarning("Room not found.");
    return;
  }

  RoomType roomtype;
  getRoomTypeById(room.room_type_id, roomtype);

  showHighlight("--- Room Details ---");
  cout << "Room ID: " << room.room_id << endl;
  cout << "Room Number: " << room.room_number << endl;
  cout << "Room Type: " << roomtype.type_name << endl;
  cout << "Availability: "
       << (room.is_available ? "Available" : "Not Available") << endl;
}


void leaveRoom() {
    if(current_user.room_id == -1){
        showWarning("You didn't book any room yet.");
        return;
    }

    int room_id = current_user.room_id;

    for(Room &r : rooms){
      if(r.room_id == room_id){
        r.is_available = true;
      }
    }

    try{
        string updateQuery = "UPDATE Rooms SET is_available = 1 WHERE room_id = " + to_string(room_id) + ";";
        
        if (!updateObject(updateQuery)) {
        showError("Failed to update room availability.");
        throw runtime_error("Failed to update room availability in database");
        }
    }
    catch (const exception &e) {
        showError("Error: " + string(e.what()));
        exitProgram();
    }
    current_user.room_id = -1; // reset the room id of the current user
    showSuccess("You left the room successfully.");
}




// Show all rooms function
void showRooms() {
    // string query = "SELECT * FROM Rooms;";
  
    // try{
    //     if (!getObjects(query, RoomCallback, &rooms)) {
    //       throw runtime_error("Failed to fetch rooms from database");
    //     }
    // }
    //   catch (const exception &e) {
    //       showError("Error: " + string(e.what()));
    //       exitProgram();
    //   }
  
    showHighlight("--- All Rooms ---");
    cout << left << setw(15) << "Room ID" << setw(15) << "Room No" << setw(15)
         << "Room Type" << setw(15) << "Availability" << endl;
    for (const Room &room : rooms) {
      RoomType roomtype;
      getRoomTypeById(room.room_type_id, roomtype);
  
      cout << left << setw(15) << room.room_id << setw(15) << room.room_number
           << setw(15) << roomtype.type_name << setw(15) << (room.is_available ? "Available" : "Not Available") << endl;
    }
  }


// database functions

void getRooms() {
  try {
    string query = "SELECT * FROM Rooms;";
    if (!getObjects(query, RoomCallback, &rooms)) {
      throw runtime_error("Error when retrieving all the rooms");
    }
  } catch (const exception &e) {
    showError("Error: " + string(e.what()));
    exitProgram();
  }
}

// callbacks
int RoomCallback(void *data, int columns, char **values, char **column_names) {
  vector<Room> *rooms = static_cast<vector<Room> *>(data);
  
  Room room;

  room.room_id = values[0] ? atoi(values[0]) : -1;
  room.room_number = values[1] ? atoi(values[1]) : -1;
  room.room_type_id = values[2] ? atoi(values[2]) : -1;
  room.is_available = atoi(values[3]) == 1 ? true : false;

  rooms->push_back(room);
  return 0;
}
