#include "authentication.h"

bool signUp() {
    showInfo("Signing Up... ");
    if(current_user.isCustomer){
        Customer new_customer = addCustomer();
        if(new_customer.customer_id == -1){
            return false;
        }
        current_user.customer_id = new_customer.customer_id;
        return true;
    }

    return false;
}



bool logIn() {
    string email, password;

    while (true) {
        showInfo("Logging in...");
        cleanInput();
        cout << "Email: "; getline(cin, email);
        cout << "Password: "; getline(cin, password);

        if (isEmpty(email) || isEmpty(password)) {
            showError("Empty fields detected. Please fill all fields correctly");
            continue;
        }

        if (current_user.isCustomer) {
            for (const Customer& c : customers) {
                if (c.email == email && c.password == password) {
                    showSuccess("Successfully logged in as Customer");
                    current_user.customer_id = c.customer_id;
                    return true;
                }
            }
        }
        else {
            for (const Staff& s : staffs) {
                if (s.email == email && s.password == password) {
                    if(s.role == "Admin"){
                        showSuccess("Successfully logged in as Admin Staff");
                        current_user.isAdmin = true;
                    }
                    else{
                        showSuccess("Successfully logged in as Staff!");
                    }
                    current_user.staff_id = s.staff_id;
                    return true;
                }
            }
        }

        showWarning("Email or password doesn't match!");
        showWarning("If you don't have an account, please sign up");
        return false;
    }
}




void logOut(void (*startProgram)()) {
    showInfo("Logging out...");
    current_user.isStaff = false;
    current_user.isCustomer = false;
    current_user.isAdmin = false;
    current_user.customer_id = -1;
    current_user.staff_id = -1;
    showSuccess("Logged Out successfully");
    if (startProgram) {
        startProgram();
    }
}
