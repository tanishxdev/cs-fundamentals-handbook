# Distributed Caching & Consistent Hashing

![](https://substackcdn.com/image/fetch/$s_!THXz!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2Fd2088a5f-3a3f-483e-9afb-74b4e4c0d47e_1526x1600.png)
---

# 1. What is Distributed Caching?

A **distributed cache** means:

Cache data is spread across **multiple cache servers**, not just one.

Why?

Because:

* Single cache server cannot handle large traffic
* Single machine has limited RAM
* If one cache fails → everything breaks
* Scaling horizontally is required for big systems

Examples:

* Redis Cluster
* Memcached Cluster
* CDN caching layers

---

# 2. Why not put all data in one cache node?

Because:

1. **Memory limit**
   Both Redis and Memcached have per-node memory caps.

2. **High traffic will overload one machine**
   Cache must scale out.

3. **Single point of failure**
   If one server dies → whole system fails.

4. **Better performance**
   Distributed cache = parallel reads = high throughput.

---

# 3. Basic Idea of Distributed Cache

If you have multiple cache nodes:

Node A
Node B
Node C
Node D

You need to decide:

**Which key goes to which node?**

Example:

key “user:123” → Node A
key “post:88” → Node C
key “feed:home” → Node D

This mapping must be:

* Fast
* Predictable
* Evenly balanced
* Stable when nodes join/leave

But normal hashing fails here.

---

# 4. Why Normal Hashing Fails

(Using `hash(key) % N`)

Traditional formula:

```
nodeIndex = hash(key) % numberOfNodes
```

Example:

hash("A") % 3 → Node 0
hash("B") % 3 → Node 1
hash("C") % 3 → Node 2

### Major Problem: Node Change = Total Remap

If one node is added or removed,
`N` (number of nodes) changes → **every key remaps**.

This causes:

* Massive cache misses
* Huge load on database
* System meltdown during scaling

This is why big systems **never** use modulo-based hashing.

---

# 5. Consistent Hashing (The Hero Solution)

[Consistent Hashing 101: How Modern Systems Handle Growth and Failure](https://blog.bytebytego.com/p/consistent-hashing-101-how-modern)


Consistent Hashing solves the problem of **mass remapping**.

Core idea:

**Adding or removing a node should NOT remap all keys.**
Only a very small portion should move.

This keeps cache warm and stable.

---

# 6. How Consistent Hashing Works (Very Easy Language)

Think of a circle (0–360 degrees).

This is called the **hash ring**.

Steps:

1. Hash all cache nodes and place them on the ring.
2. Hash all keys and place them on the ring.
3. Each key belongs to the **next node clockwise** on the ring.

Example:

```
[Key K] ---> assigned to next clockwise Node
```

---

# 7. What Happens When a Node Fails?

Only keys that belonged to that node move to the **next node**.

Everything else stays the same.

So:

* Minimal remapping
* System stays stable
* Cache misses are low

---

# 8. What Happens When a Node Joins?

Add the new node to the ring.

Only the keys between the new node and its predecessor move.

Small key movement = system stable.

---

# 9. Problem in Basic Consistent Hashing: Uneven Distribution

Hashing may cluster keys near some nodes.

Example:

Node A → 70% keys
Node B → 10%
Node C → 20%

This causes load imbalance.

---

# 10. Solution: Virtual Nodes (VNodes)

Each physical node is represented by many **virtual nodes**.

Example:

Node A → A1, A2, A3, A4
Node B → B1, B2, B3, B4
Node C → C1, C2, C3, C4

This spreads keys evenly.

Used by:

* Redis Cluster
* Cassandra
* DynamoDB
* Kafka partitions

---

# 11. Example Scenario (Very Clear)

3 nodes: A, B, C

Key K = hash(K)

Case 1: All nodes alive
K goes to node C

Case 2: Node C fails
Now K goes to the next clockwise node (A)

Only keys mapped to C change.
A and B keys remain untouched.

---

# 12. Consistent Hashing in Real Systems

### Redis Cluster

Uses hash slots (0–16383) instead of a ring, but the idea is similar.

### Amazon DynamoDB

Famous for virtual nodes and perfect distribution.

### Cassandra

Uses token ranges (consistent hashing based).

### Kafka

Uses partitions + hashing (not exactly consistent hashing, but similar).

---

# 13. Benefits of Consistent Hashing

| Benefit              | Explanation                                |
| -------------------- | ------------------------------------------ |
| Minimal key movement | Only affected keys move on node join/leave |
| Even distribution    | With virtual nodes                         |
| High scalability     | Add nodes without downtime                 |
| High availability    | Node failures handled gracefully           |
| Better performance   | Cache misses minimized                     |

---

# 14. Where Distributed Caching is Used

* User sessions
* Feed caches (Twitter, Instagram)
* Product catalog (Amazon)
* Notification systems
* Search indexing
* High-speed microservices

---

# 15. Interview-ready Summary (Perfect 30-second answer)

Distributed caching spreads cached data across multiple nodes.
But naive hashing fails because adding or removing a node remaps almost every key.
Consistent Hashing solves this by placing nodes and keys on a hash ring.
Each key maps to the next clockwise node.
When nodes join or leave, only a small fraction of keys remap.
Virtual nodes are used to ensure even load distribution.
This technique powers Redis Cluster, Cassandra, DynamoDB, and many scalable systems.

---