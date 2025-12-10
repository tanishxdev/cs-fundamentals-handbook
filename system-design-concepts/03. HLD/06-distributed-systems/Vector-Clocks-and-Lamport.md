

# Vector Clocks & Lamport Clocks

---

In distributed systems, **there is no global clock**.
Servers have their own physical time → which can drift → which causes ordering problems.

So we need **logical clocks** to order events without relying on physical time.

Two major logical clocks:

1. **Lamport Timestamps**
2. **Vector Clocks**

Both help answer:

* Did event A happen before event B?
* Are events concurrent?
* How to resolve write conflicts?

---

# 1. Why Physical Time Is Not Enough

Issues:

* Clock skew
* Network delays
* Machine crashes
* Different timezones
* No absolute global ordering

Logical clocks give **event ordering** without relying on actual time.

---

# 2. Lamport Clocks (Simple Logical Ordering)

Lamport timestamps give a **single number** per event.

### Lamport Clock Rules

Each process keeps a counter:

1. **Increment counter** before each event.
2. **Send counter value** with messages.
3. On receiving a message:

   ```
   counter = max(local_counter, msg_counter) + 1
   ```

### Interpretation

If:

```
timestamp(A) < timestamp(B)
```

Then A happened before B (according to logical time).

### Lamport clocks guarantee:

* A → B order preserved
* No contradictions
* Total ordering (if timestamps tie → break with process ID)

### Limitation (VERY IMPORTANT)

Lamport timestamps CANNOT detect concurrency:

```
If t(A) < t(B), B might not actually depend on A.
```

Lamport only gives **happened-before**, not concurrency detection.

---

# 3. Vector Clocks (Track Causality Precisely)

Vector clocks solve what Lamport clocks cannot.

A vector clock is a **list of counters**, one per node:

```
Node A: [A=5, B=3, C=2]
Node B: [A=4, B=7, C=2]
```

### Vector Clock Rules

1. Each node increments **its own counter** for local events.
2. When sending a message, include the entire vector.
3. On receiving:

   ```
   vector[i] = max(local[i], received[i]) for each index i
   ```

---

# 4. Vector Clocks: Understanding Ordering

Given two vector timestamps V1 and V2:

### 1. V1 < V2  → V1 happened before V2

If **all elements** of V1 ≤ V2 and at least one is <

### 2. V1 || V2  → concurrent

If neither V1 < V2 nor V2 < V1

### Vector clocks detect:

* Precise causality
* Concurrency
* Write-write conflicts

This is something Lamport clocks cannot detect.

---

# 5. Lamport vs Vector Clocks (Clear Comparison)

| Feature                 | Lamport Clock          | Vector Clock                 |
| ----------------------- | ---------------------- | ---------------------------- |
| Type                    | Single counter         | Array of counters            |
| Tracks                  | Ordering only          | Ordering + causality         |
| Can detect concurrency? | No                     | Yes                          |
| Size                    | Small (1 int)          | Large (depends on nodes)     |
| Used in                 | Raft, Paxos, databases | Dynamo, CRDTs, event systems |
| Complexity              | Low                    | Medium-high                  |

---

# 6. When to Use Lamport Clocks

Lamport timestamps are used when:

* Only ordering matters
* Concurrency detection is unnecessary
* You want low overhead
* Cluster size may change dynamically
* You want fast, simple logical clocks

Used in:

* Google's Chubby (Paxos)
* Kafka internal timestamp fallback
* Raft log index ordering
* Distributed locking algorithms
* Order-based replication

---

# 7. When to Use Vector Clocks

Vector clocks are used when:

* You need to detect conflicting concurrent updates
* You use multi-master or leaderless replication
* Writes can happen on different nodes at same time

Used in:

* **Amazon Dynamo**
* Cassandra (old versions)
* Riak
* CRDTs
* Event-sourced systems

Vector clocks allow systems to answer:

* Did these two writes conflict?
* Which version is newer?
* Should we merge these versions?

---

# 8. Example That Shows the Difference

Two users edit a profile simultaneously:

### Lamport Clock

Both writes have timestamps:

```
Node A: 10
Node B: 10
```

Lamport cannot know if:

* They are concurrent
* One caused the other

So system must choose last-write-wins → possible data loss.

### Vector Clock

Writes have vectors:

```
Node A: [A=2, B=0]
Node B: [A=0, B=2]
```

Neither is less than the other → **conflict detected**.

System can:

* Merge
* Ask user
* Resolve via policy

---

# 9. Complexity Differences

### Lamport clocks:

* Very light
* O(1) storage
* O(1) comparison

### Vector clocks:

* Heavy in large clusters
* O(N) storage per node
* O(N) comparison per event
* Harder when nodes dynamically join/leave

This is why production systems avoid vector clocks in large clusters (Cassandra removed them).

---

# 10. Interview-Ready Summary (30 Seconds)

Lamport clocks assign a single increasing number to events and provide a simple logical ordering. They guarantee happened-before ordering but **cannot detect concurrent updates**.

Vector clocks maintain a counter per node and provide **full causality tracking**. They can detect if events are concurrent or dependent. This is crucial in leaderless databases (Dynamo-style) to resolve conflicts.

Lamport → ordering
Vector → ordering + causality + concurrency detection

---
