

# **Sleeping Barber Problem (Process Synchronization)**

---

## 1. Introduction

The **Sleeping Barber Problem** is a **classical synchronization problem** used to explain:

* Process coordination
* Mutual exclusion
* Blocking and waking mechanisms

It models a **service system** where a single service provider (barber) serves multiple clients (customers) using a **limited waiting area**.

This problem is important because it combines **Producer–Consumer behavior**, **conditional waiting**, and **fairness** in one model.

---

## 2. Why This Problem Exists

In real systems:

* Tasks arrive **asynchronously**
* Resources are **limited**
* Some tasks must **wait**, while others may be **rejected**

Without proper synchronization:

* Multiple customers may access the barber chair
* Barber may work when no customer exists
* Customers may wait forever or corrupt shared state

---

## 3. Problem Statement

![](https://media.geeksforgeeks.org/wp-content/uploads/20250903103327460003/dining_philospher-problem-image.png)

The barbershop has:

1. **One barber**
2. **One barber chair**
3. **N waiting chairs**

Rules:

1. If no customers are present, the barber **sleeps**
2. If a customer arrives:

   * Wakes the barber if he is sleeping
   * Waits if a waiting chair is available
   * Leaves if no chair is free
3. Only **one customer** can sit in the barber chair at a time

---

## 4. Core Synchronization Challenges

The solution must ensure:

* Mutual exclusion for shared data (chairs)
* Proper coordination between barber and customers
* No deadlock
* Correct sleeping and waking behavior

---

## 5. Synchronization Tools Used

We use **three semaphores** and one shared variable.

---

### 5.1 `Customers` Semaphore

* Counting semaphore
* Tracks number of waiting customers
* Barber waits on this semaphore

```
Customers = 0
```

---

### 5.2 `Barber` Semaphore

* Binary semaphore
* Used by barber to signal readiness
* Customers wait on this semaphore

```
Barber = 0
```

---

### 5.3 `Seats` Semaphore (Mutex)

* Binary semaphore
* Protects access to waiting chairs

```
Seats = 1
```

---

### 5.4 `FreeSeats`

* Integer variable
* Tracks number of available waiting chairs

```
FreeSeats = N
```

---

## 6. Barber Process Logic

![](https://media.geeksforgeeks.org/wp-content/uploads/20250903103327726780/dining_philospher-problem-flowchart.png)
---

### Barber Pseudocode

```c
Barber {
    while (true) {
        down(Customers);     // sleep if no customers
        down(Seats);         // lock seats
        FreeSeats++;         // customer moves to barber chair
        up(Barber);          // barber ready
        up(Seats);           // unlock seats

        // cut hair
    }
}
```

---

### Barber Logic Explained

1. `down(Customers)`

   * Barber sleeps if no customers
2. `down(Seats)`

   * Protects shared chair count
3. `FreeSeats++`

   * Waiting chair becomes free
4. `up(Barber)`

   * Signals customer to sit in chair
5. Barber cuts hair

---

## 7. Customer Process Logic

---

### Customer Pseudocode

```c
Customer {
    down(Seats);
    if (FreeSeats > 0) {
        FreeSeats--;          // take a waiting chair
        up(Customers);        // notify barber
        up(Seats);            // unlock seats
        down(Barber);         // wait for barber
        // get haircut
    } else {
        up(Seats);            // leave if no seat
    }
}
```

---

### Customer Logic Explained

1. Locks `Seats` to safely check chairs
2. If chair available:

   * Sits down
   * Signals barber
   * Waits for barber
3. If no chair:

   * Leaves immediately

### Here's the code implementation of the Sleeping Barber Problem using semaphores:

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
std::vector<int> waiting;
const int NUM_CHAIRS = 3;

void barber() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Barber is sleeping..." << std::endl;
        cv.wait(lock, []{ return !waiting.empty(); });
        int cust = waiting.front();
        waiting.erase(waiting.begin());
        std::cout << "Barber cutting hair of customer " << cust << std::endl;
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1));
        std::cout << "Barber finished with customer " << cust << std::endl;
        lock.lock();
        cv.notify_one();
    }
}

void customer(int i) {
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 4 + 1));
    std::unique_lock<std::mutex> lock(mtx);
    if (waiting.size() < NUM_CHAIRS) {
        waiting.push_back(i);
        std::cout << "Customer " << i << " waiting" << std::endl;
        lock.unlock();
        cv.notify_one();
        lock.lock();
        cv.wait(lock, []{ return waiting.front() != i; });
        std::cout << "Customer " << i << " got haircut" << std::endl;
    } else {
        std::cout << "Customer " << i << " left (no seat)" << std::endl;
    }
}

int main() {
    std::thread t1(barber);
    for (int i = 0; i < 5; ++i) {
        std::thread t(customer, i);
        t.detach();
    }
    t1.join();
    return 0;

```
---

## 8. Why This Solution Works

---

### Mutual Exclusion

* `Seats` semaphore ensures only one process updates `FreeSeats`

---

### No Busy Waiting

* Barber sleeps on `Customers`
* Customers sleep on `Barber`
* CPU is not wasted

---

### Correct Coordination

* Barber works **only when customers exist**
* Customers get served **one at a time**

---

## 9. Relation to Producer–Consumer Problem

| Producer–Consumer | Sleeping Barber |
| ----------------- | --------------- |
| Producer          | Customer        |
| Consumer          | Barber          |
| Buffer            | Waiting chairs  |
| Full/Empty        | Seats count     |

Sleeping Barber is a **specialized producer–consumer problem with rejection**.

---

## 10. Common Interview Doubts

---

### Q1. Is this busy waiting?

**No.**

* Threads block using semaphores
* CPU is released until signaled

---

### Q2. What happens if `Seats` mutex is removed?

* Multiple customers may:

  * Sit on same chair
  * Corrupt `FreeSeats`
* Leads to race conditions

---

### Q3. Can starvation occur?

* Starvation is **reduced**
* But complete fairness depends on scheduling policy

---

## 11. Properties of Sleeping Barber Solution

| Property         | Status          |
| ---------------- | --------------- |
| Mutual Exclusion | Yes             |
| Deadlock         | No              |
| Busy Waiting     | No              |
| Starvation       | Possible (rare) |
| Fairness         | Partial         |

---

## 12. Interview Questions

### Basic

1. What is the Sleeping Barber Problem?
2. What does it model?
3. Why does the barber sleep?

---

### Conceptual

1. Role of `Customers` semaphore?
2. Why do customers wait on `Barber`?
3. How is deadlock avoided?

---

### Tricky

1. Is Sleeping Barber a real OS problem?
   → No, it is a conceptual model.

2. Is it a producer–consumer problem?
   → Yes, with limited buffer and rejection.

---

## 13. Key Takeaways

* Sleeping Barber models **service synchronization**
* Uses semaphores for:

  * Coordination
  * Mutual exclusion
  * Blocking instead of spinning
* Demonstrates **sleep–wake behavior**
* Important for understanding real scheduling systems

> **Sleeping Barber teaches how to design systems that wait efficiently instead of wasting CPU.**
