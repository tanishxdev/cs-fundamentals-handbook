#include <iostream>
#include <string>
using namespace std;

/*
 DatabaseConnection class WITHOUT Singleton.
 Every time an object is created, a new connection is established.
*/
class DatabaseConnection {
private:
    string connectionString;

public:
    // Public constructor allows unlimited object creation
    DatabaseConnection() {
        connectionString = "Server=127.0.0.1;User=root;Password=1234";
        cout << "New Database Connection Created!" << endl;
    }

    void query(string sql) {
        cout << "Executing SQL: " << sql << endl;
    }
};

/*
 Simulating different services in the application
 Each service creates its own DatabaseConnection object.
*/

// User Service
void userService() {
    DatabaseConnection db;
    db.query("SELECT * FROM users");
}

// Order Service
void orderService() {
    DatabaseConnection db;
    db.query("SELECT * FROM orders");
}

// Logging Service
void logService() {
    DatabaseConnection db;
    db.query("INSERT INTO logs VALUES ('User logged in')");
}

int main() {

    userService();
    orderService();
    logService();

    return 0;
}
