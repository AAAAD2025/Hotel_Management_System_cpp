#include "roomtypes.h"
// Functions to find the required room types



// check if room type id exists
bool validateRoomTypeId(int room_type_id) {
    for (RoomType &rt : roomtypes) {
        if (rt.room_type_id == room_type_id) {
            return true;
        }
    }
    return false;
}


bool getRoomTypeById(int room_type_id, RoomType &roomtype) {
    for (RoomType &rt : roomtypes) {
        if (rt.room_type_id == room_type_id) {
            roomtype = rt;
            return true;
        }
    }
    return false;
}


bool getRoomTypeByTypeName(string type_name, RoomType &roomtype) {
    for (RoomType &rt : roomtypes) {
        if (to_lower(rt.type_name) == to_lower(type_name)) {
            roomtype = rt;
            return true;
        }
    }
    return false;
}


RoomType addRoomType() {
    RoomType new_roomtype;

    while(true){
        cout << "Enter Room Type Name: ";
        cleanInput();
        getline(cin, new_roomtype.type_name);

        if(isEmpty(new_roomtype.type_name)){
            showInputError();
            continue;
        }

        cout << "Enter Room Type Price: ";
        cin >> new_roomtype.price;
        if (cin.fail()) {
            showInputError();
            continue;
        }
        break;
    }



    if(getRoomTypeByTypeName(new_roomtype.type_name, new_roomtype)){
        showWarning("Room Type already exists.");
        return RoomType();
    }

    string insertQuery = "INSERT INTO RoomTypes (type_name, price) VALUES ('" + new_roomtype.type_name +
        "', " + to_string(new_roomtype.price) + ");";
    try {
        if (!insertObject(insertQuery, "RoomTypes", RoomTypeCallback, &roomtypes)) {
            throw runtime_error("Failed to add Room Type.");
        }
    }
    catch (const exception &e) {
        showError("Error: " + string(e.what()));
        exitProgram();
    }
    showSuccess("Room Type < " + new_roomtype.type_name + " > created successfully!" );
    return RoomType();
}


void removeRoomType() {
    RoomType roomtype;
    int room_type_id;
    cout << "Enter Room Type ID to remove: ";
    cin >> room_type_id;
    if (cin.fail()) {
        showInputError();
        return;
    }

    if(!getRoomTypeById(room_type_id, roomtype)){
        showWarning("Room Type not found.");
        return;
    }


    string deleteQuery = "DELETE FROM RoomTypes WHERE room_type_id = " + to_string(room_type_id) + ";";
    try {
        if (!executeQuery(deleteQuery)) {
            throw runtime_error("Failed to remove Room Type.");
        }
        
        showSuccess("Room Type with ID " + to_string(room_type_id) + " removed successfully!");
    } catch (const exception &e) {
        showError("Error: " + string(e.what()));
        exitProgram();
    }
}


void showRoomTypeDetails(){
    int room_type_id;
    cout << "Enter the room type id: ";
    cin >> room_type_id;
    if(cin.fail()){
        showInputError();
        return;
    }

    RoomType roomtype;
    if(!getRoomTypeById(room_type_id, roomtype)){
        showWarning("Room Type not found ");
        return;
    }

    int room_count = 0;
    for(Room &r : rooms){
        if(r.room_type_id == room_type_id){
            room_count++;
        }
    }

    showHighlight("-- Room Type Details --");

    cout << "Room Type Id: " << roomtype.room_type_id << endl;
    cout << "Room Type Name: " << roomtype.type_name << endl;
    cout << "Room Type Price: " << roomtype.price << endl;
    cout << "Number of rooms: " << room_count << endl;
}

void showRoomTypes() {
    if (roomtypes.empty()) {
        showWarning("No room types available.");
        return;
    }

    showHighlight("--- Room Types ---");
    cout << left << setw(15) << "ID" << setw(20) << "Type Name" << setw(15) << "Price" << endl;
    for (const RoomType &roomtype : roomtypes) {
        cout << left << setw(15) << roomtype.room_type_id << setw(20) << roomtype.type_name
             << setw(15) << roomtype.price << endl;
    }
}


// database functions 

void getRoomTypes() {
    try {
      string query = "SELECT * FROM RoomTypes;";
      if (!getObjects(query, RoomTypeCallback, &roomtypes)) {
        throw runtime_error("Error when retrieving all the room types");
      }
    } catch (const exception &e) {
      showError("Error: " + string(e.what()));
      exitProgram();
    }
}

// callback function to handle the result of the query
int RoomTypeCallback(void *data, int columns, char **values,
                     char **column_names) {
    vector<RoomType> *roomtypes = static_cast<vector<RoomType> *>(data);

    RoomType roomtype;
    roomtype.room_type_id = values[0] ? atoi(values[0]) : -1;
    roomtype.type_name = values[1] ? values[1] : "";
    roomtype.price = values[2] ? atof(values[2]) : -1;

    roomtypes->push_back(roomtype);
    return 0;
}