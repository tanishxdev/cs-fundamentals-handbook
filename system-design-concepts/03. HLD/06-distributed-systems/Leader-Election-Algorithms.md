

# Leader Election Algorithms

---

Leader election ensures that **in a distributed system, exactly one node acts as the leader** at any time.

The leader usually performs critical tasks:

* Coordinating writes
* Lock ownership
* Task scheduling
* Metadata management
* Cluster coordination

Examples:

* Kubernetes → etcd leader
* Kafka → broker controller
* Zookeeper → ZAB leader
* Redis Sentinel → master election

Leader election prevents **split brain** and ensures consistent control.

---

# 1. Why Leader Election Is Necessary

Distributed systems need leader election to solve:

### 1. Who should be the coordinator?

To avoid multiple nodes making conflicting decisions.

### 2. What if the leader dies?

Another node must take over automatically.

### 3. How to maintain consistency?

A single leader simplifies ordering of writes.

### 4. How to prevent multiple leaders (split brain)?

With voting, quorum, or fencing tokens.

---

# 2. Required Properties of Leader Election

### 1. **Safety**

At most **one leader** at a time.

### 2. **Liveness**

A leader must eventually be elected.

### 3. **Fault tolerance**

Leader election must work even if nodes crash or network partitions occur.

### 4. **Deterministic or guaranteed convergence**

All healthy nodes agree on *the same* leader.

---

# 3. Major Leader Election Algorithms

You should know these four for interviews:

1. **Bully Algorithm**
2. **Ring Algorithm**
3. **Raft Leader Election**
4. **Zookeeper / etcd Leader Election (ZAB / Raft-based)**

Let’s go one by one.

---

# 4. Bully Algorithm

(Oldest, simplest algorithm — good for conceptual questions)

### Idea

The node with the **highest ID** becomes the leader.

### Process

1. If a node detects leader failure → it starts an election.
2. It sends messages to all nodes with higher ID.
3. If no higher node responds → this node becomes leader.
4. If a higher node replies → that node takes over the election.

### Strengths

* Simple
* Deterministic leader (highest ID always wins)

### Weaknesses

* Not fault-tolerant during partitions
* Requires reliable detection of leader failure
* Too much messaging in large clusters

### Use cases

* Learning algorithms
* Small toy systems (not used in major distributed systems today)

---

# 5. Ring Algorithm

(Another classic election method)

### Idea

Nodes are arranged in a logical ring.

### Process

1. A failed leader triggers an “election message” circulating around the ring.
2. Every node adds its ID to the ring message.
3. After full rotation, highest ID wins.
4. Winner is announced to all nodes.

### Strengths

* Simple
* Predictable messaging pattern

### Weaknesses

* Slow (needs full ring traversal)
* Breaks if ring membership is inconsistent

### Use Cases

* Basic research, teaching examples

---

# 6. Raft Leader Election

(This is the **industry standard**, extremely important)

Used in:

* etcd (Kubernetes)
* Consul
* TiKV
* CockroachDB

### States

Each node cycles through:

```
Follower → Candidate → Leader
```

### Steps (Very Clear)

1. Followers expect heartbeat from leader.
2. If heartbeat missing → follower becomes **candidate**.
3. Candidate increments term and requests votes.
4. Nodes vote only once per term.
5. If candidate gets **majority votes** → becomes leader.
6. Leader sends heartbeats to maintain authority.

### Why Raft is excellent

* Very fault-tolerant
* Guarantees no two leaders in same term
* Works under network partitions (CP system)
* Simpler than Paxos

---

# 7. Zookeeper / etcd Leader Election

(Using **ephemeral znodes** or Raft underneath)

### Zookeeper (ZAB protocol)

1. Each node creates an **ephemeral sequential znode** under `/election`.
2. The node with the **lowest sequence number** becomes leader.
3. If leader dies → its ephemeral node disappears → next node becomes leader.

### etcd (Raft-based)

Works exactly like Raft:

* Heartbeats
* Terms
* Majority voting

### Why Zookeeper/etcd elections are reliable

* Strong consistency guarantees
* Automatic lock release via ephemeral nodes
* No split-brain

Used in:

* Hadoop NameNode
* Kafka controller
* Kubernetes control plane

---

# 8. What Causes Leader Election to Trigger?

Leader election is triggered when:

* Leader crashes
* Leader becomes unreachable (network partition)
* Leader’s heartbeat times out
* Leader voluntarily steps down
* Manual failover (operational event)

Systems must detect failures fast, but not too fast (to avoid false elections).

---

# 9. Challenges in Leader Election

### 1. Split Brain

Two leaders at once → inconsistent state
Solution: Quorum-based voting

### 2. Network partitions

Nodes may think leader is dead when it's not
Solution: Term-based leadership (Raft)

### 3. Clock skew

Timeouts must handle skew
Solution: Randomized election timeout (Raft)

### 4. High latency

Slow election = cluster downtime
Solution: Heartbeats + fast detection

---

# 10. Comparison of Algorithms

(Very Clear Table)

| Feature           | Bully | Ring | Raft        | Zookeeper / etcd |
| ----------------- | ----- | ---- | ----------- | ---------------- |
| Complexity        | Low   | Low  | Medium      | Medium           |
| Modern usage      | Rare  | Rare | Very high   | Very high        |
| Fault tolerance   | Weak  | Weak | Strong      | Strong           |
| Requires majority | No    | No   | Yes         | Yes              |
| Auto recovery     | No    | No   | Yes         | Yes              |
| Consistency model | Weak  | Weak | Strong (CP) | Strong (CP)      |

---

# 11. Which Algorithm Should You Use?

### Use **Raft** when:

* You need strong consistency
* You want automatic failover
* You’re implementing metadata store, database, coordinator
* You want proven production reliability

### Use **Zookeeper-style election** when:

* You need total ordering + fairness
* You use Apache ecosystem (Kafka, Hadoop)
* You want ephemeral nodes and automatic cleanup

### Avoid **Bully** and **Ring** in real systems

Only useful for teaching or toy systems.

---

# 12. Interview-Ready Summary (30 Seconds)

Leader election algorithms ensure that exactly one node acts as a leader at a time in a distributed system. Bully and Ring are simple classical algorithms, but not used much in production.

Modern systems use **Raft** (etcd, Consul, CockroachDB) or **Zookeeper’s ZAB-based ephemeral node** election. Raft uses a majority vote with terms and heartbeats; Zookeeper uses ephemeral sequential znodes to choose a leader safely.

The goal is to avoid split brain, handle node crashes, and ensure the cluster always has a consistent leader.

---