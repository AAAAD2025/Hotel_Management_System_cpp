-- Sqlite table creation queries

DROP TABLE IF EXISTS Customers;
CREATE TABLE Customers (
    customer_id INTEGER PRIMARY KEY, -- Auto-increment by default
    name TEXT NOT NULL,
    email TEXT NOT NULL,
    password TEXT NOT NULL,
    phone_number TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE IF EXISTS Staff;
CREATE TABLE Staff (
    staff_id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    role TEXT NOT NULL,
    phone_number TEXT NOT NULL,
    email TEXT NOT NULL,
    password TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE IF EXISTS RoomTypes;
CREATE TABLE RoomTypes (
    room_type_id INTEGER PRIMARY KEY,
    type_name TEXT NOT NULL UNIQUE,
    price REAL NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE IF EXISTS Rooms;
CREATE TABLE Rooms (
    room_id INTEGER PRIMARY KEY,
    room_number INTEGER NOT NULL UNIQUE,
    room_type_id INTEGER NOT NULL,
    is_available INTEGER DEFAULT 1, -- Use 0/1 for boolean
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (room_type_id) REFERENCES RoomTypes(room_type_id) ON DELETE RESTRICT
);

DROP TABLE IF EXISTS Bookings;
CREATE TABLE Bookings (
    booking_id INTEGER PRIMARY KEY,
    customer_id INTEGER NOT NULL,
    room_id INTEGER NOT NULL,
    staff_id INTEGER,
    check_in DATE NOT NULL,
    check_out DATE NOT NULL,
    booking_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id) ON DELETE CASCADE,
    FOREIGN KEY (room_id) REFERENCES Rooms(room_id) ON DELETE CASCADE,
    FOREIGN KEY (staff_id) REFERENCES Staff(staff_id) ON DELETE SET NULL,
    UNIQUE (room_id, check_in)
);

DROP TABLE IF EXISTS Payments;
CREATE TABLE Payments (
    payment_id INTEGER PRIMARY KEY,
    booking_id INTEGER NOT NULL,
    amount REAL NOT NULL,
    payment_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (booking_id) REFERENCES Bookings(booking_id) ON DELETE CASCADE
);