# Active–Active vs Active–Passive

---
![](https://www.jscape.com/wp-content/uploads/0524_Active-Active20vs.20Active-Passive20High-Availability20Clustering_FeaturedImage_A.jpg)


These are **high availability (HA)** deployment strategies used in load balancers, databases, cache clusters, application servers, etc.

They decide:

**How many servers/nodes are active at the same time, and how failover happens when one node fails.**

---

# 1. Active–Active Architecture

Both (or all) nodes are **active at the same time** and share traffic.

### Simple Meaning

All nodes are **working together**.
If one node fails → traffic automatically goes to the remaining active nodes.

### Easy Analogy

Two shop counters are open.
Customers go to any counter.
If one cashier leaves, customers go to the other.

### How It Works

* Traffic is load-balanced across multiple active servers
* All servers continuously process requests
* If one node fails, others take over instantly

### Pros

* High performance (all nodes share load)
* Zero-downtime failover
* Better resource utilization
* Scales horizontally very well

### Cons

* Complexity is higher
* Requires synchronization (sessions, databases, cache consistency)
* More expensive to maintain

### Best Use Cases

* Load-balanced web servers
* Distributed databases (Cassandra, DynamoDB)
* Cache clusters (Redis Cluster)
* Microservices with stateless design

---

# 2. Active–Passive Architecture

One node is **active**, others are **standby**.
Standby nodes do **nothing** until a failure occurs.

### Simple Meaning

Only one node works; the other waits.
If the active node dies → passive node becomes active.

### Easy Analogy

Only one shop counter is open.
A second cashier is sitting in the back, ready to take over if the first cashier stops working.

### How It Works

* Active node receives all traffic
* Passive node periodically syncs data (heartbeat/replication)
* If active node fails → passive node is promoted

### Pros

* Simple to design
* Easy to maintain
* Strong consistency (only one active writer)

### Cons

* Failover may cause slight downtime (seconds)
* Passive server is underutilized
* Not scalable for high traffic

### Best Use Cases

* Relational databases with single-writer mode (Postgres master–replica)
* Stateful systems needing strict consistency
* Critical workloads needing safe failover (payment gateway primary + standby)

---

# 3. Active–Active vs Active–Passive

( Extremely Clear Comparison Table )

| Feature                | Active–Active                  | Active–Passive                   |
| ---------------------- | ------------------------------ | -------------------------------- |
| Number of active nodes | Multiple                       | Only one active                  |
| Failover               | Seamless / instant             | Requires switch-over             |
| Scalability            | High                           | Limited                          |
| Performance            | High (load shared)             | Medium (only one serves traffic) |
| Complexity             | Higher                         | Lower                            |
| Cost                   | Higher (all nodes active)      | Lower (one active)               |
| Idle resources         | None                           | Passive node idle                |
| Good for               | Web servers, microservices     | Databases, critical failover     |
| Consistency            | Harder (multi-writer problems) | Strong (single-writer)           |

---

# 4. How Failover Happens

## Active–Active

Failover = automatic
Load balancer simply removes the unhealthy node.

```
Node A + Node B (both active)
↓ Node A fails
Traffic → Node B (already active)
```

Zero downtime.

## Active–Passive

Failover = requires promotion
Passive node becomes active after heartbeat failure.

```
Active Node A
Passive Node B
↓ A fails
B becomes active
```

Small delay (1–10 seconds), depending on heartbeat timing.

---

# 5. Architecture Examples

## 1. Web Applications

Active–Active
Multiple servers behind a load balancer.

## 2. PostgreSQL / MySQL

Active–Passive
Primary DB + Replica (standby).

## 3. Redis Cluster

Active–Active
Multiple shards handle traffic.

## 4. Redis Sentinel

Active–Passive
Master failover to replica.

## 5. Kafka

Active–Active partitions
But each partition has 1 leader + followers (Active–Passive at partition level).

---

# 6. Interview-Ready Difference (30-second answer)

Active–Active means multiple nodes serve traffic simultaneously.
It gives high performance, zero-downtime failover, and good scalability, but increases complexity and cost.

Active–Passive means only one node is active and the rest are on standby.
It’s simpler, cheaper, and ensures strong consistency, but failover may cause slight downtime and does not scale well under high load.

---
