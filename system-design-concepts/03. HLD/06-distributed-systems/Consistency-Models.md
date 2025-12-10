# Consistency Models

---

![](https://assets.bytebytego.com/diagrams/0100-eventual-consistency-patterns-you-must-know.png)
![](https://assets.bytebytego.com/diagrams/0062-a-cheatsheet-on-database-performance.png)

In distributed systems, **different replicas of data** may not always be perfectly synchronized.
Consistency models define:

**What guarantee does the system provide when a client reads data?**


They answer:

* “If I write something, when will others see it?”
* “Is my read fresh or stale?”
* “Do all replicas agree?”

---

# 1. Why Do We Need Consistency Models?

Because in distributed systems:

* Network latency exists
* Replication delay exists
* Nodes fail
* Partitions occur
* Writes can arrive at different times in different places

Consistency models define **predictability** for developers:

* Does a read give the latest data?
* Is stale data acceptable?
* Does the order of writes matter?

---

# 2. Categories of Consistency Models

From **strongest → weakest**:

1. **Strong Consistency**
2. **Linearizability** (subset of strict consistency)
3. **Sequential Consistency**
4. **Causal Consistency**
5. **Eventual Consistency**
6. **Weak Consistency**

Let’s break each down.

---

# 3. Strong Consistency

“After a write, **any read returns the latest value**, no matter which replica you hit.”


### Example

Write X = 5
Any client immediately sees X = 5.

### Pros

* Easy for developers
* No stale reads

### Cons

* Slow
* Hard to scale
* Requires coordination between replicas

### Used in

* RDBMS (PostgreSQL, Spanner)
* Leader-based systems
* Financial transactions

---

# 4. Linearizability (The Gold Standard)

A very strong form of consistency:

**Operations appear as if they happened instantly at a single point in time.**

Guarantees:

* Real-time ordering
* Latest write is always visible
* Global ordering of operations

### Example

If you update your bank balance,
your next read **must show the updated value immediately**.

### Used in

* Google Spanner
* Zookeeper
* etcd (Kubernetes)

### Notes

Linearizability is **stronger** than typical strong consistency because it enforces **real-world ordering**.

---

# 5. Sequential Consistency

“All operations appear in the same order to all clients,
BUT not necessarily respecting real time.”

### Example

Two updates A, B are seen in the same order by all clients.
But order may differ from real time.

### Difference from Linearizability

| Model        | Real-time ordering? | Same order for all? |
| ------------ | ------------------- | ------------------- |
| Linearizable | Yes                 | Yes                 |
| Sequential   | No                  | Yes                 |

### Used in

* Some NoSQL databases
* Distributed shared memory

---

# 6. Causal Consistency

Writes that are **causally related** must be seen in order.
Unrelated writes may be seen in different orders.


### Example

Alice posts “Hello”
Bob replies to Alice → causal relationship

All users must see:

1. Alice: Hello
2. Bob: Reply

But if Charlie posts something unrelated, order doesn't matter.

### Used in

* Social networks
* Messaging apps
* Dynamo-style systems

---

# 7. Eventual Consistency

“The system will **eventually converge**, but reads may be stale.”

### Example

You update your profile picture.

Some users see old picture → until replicas sync.

After some time → all replicas become consistent.

### Pros

* Fast
* Highly available

### Cons

* Stale reads
* Hard for developers

### Used in

* Cassandra
* DynamoDB
* S3
* CDN caching
* Most large-scale systems

---

# 8. Weak Consistency

No guarantees:

* Writes may take unpredictable time to propagate
* Reads may return very stale data
* Often used for high-speed caches

### Example

Redis cache with lazy writes.

### Used in

* Cache systems
* Real-time analytics
* Logging systems

---

# 9. Consistency Spectrum (Very Clear)

From strongest to weakest:

```
Linearizable  
↓  
Strong Consistency  
↓  
Sequential Consistency  
↓  
Causal Consistency  
↓  
Eventual Consistency  
↓  
Weak Consistency
```

---

# 10. Real System Examples

| System          | Consistency Model                          |
| --------------- | ------------------------------------------ |
| Google Spanner  | Linearizable                               |
| etcd, Zookeeper | Linearizable                               |
| PostgreSQL      | Strong consistency                         |
| MongoDB         | Tunable (strong → eventual)                |
| Cassandra       | Eventual (with tunable consistency levels) |
| DynamoDB        | Strong or eventual (configurable)          |
| Redis Cache     | Weak consistency                           |

---

# 11. CAP Theorem Connection

During a network partition:

* **CP systems** → choose Consistency (block reads/writes)
* **AP systems** → choose Availability (serve stale data)

Consistency model depends on system’s CAP choice.

---

# 12. Interview-Ready Summary (30 seconds)

Consistency models define how up-to-date and ordered data reads are in a distributed system.
Strong and linearizable consistency guarantee the latest value globally.
Sequential consistency guarantees the same operation order everywhere but may not follow real-time.
Causal consistency preserves cause-effect operations.
Eventual consistency allows stale reads but ensures replicas converge.
Weak consistency provides almost no guarantees but is very fast.

---
