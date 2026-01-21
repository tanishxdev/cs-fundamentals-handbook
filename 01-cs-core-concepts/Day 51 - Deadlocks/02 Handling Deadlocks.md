

# **Handling Deadlocks in Operating Systems**

---

## 1. Introduction

Once we understand **what a deadlock is** and **why it occurs**, the next logical question is:

> **How does an operating system handle deadlocks?**

Deadlocks are dangerous because:

* Processes remain blocked forever
* Resources are wasted
* System reliability is affected

To deal with this, operating systems follow **four fundamental strategies**.

---

## 2. Four Methods of Handling Deadlocks

![](https://media.geeksforgeeks.org/wp-content/uploads/20250903112419136580/methods_of_handling_deadlocks.webp)
An OS can handle deadlocks using **one of the following approaches**:

1. **Deadlock Prevention**
2. **Deadlock Avoidance**
3. **Deadlock Detection and Recovery**
4. **Deadlock Ignorance (Ostrich Algorithm)**

Each approach has **different trade-offs** in terms of:

* Performance
* Complexity
* Resource utilization

---

## 3. Deadlock Prevention

---

## 3.1 Core Idea

Deadlock Prevention works by **ensuring that at least one of the four necessary conditions for deadlock never holds**.

If even **one condition is broken**, deadlock becomes **impossible**.

---

## 3.2 Which Conditions Can Be Broken?

The four necessary conditions are:

1. Mutual Exclusion
2. Hold and Wait
3. No Preemption
4. Circular Wait

Prevention attacks **one or more** of these.

---

## 3.3 Examples of Prevention

### Breaking Hold and Wait

* Force processes to **request all required resources at once**
* Or release all resources before requesting new ones

**Problem:** Low resource utilization

---

### Breaking No Preemption

* If a process requests a resource and it is unavailable:

  * Force the process to release its held resources

**Problem:** Not feasible for non-preemptible resources (e.g., mutex)

---

### Breaking Circular Wait

* Impose a **strict ordering of resources**
* Processes must request resources only in increasing order

**Problem:** Difficult to design and inflexible

---

## 3.4 Characteristics of Deadlock Prevention

| Aspect               | Description          |
| -------------------- | -------------------- |
| Deadlock             | Completely prevented |
| Resource Utilization | Poor                 |
| Flexibility          | Low                  |
| Practical Use        | Limited              |

---

## 4. Deadlock Avoidance

---

## 4.1 Core Idea

Deadlock Avoidance allows deadlock conditions to exist, but **carefully avoids unsafe states**.

Before granting a resource request, the OS checks:

> “Will this allocation keep the system in a **safe state**?”

If not, the request is **denied or delayed**.

---

## 4.2 Safe vs Unsafe State (Intuition)

* **Safe State**: There exists some order in which all processes can finish
* **Unsafe State**: No such guarantee exists (deadlock may occur)

Avoidance ensures the system **never enters an unsafe state**.

---

## 4.3 Algorithms Used

### Banker’s Algorithm

* Used when **multiple instances** of resources exist
* Simulates allocation
* Checks for safe sequence

---

### Resource Allocation Graph (RAG)

* Used when **single instance** of each resource exists
* Detects cycles before allocation

---

## 4.4 Characteristics of Deadlock Avoidance

| Aspect             | Description              |
| ------------------ | ------------------------ |
| Deadlock           | Avoided                  |
| Overhead           | High                     |
| Resource Knowledge | Must be known in advance |
| Practical Use      | Moderate                 |

---

## 5. Deadlock Detection and Recovery

---

## 5.1 Core Idea

This approach **does not prevent or avoid deadlock**.

Instead, the OS:

1. Allows deadlock to occur
2. Periodically **checks for deadlock**
3. **Recovers** from it when detected

---

## 5.2 Deadlock Detection

* OS examines:

  * Wait-for graphs
  * Resource allocation states
* Detects cycles

Detection may run:

* Periodically
* When resource utilization drops

---

## 5.3 Deadlock Recovery Techniques

### Process Termination

* Abort one or more deadlocked processes
* Release their resources

**Downside:** Loss of computation

---

### Resource Preemption

* Temporarily take resources from some processes
* Reassign to others

**Downside:** Rollback complexity, starvation risk

---

## 5.4 Characteristics of Detection & Recovery

| Aspect        | Description          |
| ------------- | -------------------- |
| Deadlock      | Allowed              |
| Overhead      | Medium               |
| Data Loss     | Possible             |
| Practical Use | Common in DB systems |

---

## 6. Deadlock Ignorance (Ostrich Algorithm)

---

## 6.1 Core Idea

The OS **ignores deadlock completely**, assuming:

> “Deadlocks are rare. Handling them costs more than restarting.”

If a deadlock occurs:

* System is rebooted
* All processes restart

This is called the **Ostrich Algorithm**.

---

## 6.2 Why Is It Called Ostrich Algorithm?

Like an ostrich hiding its head in sand:

* The OS pretends the problem does not exist

---

## 6.3 Where Is This Used?

* General-purpose operating systems
* Systems where deadlocks are rare
* Example:

  * UNIX
  * Windows

---

## 6.4 Characteristics of Deadlock Ignorance

| Aspect        | Description   |
| ------------- | ------------- |
| Deadlock      | Ignored       |
| Overhead      | Very low      |
| Recovery      | System reboot |
| Practical Use | Very common   |

---

## 7. Comparison of Deadlock Handling Methods

| Method               | Deadlock Occurrence | Overhead | Resource Utilization |
| -------------------- | ------------------- | -------- | -------------------- |
| Prevention           | Never               | High     | Poor                 |
| Avoidance            | Never               | High     | Moderate             |
| Detection & Recovery | Yes                 | Medium   | Good                 |
| Ignorance            | Yes                 | Low      | Excellent            |

---

## 8. Which Method Is Best?

There is **no universally best method**.

Choice depends on:

* Type of system
* Frequency of deadlock
* Cost of recovery
* Performance requirements

---

## 9. Interview Questions

### Basic

1. What are the four deadlock handling methods?
2. Which method is used by most OS?
3. What is deadlock avoidance?

---

### Conceptual

1. Difference between prevention and avoidance?
2. What is an unsafe state?
3. Why is deadlock ignorance acceptable?

---

### Tricky

1. Do Windows and UNIX handle deadlocks?
   → Mostly ignore them.

2. Is deadlock detection always running?
   → No, it is periodic.

---

## 10. Key Takeaways

* Deadlock handling is a **design decision**
* Four approaches exist:

  * Prevent
  * Avoid
  * Detect & Recover
  * Ignore
* Most general-purpose OS **ignore deadlocks**
* Advanced systems use **avoidance or detection**

> **Deadlock handling balances correctness, performance, and practicality.**
