# Team Members:
- Abel Mekonen ---------------------------- ETS 0038/16 (Team Leader)
- Amira Abdurahman ---------------------- ETS 0170/16 (Vice Leader)
- Abel Birhane ------------------------------ ETS 0034/16 
- Abraham Teramed  ------------------------ ETS 0094/16
- Daniel Gashaw ---------------------------- ETS 0387/16 

---


# Hotel Management System

A comprehensive C++ console application for hotel management with SQLite database integration.

## Overview

The Hotel Management System is a modular C++ application designed to manage hotel operations including customer management, room bookings, staff administration, and payment processing. The system uses SQLite3 for persistent data storage and implements a clean separation between data structures, business logic, and user interface components.

## System Architecture

### Database Structure

The system uses SQLite3 with the following relational schema:

- **Customers**: Stores customer profiles (ID, name, email, password, phone)
- **Staff**: Manages staff members (ID, name, role, phone, email, password)
- **RoomTypes**: Defines room categories (ID, type name, price)
- **Rooms**: Tracks individual rooms (ID, room number, type ID, availability)
- **Bookings**: Records reservations (ID, customer ID, room ID, staff ID, check-in/out dates)
- **Payments**: Logs financial transactions (ID, booking ID, amount, date)

### C++ Data Structures

The application uses C++ structs that mirror the database tables:

```cpp
struct Customer { int customer_id; string name, email, password, phone_number; }
struct Staff { int staff_id; string name, role, email, password, phone_number; }
struct RoomType { int room_type_id; string type_name; float price; }
struct Room { int room_id, room_number, room_type_id; bool is_available; }
struct Booking { int booking_id, customer_id, room_id, staff_id; string check_in, check_out; }
struct Payment { int payment_id, booking_id; float amount; string payment_date; }
```

These structures facilitate seamless data transfer between the database and application memory.

## Core Functionalities

### Authentication System
- Secure login for customers and staff
- Role-based access control (customer vs. staff permissions)
- User registration with basic validation

### Customer Management
- Customer profile creation and management
- Customer search functionality
- Profile viewing and editing

### Room Management
- Room inventory tracking
- Room categorization by types and pricing
- Room availability monitoring

### Booking System
- Room reservation processing
- Check-in/check-out management
- Booking history tracking

### Payment Processing
- Payment recording and tracking
- Payment history maintenance

### Staff Management
- Staff information management
- Staff role assignment

## Technical Implementation

### Code Organization
- **Auth/**: Authentication related code
- **Components/**: Core system components (Customer, Room, Booking, etc.)
- **Database/**: Database operations and SQLite integration
- **Features/**: User interface and menu systems
- **Structures/**: Data structure definitions

### User Interface
- Console-based menu system
- Role-specific menus for customers and staff
- Clear navigation and error handling


### Installation Steps
1. Double-click `main.exe` to run the program

## Troubleshooting

If you encounter any of these errors:

1. "sqlite3.dll is missing":
   - Ensure sqlite3.dll is in the same directory as main.exe

2. "Database error":
   - Verify that hotel_database.sqlite3 is present in the same directory
   - Check if you have write permissions in the folder

## Development

### Build Instructions
The project can be built using g++ with the following command:
```
g++ main.cpp Structures/structures.cpp Features/Messages/messages.cpp Features/menus.cpp Auth/authentication.cpp Database/database.cpp Components/Customer/customer.cpp Components/Payment/payment.cpp Components/Staff/staff.cpp Components/Room/room.cpp Components/Room/roomtypes.cpp Components/Booking/booking.cpp -o main.exe -I. -IDatabase/sqlite3 -LDatabase -lsqlite3
```

### Development Environment
- C++ programming language
- SQLite3 database
- MinGW-w64 compiler
- Visual Studio Code IDE
