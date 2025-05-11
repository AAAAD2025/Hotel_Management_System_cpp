# Hotel Management System - Installation Guide

## Required Files

Make sure you have all these files in the same directory:

-   `main.exe`
-   `sqlite3.dll`
-   `libgcc_s_seh-1.dll`
-   `libstdc++-6.dll`
-   `hotel_database.sqlite3`

## Prerequisites

1. System Requirements:
    - Windows 7 or later
    - At least 4GB RAM
    - 100MB free disk space

## Installation Steps

1. Create a new folder where you want to install the application
2. Copy all the required files listed above into this folder
3. Double-click `main.exe` to run the program

## Troubleshooting

If you encounter any of these errors:

1. "libgcc_s_seh-1.dll" or "libstdc++-6.dll" is missing:

    - Make sure both DLL files are in the same directory as main.exe
    - If problems persist, download and install MinGW-w64 from: https://winlibs.com/
    - After installation, copy both libgcc_s_seh-1.dll and libstdc++-6.dll from MinGW's bin directory to your application folder

2. "sqlite3.dll is missing":

    - Ensure sqlite3.dll is in the same directory as main.exe

3. "Database error":
    - Verify that hotel_database.sqlite3 is present in the same directory
    - Check if you have write permissions in the folder

For any other issues, please contact the developer.
