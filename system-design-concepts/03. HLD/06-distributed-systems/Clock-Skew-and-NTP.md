
# Clock Skew & NTP

---
![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSzY0g1MICegQM8S1Dv7kDWssRIgAMOSwFpTw&s)

![](https://docs.couchbase.com/server/current/install/_images/ntp_config_3.png)

In distributed systems, **every machine has its own clock**.
These clocks **do not stay perfectly aligned** due to hardware differences, drift, and network delays.

This difference in time between machines is called:

# 1. What is Clock Skew?

**Clock Skew = the difference between two servers' clocks.**

Example:

```
Server A: 12:00:10
Server B: 12:00:07
→ Skew = 3 seconds
```

All machines drift differently because:

* CPU crystals tick at slightly different rates
* Temperature affects hardware clocks
* No clock runs perfectly unless corrected

Clock skew makes **timestamps unreliable** across distributed systems.

---

# 2. Why Clock Skew Is a Big Problem

Clock skew directly causes serious distributed system bugs:

### 1. Incorrect ordering of events

If Server B is behind, it may appear that an event happened **before** another event even though it did not.

Example:

```
Write 1 → timestamp 12:00:10
Write 2 → timestamp 12:00:08
```

System thinks Write 2 happened first → catastrophic for databases.

### 2. Violates consistency guarantees

Distributed databases (Spanner, Cassandra, Mongo) rely on timestamps.
Skew breaks strong consistency.

### 3. Token/session expiration issues

If clock is ahead or behind, clients may be logged out early or gain invalid access.

### 4. Cache invalidation failures

"Expires at 12:05" fails if server clock is wrong.

### 5. Authentication bugs (OAuth/JWT)

“Token not valid yet” or “Token already expired” errors.

### 6. Race conditions

One server may think an event “hasn’t happened yet” when other servers think it has.

---

# 3. Clock Drift vs Clock Skew

(Very Clear Difference)

| Concept         | Meaning                                                |
| --------------- | ------------------------------------------------------ |
| **Clock Drift** | Clock on a machine slowly becomes inaccurate over time |
| **Clock Skew**  | The difference between time on machine A vs machine B  |

Drift causes skew.

---

# 4. What Is NTP?

![](https://www.zenarmor.com/docs/assets/images/figure-2-howntpworks-0b7a2c8c91dce9e29b2a8197505017b8.png)

(Network Time Protocol)


NTP is a protocol used to **synchronize clocks across servers**.

It ensures:

* All machines stay close in time
* Skew is minimized
* Drift is corrected continuously

### How NTP works (simple explanation)

1. Machine asks an NTP server for the time
2. NTP server replies with correct UTC time
3. Machine adjusts its clock slowly (not instantly!)
4. Sync happens regularly (every few minutes)

### Why slowly?

Fast jumps in time can break applications.
So NTP does **gradual adjustments** (“slewing”).

---

# 5. NTP Hierarchy

(Stratum Levels)

```
Stratum 0 → Atomic clocks / GPS clocks
Stratum 1 → Directly connected to Stratum 0
Stratum 2 → Get time from Stratum 1
Stratum 3 → Get time from Stratum 2
...
```

Lower stratum = more accurate.

Most companies sync their servers to Stratum 2 or 3.

---

# 6. Why NTP Alone Is Not Enough for Large Systems

Even with NTP:

* There is always some skew (5–100 ms)
* Network latency causes inaccurate time sync
* Sudden jumps can still break strongly consistent systems

This is why:

* Google Spanner uses **TrueTime API**
* Cassandra uses **Hybrid Logical Clocks (HLC)**
* Kafka warns about clock drift mismatches
* Kubernetes components fail if clock drift > 5 min

NTP helps but **does not guarantee perfect time synchronization**.

---

# 7. How Big Systems Handle Clock Skew

### A. Google Spanner: TrueTime API

Guarantees bounded time uncertainty ε.

### B. Cassandra: Hybrid Logical Clocks

Combines physical + logical time.

### C. Kafka: Strict broker time requirements

If clocks differ too much, consumer offsets break.

### D. Distributed locks

Require synchronized time to avoid deadlocks.

### E. Authentication tokens

JWT requires accurate server time validation.

---

# 8. Common Problems in Real Systems

### 1. User creates account → timestamp future dated

Second write with “older” timestamp seems to override it.

### 2. Payment system logs show reversed ordering

Fraud detection fails.

### 3. Cache invalidates early/late

TTL becomes unreliable.

### 4. Leader election fails

Raft, Zookeeper require synchronized timeouts.

### 5. Logging & Debugging become impossible

Events appear out of order.

---

# 9. How to Minimize Clock Skew

(Best Practices)

### 1. Use NTP on all servers

Sync with same NTP servers.

### 2. Prefer multiple NTP servers

To avoid single point of failure.

### 3. Use clock slewing instead of jumps

Jumps cause serious bugs.

### 4. Monitor drift

Alert when servers differ by >50–100 ms.

### 5. Use Logical Clocks where possible

Lamport clocks, vector clocks avoid relying on physical time.

### 6. Place servers geographically close

Less network latency → more accurate NTP sync.

---

# 10. Interview-Ready Summary (30 seconds)

Clock skew is the difference in time between servers in a distributed system.
It causes problems with ordering, consistency, TTLs, logs, and authentication.
NTP (Network Time Protocol) synchronizes machine clocks but still allows small drift.
Large systems combine NTP with logical clocks (like Lamport or hybrid clocks) or bounded-uncertainty systems (Google TrueTime) to achieve correct ordering.

---
