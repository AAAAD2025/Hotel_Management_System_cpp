#ifndef ROOMTYPES_H
#define ROOMTYPES_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>

#include "../../Structures/structures.h"
#include "../../Features/Messages/messages.h"
#include "../../Database/database.h"

// helper functions
void tolower(string &str);
bool validateRoomTypeId(int room_type_id);
bool getRoomTypeById(int room_type_id, RoomType &roomtype);
bool getRoomTypeByTypeName(string type_name, RoomType &roomtype);

// room type menu functions
RoomType addRoomType();
void removeRoomType();
void showRoomTypes();
void getRoomTypes();
int RoomTypeCallback(void *data, int columns, char **values,
                      char **column_names);

#endif