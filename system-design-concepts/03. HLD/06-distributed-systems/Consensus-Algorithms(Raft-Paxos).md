
# Consensus Algorithms (Raft & Paxos)

---

Consensus algorithms allow a **cluster of machines** to:

**Agree on a single value / state, even if some machines fail.**

This is the backbone of:

* Distributed databases
* Kubernetes (etcd uses Raft)
* Zookeeper (uses Zab/Paxos ideas)
* Blockchain
* Replicated logs
* Leader election
* Fault-tolerant systems

Consensus solves a fundamental problem:

**How do multiple nodes agree on the same decision even if network is unreliable or nodes crash?**

---

# 1. Why Do We Need Consensus?

Because in distributed systems:

* Machines can fail
* Networks can partition
* Messages can delay
* Nodes may disagree

Consensus ensures:

* One elected leader
* Single source of truth
* All nodes apply operations in same order
* System remains correct even after node failures

Without consensus → databases diverge → corruption.

---

# 2. Raft vs Paxos: High-Level Difference

| Property        | **Raft**                   | **Paxos**                                        |
| --------------- | -------------------------- | ------------------------------------------------ |
| Complexity      | Simple, easy to understand | Complicated, mathematically elegant              |
| Real-world use  | Very widely used           | Foundational theory, fewer clean implementations |
| Leader election | Built-in and clear         | Leader concept exists but less explicit          |
| Log replication | Very structured            | Hard to implement correctly                      |
| Best for        | Practical systems          | Academic or highly tuned systems                 |

Raft was literally designed to be:

> “A more understandable alternative to Paxos.”

---

# 3. RAFT Algorithm (Very Simple Explanation)

Raft divides the problem into 3 easy parts:

## A. Leader Election

Nodes start as **followers**.
If they don’t hear from a leader → they become **candidates**.

Candidate asks others:

"Make me the leader?"

If majority agrees → new **leader** is chosen.

## B. Log Replication

Clients send commands to the leader.
Leader appends them to its log and sends to followers.

Followers append entries and acknowledge.

When majority has acknowledged → entry is considered **committed**.

## C. Safety

Raft ensures:

* Only one leader at a time
* Log order is consistent
* Conflicts resolved deterministically

### Raft States

```
Follower → Candidate → Leader
```

### Key Idea

Majority agreement ensures correctness even if some nodes fail.

---

# 4. PAXOS Algorithm (Simple Explanation)

Paxos is more theoretical and has three roles:

* **Proposer** – suggests a value
* **Acceptor** – accepts the proposed value if valid
* **Learner** – learns the final agreed value

### How Paxos works (very simple)

1. Proposer sends proposal: “Let's agree on value X”
2. Acceptors promise not to accept older proposals
3. If majority accept → value is chosen
4. Learners get the final value

### Challenges with Paxos

* Hard to implement
* Handling log replication is very complex
* Many variations (Multi-Paxos, Fast Paxos)

### But Paxos is extremely powerful

It forms the theoretical foundation of consensus in academia.

---

# 5. Raft vs Paxos (Clear Comparison Table)

| Feature           | Raft                            | Paxos                                      |
| ----------------- | ------------------------------- | ------------------------------------------ |
| Understandability | Very easy                       | Very difficult                             |
| Leader model      | Strong leader                   | Weak/implicit leader                       |
| Log replication   | Built-in                        | Complicated                                |
| Performance       | Very good                       | Can be optimized but harder                |
| Implementation    | Easier                          | Very tricky                                |
| Real world        | Kubernetes (etcd), Consul, TiKV | Chubby (Google), Zookeeper-like algorithms |
| Safety            | Strong                          | Strong                                     |
| Liveness          | Good                            | Depends on version                         |

---

# 6. Why Raft Is Preferred in Real Systems

Most distributed systems today use Raft because:

* Clear leader = simpler logic
* Easy to debug
* Predictable behavior
* Easy log replication
* Cleaner conflict resolution

Systems using Raft:

* **Etcd (Kubernetes)**
* **Consul**
* **TiKV (TiDB)**
* **CockroachDB**
* **RethinkDB**

---

# 7. When Does Consensus Matter?

You need consensus for:

### 1. Leader election

Which node should act as the primary?

### 2. Replicated state machines

Every node must apply the **same updates in the same order**.

### 3. Metadata management

Cluster configuration
Shard placement
Membership changes

### 4. Distributed locks

Guaranteeing exclusive access.

### 5. Transaction coordination

Ensuring atomic commits (2PC/3PC + consensus hybrid).

---

# 8. Raft Algorithm Steps (Very Clear)

### Step 1 → Followers wait for heartbeat

Leader sends heartbeat
If missing → election starts

### Step 2 → Candidate requests votes

Gets majority → becomes leader

### Step 3 → Leader receives client requests

Adds to log

### Step 4 → Leader replicates log entries

Sends entries to followers

### Step 5 → Followers append & acknowledge

Leader marks entry as committed after majority ack

### Step 6 → All nodes apply entry to state machine

---

# 9. Paxos Algorithm Steps (Very Simple)

There are two phases:

### Phase 1: Prepare

Proposer asks acceptors:

“Will you promise not to accept older proposals?”

### Phase 2: Accept

Proposer sends value
If majority accept → value chosen

### Learners get the chosen value.

More robust variants include:

* Multi-Paxos
* Fast Paxos
* Cheap Paxos
* Generalized Paxos

---

# 10. Analogies (Very Simple to Remember)

### Raft = Democracy with a Leader

Everyone votes → majority chooses leader
Leader manages everything

### Paxos = Proposal Meeting

Proposer suggests something
If enough people agree → decision finalized

---

# 11. Interview-Ready Summary (30 Seconds)

Consensus algorithms allow distributed systems to agree on a single value even in the presence of failures.

**Raft** uses a strong leader, clear phases (leader election, log replication, safety), and is simple to implement. It’s used in Kubernetes (etcd), Consul, CockroachDB.

**Paxos** is the classical theoretical algorithm involving proposers, acceptors, and learners. It’s powerful but complex and hard to implement. Most real systems use Raft instead of raw Paxos.

Raft = practical & understandable
Paxos = theoretical & foundational

Both guarantee correctness if majority nodes agree.
