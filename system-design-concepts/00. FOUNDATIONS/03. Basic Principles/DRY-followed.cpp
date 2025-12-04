#include <iostream>
#include <string>
using namespace std;

// Common reusable function (Single source of truth)
bool validateEmail(const string& email) {
    if (email.find("@") == string::npos || email.find(".") == string::npos) {
        return false;
    }
    return true;
}

bool loginUser(string email, string password) {
    if (!validateEmail(email)) {
        cout << "Invalid email!" << endl;
        return false;
    }
    cout << "User logged in successfully." << endl;
    return true;
}

bool registerUser(string email, string password) {
    if (!validateEmail(email)) {
        cout << "Invalid email!" << endl;
        return false;
    }
    cout << "User registered successfully." << endl;
    return true;
}

int main() {
    loginUser("sid@abc.com", "1234");
    registerUser("hazra.com", "5678");
    return 0;
}
