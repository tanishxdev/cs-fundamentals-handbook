# Flight Booking System | MakeMyTrip | Airlines

### **1. Functional and Non-Functional Requirements**

#### **Functional Requirements**
These define what the flight booking system must do:
- **User Login**: Users should be able to log in to provide personal details (e.g., name, email, date of birth, gender).
- **Flight Search**: Users can search for flights based on:
  - Source and destination locations.
  - Travel date.
- **Flight Selection**: Users can select a flight based on preferences like time or cost.
- **Booking**: Users can input personal details and book a flight.
- **Payment Processing**: The system must integrate a payment gateway to confirm bookings.
- **Notification**: After a successful booking, users receive a confirmation email with details like flight information and PNR number.

#### **Non-Functional Requirements**
These ensure the system is robust and scalable:
- **Scalability**: The system should handle high traffic (e.g., thousands of concurrent users).
- **Reliability**: The system must be dependable, ensuring minimal downtime and accurate booking data.
- **Modularity**: The design should allow easy enhancements for future requirements.
- **Maintainability**: Code and components should be organized for easy updates and debugging.

---

### **2. Actors**
The primary actors interacting with the system are:
1. **Customer**: Books flights, searches for flights, and makes payments.
2. **Airline Authority**: Registers flights and manages schedules.
3. **Admin**: Manages flight details, such as adding or updating flight schedules.

---

### **3. Core Entities**
The design revolves around the following key entities, each with specific attributes and relationships:

1. **Flight**:
   - **Attributes**:
     - Flight Number (unique identifier).
     - Airline (reference to the Airline entity).
     - Seat Capacity (e.g., 90 for small flights, 150 for larger ones).
     - Seats (a list of Seat objects, representing individual seats).
   - **Purpose**: Represents a specific flight operated by an airline.

2. **Airline**:
   - **Attributes**:
     - Name (e.g., Indigo, AirAsia).
     - Flights (list of Flight objects associated with the airline).
   - **Purpose**: Manages the collection of flights operated by a specific airline.

3. **Seat**:
   - **Attributes**:
     - Seat Number (e.g., 15F).
     - Class Type (e.g., Economy, Business; implemented as a string or enum).
   - **Purpose**: Defines individual seats within a flight, categorized by class.

4. **Schedule**:
   - **Attributes**:
     - Flight (reference to the Flight entity).
     - Source Airport (reference to Airport entity).
     - Destination Airport (reference to Airport entity).
     - Start Time (timestamp for departure).
     - End Time (timestamp for arrival).
     - Status (enum: On Time, Delayed, Canceled).
   - **Purpose**: Represents a specific instance of a flight’s journey (e.g., Flight 101 from Lucknow to Bangalore on Tuesday at 6 PM).

5. **FlightSeat** (extends Seat):
   - **Attributes**:
     - Flight Number (inherited from Flight).
     - Class Type (inherited from Seat).
     - Price (e.g., 7,000 INR for a specific seat on a specific schedule).
     - Status (enum: Open, Booked).
   - **Purpose**: Captures seat-specific details for a particular flight schedule, including pricing and availability.

6. **Airport**:
   - **Attributes**:
     - Name (e.g., Delhi International Airport).
     - Location (e.g., city or coordinates).
     - Flights (list of Flight objects associated with the airport).
   - **Purpose**: Represents the starting and ending points of a flight’s schedule.

7. **User**:
   - **Attributes**:
     - Name.
     - Email ID.
     - Date of Birth.
     - Gender.
   - **Purpose**: Represents a customer who books flights.

8. **Booking Details**:
   - **Attributes**:
     - Flight Details (reference to Flight and Schedule).
     - User Details (reference to User).
     - Source and Destination.
     - Travel Date.
     - PNR Number (unique booking identifier).
   - **Purpose**: Stores metadata for a confirmed booking, used for notifications.

9. **Flight Booking System** (Core Class):
   - **Attributes**:
     - Users (list of User objects).
     - Flights (list of Flight objects).
   - **Methods**:
     - `getFlightDetails(source, destination, date)`: Searches for flights based on user input.
     - `bookFlight(flightDetails, userDetails)`: Books a flight for a user.
     - `confirmBooking(bookingDetails)`: Sends a confirmation notification to the user.
   - **Purpose**: The central class that orchestrates flight searches, bookings, and confirmations.

10. **Payment Module** (High-Level):
    - Handles payment processing via a gateway.
    - Not detailed in the design but noted as a separate system.

11. **Notification Module** (High-Level):
    - Sends confirmation emails to users after booking.
    - Not detailed but noted as a separate system.

---

### **4. Low-Level Design Approach**

The LLD follows a modular, object-oriented design with clear separation of concerns. Here’s how the entities interact:

- **Flight Booking Workflow**:
  1. A **User** logs into the **Flight Booking System**.
  2. The user calls `getFlightDetails(source, destination, date)` to search for flights. This queries the **Schedule** and **Flight** entities to return matching flights.
  3. The user selects a flight and a seat (via **FlightSeat**), which checks availability (status = Open).
  4. The user provides personal details and initiates `bookFlight(flightDetails, userDetails)`, creating a **Booking Details** object.
  5. The system processes payment (via the **Payment Module**).
  6. Upon successful payment, `confirmBooking(bookingDetails)` triggers the **Notification Module** to send a confirmation email.
  7. The **FlightSeat** status is updated to Booked.

- **Entity Relationships**:
  - **Flight** has a reference to **Airline** and a list of **Seats**.
  - **Schedule** references a **Flight** and two **Airports** (source and destination).
  - **FlightSeat** extends **Seat** and adds pricing and booking status.
  - **Booking Details** links a **User**, **Flight**, and **Schedule**.
  - **Flight Booking System** orchestrates interactions among all entities.

- **Modularity**:
  - Each entity (e.g., **Flight**, **User**, **Schedule**) is a separate class, making the system extensible.
  - The **Payment** and **Notification** modules are treated as external systems to keep the core design focused.

---

### **5. Practice Tips for a Technical Interview**

When tackling an LLD question like this in an interview, follow these steps to demonstrate clarity and structure:

1. **Clarify Requirements**:
   - Ask the interviewer about functional requirements (e.g., “Should users be able to cancel bookings?”).
   - Confirm non-functional requirements (e.g., “Is high availability critical?”).
   - Example: “Does the system need to support multiple airlines or international flights?”

2. **Identify Actors and Entities**:
   - List actors (Customer, Airline Authority, Admin).
   - Define core entities (Flight, Schedule, User, etc.) and their attributes.
   - Use a whiteboard or paper to sketch relationships (e.g., Flight → Schedule → Airport).

3. **Design Iteratively**:
   - Start with the core entity (e.g., **Flight**) and expand to related entities (e.g., **Airline**, **Schedule**).
   - Break down complex entities (e.g., separate **Seat** and **FlightSeat** for pricing and status).
   - Validate with the interviewer: “Does it make sense to separate seat pricing into a FlightSeat class?”

4. **Define the Core System**:
   - Create a central class like **Flight Booking System** to handle key operations (search, book, confirm).
   - Outline method signatures and inputs/outputs (e.g., `getFlightDetails(source, destination, date)`).

5. **Address Non-Functional Requirements**:
   - **Scalability**: Suggest using a database (e.g., MySQL for relational data, Redis for caching flight availability).
   - **Reliability**: Mention transaction management for bookings to ensure consistency.
   - **Modularity**: Emphasize separate classes for extensibility (e.g., adding a **Cancellation** module later).

6. **Communicate Clearly**:
   - Explain your thought process: “I’m defining a Schedule class because a flight can have multiple routes on different days.”
   - Draw diagrams to show relationships (e.g., UML class diagram with Flight, Schedule, and User).
   - Confirm with the interviewer: “Are we focusing only on booking, or should I include cancellation and refunds?”

7. **Handle Edge Cases**:
   - Discuss scenarios like flight delays, seat conflicts, or failed payments.
   - Example: “If two users try to book the same seat, we can use optimistic locking to prevent double-booking.”

8. **Keep It Simple**:
   - Avoid overcomplicating (e.g., don’t design the full payment system unless asked).
   - Focus on the core workflow (search → select → book → pay → notify).

9. **Practice UML Diagrams**:
   - Prepare to draw a class diagram showing entities, attributes, and relationships.
   - Example:
     ```
     [Flight] ----> [Airline]
       | 1
       | *
     [Schedule] ----> [Airport]
       | 1
       | *
     [FlightSeat] ----> [Seat]
     ```

10. **Prepare for Follow-Ups**:
    - Be ready for questions like:
      - “How would you handle a booking cancellation?”
      - “How do you ensure the system scales for 1 million users?”
      - “What if the payment fails after reserving a seat?”

---

### **6. Sample UML Class Diagram**

Below is a simplified representation of the class relationships (not a chart, as no numerical data is provided):

```
[Flight]
- flightNumber: String
- airline: Airline
- seatCapacity: int
- seats: List<Seat>
+ getFlightDetails()

[Airline]
- name: String
- flights: List<Flight>

[Seat]
- seatNumber: String
- classType: String (or Enum)

[FlightSeat]
- price: double
- status: Enum (Open, Booked)
+ extends Seat

[Schedule]
- flight: Flight
- source: Airport
- destination: Airport
- startTime: Timestamp
- endTime: Timestamp
- status: Enum (OnTime, Delayed, Canceled)

[Airport]
- name: String
- location: String
- flights: List<Flight>

[User]
- name: String
- email: String
- dateOfBirth: Date
- gender: String

[BookingDetails]
- flight: Flight
- schedule: Schedule
- user: User
- source: String
- destination: String
- travelDate: Date
- pnrNumber: String

[FlightBookingSystem]
- users: List<User>
- flights: List<Flight>
+ getFlightDetails(source, destination, date)
+ bookFlight(flightDetails, userDetails)
+ confirmBooking(bookingDetails)
```

---

### **7. Notes on Payment and Notification Modules**
- **Payment Module**: Assumed to be an external system. In an interview, mention that it would involve APIs for payment gateways (e.g., Stripe, PayPal) and focus on integration points (e.g., passing booking details and handling success/failure).
- **Notification Module**: Also external. Highlight that it sends emails/SMS with booking details (e.g., using AWS SES or SendGrid).

---

### **8. Practice Questions to Extend the Design**
To prepare further, consider these extensions:
1. Add a **Cancellation** feature: How would you update the **FlightSeat** status and notify the user?
2. Support **Multi-City Flights**: How would you modify the **Schedule** class?
3. Handle **Concurrency**: How do you prevent two users from booking the same seat?
4. Add **Discounts**: How would you incorporate dynamic pricing or promo codes?

---
