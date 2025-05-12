#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include <iostream>
using namespace std;

const string RESET = "\033[0m";
const string SUCCESS = "\033[1;32m";  // Bold Green
const string ERROR = "\033[1;31m";    // Bold Red
const string INFO = "\033[1;34m";     // Bold Blue
const string WARNING = "\033[1;33m";  // Bold Yellow
const string HIGHLIGHT = "\033[1;36m"; // Bold Cyan

// Message display functions
void showSuccess(string message);
void showError(string message);
void showInfo(string message);
void showWarning(string message);
void showHighlight(string message);

#endif // MESSAGES_H 