

# Quorum Reads & Writes

---

Quorums are used in distributed databases to ensure **consistency and fault tolerance** even when some replicas fail.

A quorum means:

```
Enough replicas must agree before an operation is accepted.
```

Quorums guarantee that **reads intersect with writes**, ensuring clients always see correct data.

---

# 1. Basic Terms You Must Know

Distributed databases replicate data across **N nodes**.

Quorum operations are defined by three numbers:

```
N = total replicas
W = number of replicas that must acknowledge a write
R = number of replicas that must respond to a read
```

To guarantee strong consistency:

```
R + W > N
```

This ensures **every read overlaps with the latest write**.

---

# 2. Quorum Write (W)

A write is considered successful when **W replicas** acknowledge it.

### Example

If:

```
N = 3
W = 2
```

Write is accepted when any 2 replicas confirm the write.

Benefits:

* Write survives even if 1 replica is down
* Guaranteed that majority stores the latest version

---

# 3. Quorum Read (R)

A read is successful when **R replicas** return values.

Client picks the **latest version** from R responses using:

* Timestamps
* Vector clocks
* Version numbers

---

# 4. Why R + W > N Is Critical

This formula ensures:

* Read-set intersects write-set
* At least one replica in R has the latest committed write
* No stale reads if timestamps are correct

### Example 1 (Strong Consistency)

```
N = 3
W = 2
R = 2
R + W = 4 > 3 → Strong consistency guaranteed
```

### Example 2 (Eventual Consistency)

```
N = 3
W = 1
R = 1
R + W = 2 ≤ 3 → NO strong consistency
```

---

# 5. Quorum Examples (Very Easy)

### Majority Quorum

```
N = 5
W = 3
R = 3
```

Any 3 nodes agreeing ensures correctness.

### Fast Reads (small R)

```
W = majority
R = 1
```

Read is fast BUT requires majority write.

### Fast Writes (small W)

```
W = 1
R = majority
```

Write is fast, read must do more work.

---

# 6. Quorum Levels in Real Systems

## Cassandra (Tunable Consistency)

Supports:

```
ONE
QUORUM
LOCAL_QUORUM
ALL
```

Example: QUORUM for N=3 = any 2 replicas

Consistent writes:

```
R = QUORUM
W = QUORUM
```

## DynamoDB

Strong consistency:

```
R = majority
```

Eventual:

```
R = 1
```

## MongoDB (Replica Set)

Write concerns:

```
w: "majority"
```

Read concerns:

```
readConcern: "majority"
```

---

# 7. What Happens If Replicas Fail?

Quorums handle failures as long as enough nodes remain.

Example:

```
N = 5
W = 3
```

Even if 2 replicas fail, write still succeeds because 3 remain.

This gives **high availability with consistency**.

---

# 8. Notes on Version Conflict Resolution

Quorum systems still require conflict resolution for:

* clock skew
* concurrent writes
* network partitions

Common techniques:

* last-write-wins
* vector clocks
* timestamps
* hybrid clocks (HLC)

---

# 9. Benefits of Quorum-Based Consistency

### 1. Fault Tolerant

Operations succeed even if some nodes fail.

### 2. Consistency Guarantee

If `R + W > N`, read always sees latest write.

### 3. Tunable

You can adjust R/W to optimize for reads or writes.

### 4. Good for Large-Scale Systems

Used in AP systems that want tunable consistency.

---

# 10. Trade-offs of Quorums

### 1. Higher R/W → higher latency

More replicas contacted = slower operation.

### 2. Write amplification

More replicas must acknowledge.

### 3. Clock skew issues

Timestamps may cause incorrect version selection.

### 4. Network partitions

Quorum might not form → system becomes unavailable.

---

# 11. Common Quorum Settings

(Important for interviews)

### Balanced strong consistency

```
R = QUORUM
W = QUORUM
```

### Fast reads (write-heavy workloads)

```
W = QUORUM
R = 1
```

### Fast writes (read-heavy workloads)

```
W = 1
R = QUORUM
```

### Write-mostly workloads

```
W = 1
R = ALL
```

---

# 12. Quorum Behavior in CAP Theorem

Quorums follow **CP** behavior:

* If partitioned, leader can't get majority → reject writes
* Ensures consistency but reduces availability

AP databases (Cassandra/Dynamo-like) use “tunable quorums” to adjust behavior.

---

# 13. Interview-Ready Summary (30 Seconds)

Quorum reads and writes ensure consistency by requiring a minimum number of replicas to agree before an operation succeeds.
Using parameters N (total replicas), R (read quorum), and W (write quorum), strong consistency is achieved if R + W > N.
Quorums allow systems to tolerate failures while maintaining correctness, and are used in Cassandra, DynamoDB, MongoDB, and other distributed databases.
You can tune R and W to favor fast reads, fast writes, or balanced consistency.

---
