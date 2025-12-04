#include <string>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

// Enum for Seat Class Type (Economy, Business)
enum class SeatClass {
    ECONOMY,
    BUSINESS
};

// Enum for Flight Schedule Status (OnTime, Delayed, Canceled)
enum class ScheduleStatus {
    ON_TIME,
    DELAYED,
    CANCELED
};

// Enum for FlightSeat Status (Open, Booked)
enum class SeatStatus {
    OPEN,
    BOOKED
};

// Airport class to represent an airport entity
class Airport {
private:
    string name;           // Name of the airport (e.g., Delhi International)
    string location;       // Location of the airport (e.g., Delhi)
    vector<string> flights; // List of flight numbers associated with the airport

public:
    // Constructor
    Airport(string name, string location) : name(name), location(location) {}

    // Getters
    string getName() const { return name; }
    string getLocation() const { return location; }
    const vector<string>& getFlights() const { return flights; }

    // Add a flight to the airport
    void addFlight(const string& flightNumber) {
        flights.push_back(flightNumber);
    }
};

// Seat class to represent a seat in a flight
class Seat {
private:
    string seatNumber;     // Seat number (e.g., 15F)
    SeatClass classType;   // Seat class (Economy or Business)

public:
    // Constructor
    Seat(string seatNumber, SeatClass classType) 
        : seatNumber(seatNumber), classType(classType) {}

    // Getters
    string getSeatNumber() const { return seatNumber; }
    SeatClass getClassType() const { return classType; }
};

// FlightSeat class extends Seat to include pricing and booking status
class FlightSeat : public Seat {
private:
    double price;          // Price of the seat for a specific schedule
    SeatStatus status;     // Booking status (Open or Booked)

public:
    // Constructor
    FlightSeat(string seatNumber, SeatClass classType, double price) 
        : Seat(seatNumber, classType), price(price), status(SeatStatus::OPEN) {}

    // Getters
    double getPrice() const { return price; }
    SeatStatus getStatus() const { return status; }

    // Set booking status
    void setStatus(SeatStatus newStatus) { status = newStatus; }
};

// Airline class to represent an airline entity
class Airline {
private:
    string name;           // Name of the airline (e.g., Indigo)
    vector<string> flights; // List of flight numbers operated by the airline

public:
    // Constructor
    Airline(string name) : name(name) {}

    // Getters
    string getName() const { return name; }
    const vector<string>& getFlights() const { return flights; }

    // Add a flight to the airline
    void addFlight(const string& flightNumber) {
        flights.push_back(flightNumber);
    }
};

// Forward declaration of Flight class to resolve circular dependency
class Flight;

// Schedule class to represent a flight schedule
class Schedule {
private:
    Flight* flight;        // Reference to the associated Flight
    Airport* source;       // Source airport
    Airport* destination;  // Destination airport
    time_t startTime;      // Departure timestamp
    time_t endTime;        // Arrival timestamp
    ScheduleStatus status; // Status of the schedule (OnTime, Delayed, Canceled)

public:
    // Constructor
    Schedule(Flight* flight, Airport* source, Airport* destination, 
             time_t startTime, time_t endTime, ScheduleStatus status) 
        : flight(flight), source(source), destination(destination), 
          startTime(startTime), endTime(endTime), status(status) {}

    // Getters
    Flight* getFlight() const { return flight; }
    Airport* getSource() const { return source; }
    Airport* getDestination() const { return destination; }
    time_t getStartTime() const { return startTime; }
    time_t getEndTime() const { return endTime; }
    ScheduleStatus getStatus() const { return status; }
};

// Flight class to represent a flight entity
class Flight {
private:
    string flightNumber;   // Unique flight number (e.g., IND101)
    Airline* airline;      // Reference to the associated Airline
    int seatCapacity;      // Total number of seats
    vector<FlightSeat*> seats; // List of seats in the flight
    vector<Schedule*> schedules; // List of schedules for the flight

public:
    // Constructor
    Flight(string flightNumber, Airline* airline, int seatCapacity) 
        : flightNumber(flightNumber), airline(airline), seatCapacity(seatCapacity) {
        airline->addFlight(flightNumber); // Register flight with airline
    }

    // Getters
    string getFlightNumber() const { return flightNumber; }
    Airline* getAirline() const { return airline; }
    int getSeatCapacity() const { return seatCapacity; }
    const vector<FlightSeat*>& getSeats() const { return seats; }
    const vector<Schedule*>& getSchedules() const { return schedules; }

    // Add a seat to the flight
    void addSeat(FlightSeat* seat) {
        if (seats.size() < static_cast<size_t>(seatCapacity)) {
            seats.push_back(seat);
        }
    }

    // Add a schedule to the flight
    void addSchedule(Schedule* schedule) {
        schedules.push_back(schedule);
        // Register flight with source and destination airports
        schedule->getSource()->addFlight(flightNumber);
        schedule->getDestination()->addFlight(flightNumber);
    }
};

// User class to represent a customer
class User {
private:
    string name;           // User's name
    string email;          // User's email
    string dateOfBirth;    // User's date of birth
    string gender;         // User's gender

public:
    // Constructor
    User(string name, string email, string dateOfBirth, string gender) 
        : name(name), email(email), dateOfBirth(dateOfBirth), gender(gender) {}

    // Getters
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getDateOfBirth() const { return dateOfBirth; }
    string getGender() const { return gender; }
};

// BookingDetails class to store booking metadata
class BookingDetails {
private:
    Flight* flight;        // Reference to the booked flight
    Schedule* schedule;    // Reference to the booked schedule
    User* user;            // Reference to the user
    string pnrNumber;      // Unique PNR number
    string source;         // Source location
    string destination;    // Destination location
    time_t travelDate;     // Travel date

public:
    // Constructor
    BookingDetails(Flight* flight, Schedule* schedule, User* user, string pnrNumber, 
                   string source, string destination, time_t travelDate) 
        : flight(flight), schedule(schedule), user(user), pnrNumber(pnrNumber), 
          source(source), destination(destination), travelDate(travelDate) {}

    // Getters
    Flight* getFlight() const { return flight; }
    Schedule* getSchedule() const { return schedule; }
    User* getUser() const { return user; }
    string getPnrNumber() const { return pnrNumber; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    time_t getTravelDate() const { return travelDate; }
};

// FlightBookingSystem class to manage the core functionality
class FlightBookingSystem {
private:
    vector<User*> users;   // List of registered users
    vector<Flight*> flights; // List of available flights

public:
    // Constructor
    FlightBookingSystem() {}

    // Add a user to the system
    void addUser(User* user) {
        users.push_back(user);
    }

    // Add a flight to the system
    void addFlight(Flight* flight) {
        flights.push_back(flight);
    }

    // Search for flights based on source, destination, and date
    vector<Schedule*> getFlightDetails(string source, string destination, time_t date) {
        vector<Schedule*> result;
        // Iterate through all flights and their schedules
        for (Flight* flight : flights) {
            for (Schedule* schedule : flight->getSchedules()) {
                // Check if the schedule matches the source, destination, and date
                if (schedule->getSource()->getName() == source &&
                    schedule->getDestination()->getName() == destination &&
                    schedule->getStartTime() >= date &&
                    schedule->getStatus() == ScheduleStatus::ON_TIME) {
                    result.push_back(schedule);
                }
            }
        }
        return result;
    }

    // Book a flight for a user
    BookingDetails* bookFlight(Flight* flight, Schedule* schedule, User* user, FlightSeat* seat) {
        // Check if the seat is available
        if (seat->getStatus() == SeatStatus::OPEN) {
            // Update seat status to booked
            seat->setStatus(SeatStatus::BOOKED);
            // Generate a unique PNR (simplified for demo)
            string pnr = "PNR" + to_string(rand() % 1000000);
            // Create booking details
            return new BookingDetails(flight, schedule, user, pnr, 
                                     schedule->getSource()->getName(), 
                                     schedule->getDestination()->getName(), 
                                     schedule->getStartTime());
        }
        return nullptr; // Booking failed (seat not available)
    }

    // Confirm booking and send notification (simulated)
    void confirmBooking(BookingDetails* booking) {
        // Simulate sending a notification (e.g., email)
        cout << "Booking confirmed! PNR: " << booking->getPnrNumber() 
             << ", User: " << booking->getUser()->getName() 
             << ", Flight: " << booking->getFlight()->getFlightNumber() 
             << ", From: " << booking->getSource() 
             << " To: " << booking->getDestination() << endl;
        // In a real system, this would call the Notification Module
    }
};

// Main function to demonstrate the system
int main() {
    // Create an airline
    Airline* indigo = new Airline("Indigo");

    // Create airports
    Airport* delhi = new Airport("Delhi International", "Delhi");
    Airport* bangalore = new Airport("Bangalore International", "Bangalore");

    // Create a flight
    Flight* flight101 = new Flight("IND101", indigo, 150);

    // Create seats
    FlightSeat* seat1 = new FlightSeat("15F", SeatClass::ECONOMY, 7000.0);
    flight101->addSeat(seat1);

    // Create a schedule
    time_t now = time(nullptr);
    Schedule* schedule1 = new Schedule(flight101, delhi, bangalore, now, now + 7200, ScheduleStatus::ON_TIME);
    flight101->addSchedule(schedule1);

    // Create a user
    User* user1 = new User("John Doe", "john@example.com", "1990-01-01", "Male");

    // Create the flight booking system
    FlightBookingSystem* system = new FlightBookingSystem();
    system->addUser(user1);
    system->addFlight(flight101);

    // Search for flights
    vector<Schedule*> availableFlights = system->getFlightDetails("Delhi International", "Bangalore International", now);
    if (!availableFlights.empty()) {
        cout << "Found " << availableFlights.size() << " flights!" << endl;
        // Book the first available flight
        BookingDetails* booking = system->bookFlight(flight101, availableFlights[0], user1, seat1);
        if (booking) {
            system->confirmBooking(booking);
        } else {
            cout << "Booking failed: Seat not available" << endl;
        }
    } else {
        cout << "No flights found!" << endl;
    }

    return 0;
}