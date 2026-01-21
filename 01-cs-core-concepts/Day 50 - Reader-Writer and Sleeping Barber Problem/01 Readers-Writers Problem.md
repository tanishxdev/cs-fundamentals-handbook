
# **Readers–Writers Problem (Process Synchronization)**

---

## 1. Introduction

The **Readers–Writers Problem** is a classical synchronization problem that deals with **concurrent access to shared data**.

Examples of shared data:

* Database
* File system
* Shared memory structure

Different processes may want to **read** or **write** this data at the same time, which leads to synchronization challenges.

---

## 2. Why This Problem Exists

Not all accesses to shared data are the same:

* **Readers** only read data → they do **not modify** it
* **Writers** modify data → concurrent access can corrupt data

So, the OS must allow:

* **Multiple readers simultaneously** (for performance)
* **Only one writer at a time**
* **No reader while a writer is writing**

---

## 3. Problem Statement (Formal Rules)

The synchronization scheme must ensure:

1. Any number of readers can read **simultaneously**
2. Only **one writer** can write at a time
3. While a writer is writing:

   * No reader can read
   * No other writer can write

---

## 4. Core Challenge

The real difficulty is **priority management**:

* Should readers be favored?
* Should writers be favored?
* Or should access be completely fair?

This leads to **different variants** of the problem.

---

## 5. Variants of Readers–Writers Problem

---

## 5.1 Readers-Preference Problem

### Definition

* Readers are given priority
* If a reader arrives and the resource is being read, it is allowed to enter
* Writers may have to wait indefinitely

---

### Consequence

* High read throughput
* **Writer starvation is possible**

---

## 5.2 Writers-Preference Problem

### Definition

* Writers are given priority
* Once a writer is waiting, new readers are blocked
* Writers will not starve

---

### Consequence

* Writers are served quickly
* Readers may starve

---

> Some systems implement **fair solutions**, but here we focus on the classical **readers-preference solution**, as commonly asked in exams.

---

## 6. Readers-Preference: Allowed and Disallowed Cases

| Case | Process 1 | Process 2 | Allowed |
| ---- | --------- | --------- | ------- |
| 1    | Writing   | Writing   | No      |
| 2    | Writing   | Reading   | No      |
| 3    | Reading   | Writing   | No      |
| 4    | Reading   | Reading   | Yes     |

---

## 7. Synchronization Variables Used

To implement the solution, we use:

---

### 7.1 `readcnt` — Reader Count

* Integer variable
* Tracks number of readers currently reading

---

### 7.2 `mutex` — Protects `readcnt`

* Binary semaphore
* Ensures mutual exclusion while updating `readcnt`

---

### 7.3 `wrt` — Writer Lock

* Binary semaphore
* Ensures exclusive access to the shared resource

---

## 8. Semaphore Operations (Reminder)

```c
wait(S);    // decrement, block if S <= 0
signal(S);  // increment, wake waiting process
```

---

## 9. Reader Process (Readers-Preference Solution)

---

### Reader Pseudocode

```c
do {
    wait(mutex);          // protect readcnt
    readcnt++;

    if (readcnt == 1)
        wait(wrt);        // first reader blocks writers

    signal(mutex);        // allow other readers

    // ---- Critical Section (Reading) ----

    wait(mutex);          // protect readcnt
    readcnt--;

    if (readcnt == 0)
        signal(wrt);      // last reader allows writers

    signal(mutex);
} while (true);
```

---

### Step-by-Step Explanation

#### Entry Section

1. Reader locks `mutex`
2. Increments `readcnt`
3. If it is the **first reader**:

   * It locks `wrt`
   * Writers are blocked
4. Releases `mutex`

Now:

* Multiple readers can read concurrently

---

#### Exit Section

1. Reader locks `mutex`
2. Decrements `readcnt`
3. If it is the **last reader**:

   * It releases `wrt`
   * Writers are allowed
4. Releases `mutex`

---

## 10. Writer Process

---

### Writer Pseudocode

```c
do {
    wait(wrt);      // lock resource

    // ---- Critical Section (Writing) ----

    signal(wrt);    // release resource
} while (true);
```

---

### Explanation

* Writer must acquire `wrt` before writing
* Only one writer can hold `wrt`
* Readers are blocked while a writer is active

---

## 11. Why `wait(mutex)` Is Used Twice in Reader Code (Very Important)

This is a **common interview doubt**.

### Reason:

* `mutex` protects **readcnt**
* `readcnt` is modified:

  * Once when reader enters
  * Once when reader exits

So:

* First `wait(mutex)` → protects increment
* Second `wait(mutex)` → protects decrement

Without this:

* Two readers could update `readcnt` simultaneously
* Leading to incorrect reader count
* Writers may enter incorrectly

---

## 12. Properties of Readers-Preference Solution

| Property           | Status             |
| ------------------ | ------------------ |
| Mutual Exclusion   | Yes                |
| Multiple Readers   | Yes                |
| Writer Exclusivity | Yes                |
| Deadlock           | No                 |
| Starvation         | Writers may starve |

---

## 13. Limitations of Readers-Preference

* Continuous arrival of readers
* Writers may wait indefinitely
* Not suitable for systems where writes are critical

This is why **writers-preference or fair solutions** exist.

---

## 14. Interview Questions

### Basic

1. What is the Readers–Writers problem?
2. Why can multiple readers read simultaneously?
3. Why writers need exclusive access?

---

### Conceptual

1. Difference between readers-preference and writers-preference?
2. Why does readers-preference cause writer starvation?
3. What is the role of `readcnt`?

---

### Tricky

1. Why does the first reader lock `wrt`?
2. Why does the last reader unlock `wrt`?
3. Is this solution deadlock-free?
   → Yes.

---

## 15. Key Takeaways

* Readers–Writers models **shared data access**
* Readers can share, writers must be exclusive
* Readers-preference improves read performance
* But can cause **writer starvation**
* Correct synchronization depends on:

  * Semaphore ordering
  * Accurate reader counting

> **This problem teaches priority handling and starvation trade-offs.**
