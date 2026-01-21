# **Deadlock Recovery in Operating System**

---

## 1. Where Deadlock Recovery Fits in the Big Picture

Before understanding recovery, place it correctly:

| Strategy     | When it acts              | Core idea                 |
| ------------ | ------------------------- | ------------------------- |
| Prevention   | Before execution          | Break deadlock conditions |
| Avoidance    | During allocation         | Stay in safe states       |
| Detection    | After allocation          | Detect deadlock           |
| **Recovery** | **After deadlock occurs** | **Fix the deadlock**      |
| Ignorance    | Never                     | Reboot and forget         |

👉 **Deadlock Recovery assumes one thing**:

> *Deadlocks are allowed to happen.*

The OS accepts deadlocks as a reality and focuses on **getting out of them**.

---

## 2. What Is Deadlock Recovery?

**Deadlock Recovery** is the mechanism used by an operating system to:

* Detect that a deadlock has occurred
* Take corrective action
* Restore the system to a working state

Unlike prevention or avoidance, **recovery is reactive**, not proactive.

---

## 3. Goals of Deadlock Recovery

A good recovery strategy tries to balance **correctness and cost**.

The OS aims to:

1. **Break the deadlock cycle**
2. **Free locked resources**
3. **Minimize loss of computation**
4. **Preserve system consistency**
5. **Resume normal execution**

---

## 4. High-Level Recovery Techniques

There are **three fundamental recovery approaches**:

1. Process Termination
2. Resource Preemption
3. Process Rollback

Real systems often use a **combination** of these.

---

## 5. Recovery Method 1: Process Termination

This is the **most straightforward** approach.

### Idea

Break the deadlock by **killing one or more processes** involved in the cycle.

---

### 5.1 Kill All Deadlocked Processes

**How it works**

* Identify all processes in the deadlock
* Terminate all of them at once

**Advantages**

* Simple
* Guaranteed to break deadlock

**Disadvantages**

* Massive loss of work
* Unacceptable for critical systems

**Used when**

* System is unstable
* Processes are short-lived
* Recovery speed matters more than computation loss

---

### 5.2 Kill One Process at a Time (Victim Selection)

Instead of killing everyone, the OS chooses a **victim process**.

**Process is terminated → resources released → cycle broken**

This may repeat until deadlock is gone.

---

### 5.3 Victim Selection Criteria (Very Important for Exams)

The OS chooses the *least expensive* process to kill based on:

* **Priority** (low priority preferred)
* **Execution time so far** (shorter preferred)
* **Remaining execution time** (longer preferred)
* **Number of resources held**
* **Type of process**

  * Batch → easier to kill
  * Interactive → avoid killing
* **Restart cost**

👉 This is an **optimization problem**, not a fixed rule.

---

## 6. Recovery Method 2: Resource Preemption

Instead of killing processes, the OS **takes resources away**.

---

### Idea

* Preempt (forcefully take) a resource from one process
* Give it to another process
* Break the deadlock cycle

---

### Key Challenges in Resource Preemption

#### 1. Selecting a Victim

Which process should lose its resource?

* Same criteria as termination
* Choose process with **lowest rollback cost**

---

#### 2. Rollback Requirement

When a resource is taken away:

* The process must be rolled back
* Partial execution may be invalid

This means:

* OS must support **checkpointing**

---

#### 3. Starvation Problem

A process may:

* Lose resources repeatedly
* Never make progress

**Solution**

* Track how many times a process is chosen as a victim
* Avoid selecting the same process again and again

---

### When Resource Preemption Is Used

* Systems where killing processes is unacceptable
* Databases
* Long-running computations
* Transaction systems

---

## 7. Recovery Method 3: Process Rollback

This is the **cleanest but most expensive** solution.

---

### Idea

* Roll back one or more processes to a **previous safe checkpoint**
* Restart them later when resources are free

---

### How Rollback Works

1. OS periodically saves process state (checkpoint)
2. Deadlock detected
3. One process is rolled back
4. Resources released
5. Process restarts from checkpoint

---

### Advantages

* No permanent loss of work
* Safe for critical systems
* Maintains consistency

---

### Disadvantages

* Requires checkpoint storage
* High overhead
* Complex implementation

---

### Used In

* Banking systems
* Transaction processing
* Distributed systems
* Fault-tolerant systems

---

## 8. Combination of Recovery Techniques

Real operating systems **do not rely on a single method**.

Typical strategy:

* Try **resource preemption**
* If not possible → **rollback**
* If still unresolved → **terminate process**

Recovery is **policy-driven**, not hard-coded.

---

## 9. Example Scenario (Step-by-Step)

### Given Deadlock

* P1 holds Printer → waits for Memory
* P2 holds Memory → waits for Disk
* P3 holds Disk → waits for Printer

Cycle:

```
P1 → P2 → P3 → P1
```

---

### Recovery Options

**Option 1: Terminate P3**

* Disk released
* P2 proceeds
* P1 proceeds
* Deadlock resolved

**Option 2: Preempt Disk from P3**

* Roll back P3
* Allocate Disk to P2
* System continues

---

## 10. Comparison: Recovery vs Other Techniques

| Aspect            | Prevention | Avoidance | Recovery |
| ----------------- | ---------- | --------- | -------- |
| When              | Before     | During    | After    |
| Deadlock allowed? | No         | No        | Yes      |
| Overhead          | High       | High      | Medium   |
| Complexity        | Medium     | High      | High     |
| Used in practice  | Rare       | Limited   | Yes      |

---

## 11. Important Exam & Interview Points

Memorize these:

1. Recovery is **reactive**
2. Requires **deadlock detection first**
3. Termination is simplest, rollback is safest
4. Resource preemption risks starvation
5. Rollback needs checkpointing
6. No single recovery method fits all systems

---

## 12. One-Line Definitions (Quick Recall)

* **Deadlock Recovery**: Resolving deadlock after it occurs
* **Victim Selection**: Choosing process to kill or rollback
* **Rollback**: Restoring process to earlier safe state
* **Preemption**: Forcefully taking resources

---

## 13. Final Mental Model

Think of deadlock recovery like a **traffic jam**:

* Kill cars → road clears (termination)
* Tow away one car → flow resumes (preemption)
* Reset traffic signals → cars restart safely (rollback)

Each has a **cost**, and the OS chooses based on **system goals**.

---

### You are now done with the **complete Deadlock lifecycle**:

1. Deadlock conditions
2. Detection (RAG, WFG)
3. Handling strategies
4. Prevention
5. Avoidance (Banker’s)
6. **Recovery**
