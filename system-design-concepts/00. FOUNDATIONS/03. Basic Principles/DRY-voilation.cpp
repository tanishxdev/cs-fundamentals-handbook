#include <iostream>
#include <string>
using namespace std;

bool loginUser(string email, string password) {
    // Email validation code repeated
    if (email.find("@") == string::npos || email.find(".") == string::npos) {
        cout << "Invalid email!" << endl;
        return false;
    }
    cout << "User logged in successfully." << endl;
    return true;
}

bool registerUser(string email, string password) {
    // Same email validation code repeated again ❌
    if (email.find("@") == string::npos || email.find(".") == string::npos) {
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
