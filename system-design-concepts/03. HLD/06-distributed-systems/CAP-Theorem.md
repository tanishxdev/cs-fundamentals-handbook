
# CAP Theorem

---

![](https://media.geeksforgeeks.org/wp-content/uploads/20240813184051/cap.png)
![](https://substackcdn.com/image/fetch/$s_!H1G6!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F80ce435d-ddc1-4d6f-8d97-ce8db8b408c9_1600x973.png)
![](https://substackcdn.com/image/fetch/$s_!nxxY!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2Fe8df406b-65b8-4294-ba33-0b3de91d9a4f_2250x2624.png)


CAP theorem explains the **trade-off** every distributed system must make:

A distributed system **cannot** simultaneously guarantee:

* **C – Consistency**
* **A – Availability**
* **P – Partition Tolerance**

It can only guarantee **two at a time** (when a network partition happens).

---

# 1. Why CAP Theorem Exists

Because in distributed systems:

**Network failures are unavoidable.**
Machines can crash, networks can get slow, packets can drop.

When this happens, you must choose between:

### Option 1: Consistency

Reject requests until all nodes agree.

### Option 2: Availability

Serve stale or partial data but keep the system running.

You **cannot** have both at the same time if network is broken.

---

# 2. The Three Components (Very Clear)

## A. Consistency (C)

Every read returns the **latest, correct data** from all nodes.

Meaning:

* All nodes see the same data
* Strong consistency guaranteed

Example:
If you write `balance=100`, anyone reading immediately gets `100`.

---

## B. Availability (A)

The system always **responds**, even if some data is stale.

Meaning:

* Every request gets a non-error response
* No downtime

Example:
If one node is slow or partitioned, another node still responds.

---

## C. Partition Tolerance (P)

System continues to work **even when communication between nodes breaks**.

Meaning:

* Network failures do NOT break the system
* System must survive partitions

Example:
Node A cannot talk to Node B, but the service still runs.

---

# 3. The Key Truth of CAP

**Partition Tolerance is mandatory in real distributed systems.**
Network failures will happen, so you must support P.

So the real choice is:

### CP (Consistency + Partition Tolerance)

or

### AP (Availability + Partition Tolerance)

You choose which one to sacrifice **during a network partition**.

---

# 4. CP vs AP Systems (Simple Diagram)

---

# 5. CP Systems

**Consistency over Availability**

If nodes cannot communicate (partition), the system prefers:

✔ Consistency
✘ Availability (will reject requests)

Example behavior:

* If replica is unreachable → refuses to serve stale data
* Writes require majority consensus
* May block reads/writes to ensure correctness

### Real-world CP systems

* **MongoDB (majority write concern)**
* **HBase**
* **Zookeeper**
* **Etcd** (Kubernetes uses it)
* **Google Spanner**

### Used When

* Correctness is critical
* Banking balances
* Inventory count
* Leader election
* Distributed locking

---

# 6. AP Systems

**Availability over Consistency**

If nodes cannot communicate, the system prefers:

✔ Availability
✘ Consistency (may return stale data)

Example behavior:

* Always responds, even if some nodes are outdated
* Performs writes locally
* Syncs later (eventual consistency)

### Real-world AP systems

* **Cassandra**
* **DynamoDB**
* **Couchbase**
* **Riak**

### Used When

* High availability is required
* Social media feeds
* Shopping product pages
* Analytics
* Logging

---

# 7. CAP Matrix (Very Clear)

| Property            | CP Systems                | AP Systems          |
| ------------------- | ------------------------- | ------------------- |
| Consistency         | Strong                    | Eventual            |
| Availability        | Lower                     | High                |
| Partition Tolerance | Yes                       | Yes                 |
| Behavior in failure | Block requests            | Serve stale data    |
| Examples            | Zookeeper, HBase, Spanner | Cassandra, DynamoDB |

---

# 8. Real-World Example (Very Simple)

## You update your Instagram profile picture

If a network partition happens:

### AP system behavior:

* Shows old picture to some users
* Shows new picture to others
* But **app always works**
  (Instagram uses AP for feeds)

### CP system behavior:

* Might block profile update
* Or block reads until sync happens
  (Strong consistency)

---

# 9. What CAP Does NOT Mean

Very common interview clarifications:

✔ You do NOT choose two forever
✔ CAP tradeoff happens **only during a network partition**
✔ Most production DBs let you tune consistency level
✔ Modern systems often mix CP + AP depending on operation

---

# 10. Interview-Ready Summary (30 seconds)

CAP theorem states that in a distributed system, you cannot guarantee Consistency, Availability, and Partition Tolerance simultaneously.
Since partitions are inevitable, a system must choose between:

* **CP** – prioritize consistency, sacrifice availability
* **AP** – prioritize availability, sacrifice consistency

CP systems reject requests during partition to stay correct.
AP systems continue serving even if data is stale.
Examples:
CP → Zookeeper, Spanner, HBase
AP → Cassandra, DynamoDB

---

