#include "messages.h"
#include <iomanip>
#include <iostream>

void showSuccess(string message) {
    cout << "\n\n" << SUCCESS << message << RESET << "\n\n";
}

void showError(string message) {
    cout << "\n\n" << ERROR << message << RESET << "\n\n";
}

void showInfo(string message) {
    cout << "\n\n" << INFO << message << RESET << "\n\n";
}

void showWarning(string message) {
    cout << "\n\n" << WARNING << message << RESET << "\n\n";
}

void showHighlight(string message) {
    cout << "\n\n" << HIGHLIGHT << message << RESET << "\n\n";
}