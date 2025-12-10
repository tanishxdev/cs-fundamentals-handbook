
# Distributed Locking (Redis vs Zookeeper)
---

Distributed locking ensures that **multiple nodes in a distributed system** do **not perform the same critical action simultaneously**.

It provides **mutual exclusion** across different servers.

Used for:

* Preventing duplicate job execution
* Ensuring only 1 instance updates shared resource
* Leader election
* Scheduling tasks
* Inventory update / payment processing
* Avoiding race conditions

---

# 1. Why Distributed Locks Are Needed

In distributed systems:

* Multiple servers run the same code
* They access shared resources (DB row, file, cache, job queue)
* Without coordination → they may conflict

Examples:

* Two servers deducting money at same time
* Multiple workers processing the same message
* Two microservices updating inventory simultaneously

Distributed locks guarantee:

**Only one server holds the lock at any time.**

---

# 2. Distributed Lock Requirements (Very Important)

A good distributed lock must support:

### 1. Mutual Exclusion

Only one holder at a time.

### 2. No Deadlocks

If a node crashes → lock must auto-release.

### 3. Fault Tolerance

Lock must survive node/network failures.

### 4. Correctness Under Partition

Split-brain must not allow 2 lock holders.

### 5. Fairness (optional)

Requests granted in order.

### 6. Leasing (TTL)

Lock expires automatically after timeout.

---

# 3. Distributed Lock Using Redis

(Practical, fast, widely used)

Redis is used because:

* In-memory → very fast
* Supports atomic operations
* Simple API
* Widely used in microservices

### Basic Redis Lock (SETNX + EXPIRE)

```
SET my_lock unique_value NX PX 30000
```

Explanation:

* `NX` → only set if key does not exist
* `PX` → expiry (TTL)
* `unique_value` → identifies owner to prevent others from deleting lock

### Releasing the lock

Only owner should release it:

Use a **Lua script** to check value + delete atomically:

```
if redis.get(lock_key) == unique_value:
    redis.del(lock_key)
```

### Problems with basic Redis lock

* Redis crash may cause lock loss
* Clock skew affects TTL accuracy
* Single Redis node = single point of failure

### Production Solution: **Redlock Algorithm**

Created by Redis author (Antirez).

Uses **multiple Redis nodes**:

* Acquire lock from majority (N/2 + 1)
* Uses same key, same TTL
* Ensures correctness during partitions

Works well if:

* Redis nodes are independent
* Network partitions are rare
* Strong safety is not critical (industry debate exists)

### Where Redis locking is good:

* Job scheduling
* Microservice coordination
* Low-trust workloads
* High-speed locking

### Where Redis locking is risky:

* Banking / financial consistency
* Systems requiring strict linearizability
* When network partitions occur frequently

---

# 4. Distributed Lock Using Zookeeper

(Strong consistency, reliable, used in enterprise systems)

Zookeeper is built for **coordination and consistency**, making it ideal for distributed locks.

It guarantees:

* Strong consistency
* Automatic lock release
* No split-brain
* Ordering of requests

### How Zookeeper Lock Works (Simple Explanation)

Uses **ephemeral sequential znodes**:

1. Client creates:

   ```
   /locks/lock-00000001 (ephemeral sequential)
   ```
2. Zookeeper assigns incremental number.
3. Client with **smallest number** gets the lock.
4. Others watch the node before them.
5. If the lock-holder dies → ephemeral node disappears → next client gets lock.

### Why Zookeeper is reliable for locking

* Ephemeral nodes auto-delete if process dies
* Zookeeper is CP (strong consistency)
* Ordered locks (fairness)
* Avoids split-brain using ZAB protocol

### Where Zookeeper locking is good:

* Distributed databases
* Leader election
* Workflow coordination
* Financial applications
* Systems requiring correctness > speed

### Downsides

* Slower than Redis (disk + quorum)
* More complex setup
* Requires a cluster

---

# 5. Redis vs Zookeeper for Distributed Locking

(Very Clear Comparison Table)

| Feature          | Redis Lock                     | Zookeeper Lock                    |
| ---------------- | ------------------------------ | --------------------------------- |
| Speed            | Very fast                      | Slower                            |
| Consistency      | Eventually consistent          | Strong consistency                |
| Failure behavior | Risk of split-brain            | Safe under failures               |
| Auto-release     | TTL (not perfect)              | Ephemeral nodes (perfect)         |
| Lock ordering    | No                             | Yes (FIFO fairness)               |
| Ease of setup    | Very easy                      | More complex                      |
| Scalability      | High                           | Moderate                          |
| Best for         | High-speed apps, microservices | Critical systems, leader election |
| Examples         | Job queues, API rate limits    | Kafka, Hadoop, Kubernetes masters |

---

# 6. Which One Should You Use?

### Choose **Redis** if:

* Performance is priority
* Occasional duplicates are acceptable
* Lock duration is short
* System can tolerate at-least-once execution
* You need simple lightweight locking

### Choose **Zookeeper** if:

* You need strong correctness
* You cannot tolerate double locks
* You need ordering / fairness
* You implement leader election
* Workload is critical (financial, metadata systems)

---

# 7. Real System Examples

### Redis Locking

Used in:

* Celery workers
* Ecommerce inventory updates
* Payment retry avoidance
* Microservices job schedulers

### Zookeeper Locking

Used in:

* Hadoop NameNode
* Kafka brokers (controller election)
* HBase region servers
* Kubernetes etcd (Raft-based, similar guarantees)

---

# 8. Interview-Ready Summary (30 Seconds)

Distributed locking ensures only one node performs a critical action at a time.

Redis provides **fast, practical locking** using SETNX with TTL or the Redlock algorithm. It’s good for speed but not perfect under network partitions.

Zookeeper provides **strong and reliable locking** using ephemeral sequential znodes, with automatic lock release and fairness. It is used in systems where correctness is more important than performance.

Redis → Fast but may allow rare split-brain
Zookeeper → Safe, consistent, used for leader election & critical operations

---
