#include <iostream>
#include <string>
using namespace std;

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    string connectionString;

    // Private constructor
    DatabaseConnection() {
        connectionString = "Server=127.0.0.1;User=root;Password=1234";
        cout << "Database Connected!\n";
    }

public:
    static DatabaseConnection* getInstance() {
        if (instance == nullptr)
            instance = new DatabaseConnection();
        return instance;
    }

    void query(string sql) {
        cout << "Executing SQL: " << sql << endl;
    }

    // Prevent copy
    DatabaseConnection(const DatabaseConnection&) = delete;
    void operator=(const DatabaseConnection&) = delete;
};

DatabaseConnection* DatabaseConnection::instance = nullptr;

int main() {
    DatabaseConnection::getInstance()->query("SELECT * FROM users");
    DatabaseConnection::getInstance()->query("INSERT INTO logs VALUES ('login')");
}