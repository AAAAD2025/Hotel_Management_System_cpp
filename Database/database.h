#ifndef HOTEL_DATABASE_H
#define HOTEL_DATABASE_H

#include "sqlite3.h"
#include <iostream>
#include <string>
using namespace std;

bool connectToDatabase();
bool createTables();
bool executeQuery(const string& query, int (*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
bool getObject(const string& query, int (*callback)(void*, int, char**, char**), void* data);
bool getObjects(const string& query, int (*callback)(void*, int, char**, char**), void* data);
bool insertObject(const string& query, const string& tableName, int (*callback)(void*, int, char**, char**), void* data);
bool deleteObject(const string& query);
bool updateObject(const string& query);
void closeDatabase();
void exitProgram();

#endif // HOTEL_DATABASE_H
