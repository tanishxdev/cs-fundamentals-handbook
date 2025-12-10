

# Sliding Window Rate Limiter

---
![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSBDp4071xsWOuH-dr-ZHgwu66bfaApYmNH9g&s)
![](https://bytebytego.com/images/courses/system-design-interview/design-a-rate-limiter/figure-4-13-G2VF2RCQ.png)

Rate limiting ensures a user/client cannot exceed a certain number of requests in a given time.

Example rule:

```
Allow max 100 requests per minute per user.
```

Different algorithms exist:

* Fixed Window
* Sliding Window
* Token Bucket
* Leaky Bucket

Sliding-window is preferred when accuracy + fairness matter.

---

# 1. Problem Sliding Window Solves

### Issue with Fixed Window

If window resets at 12:00:

A user can send:

* 100 requests at 11:59
* 100 requests at 12:00
  = **200 requests in 2 seconds**
  Still allowed.

This causes traffic spikes → unfair + unsafe.

### Sliding Window fixes this by:

Limiting requests **over the last N seconds/minutes**, not inside a rigid window.

---

# 2. What is Sliding Window Rate Limiting?

Sliding window checks:

**How many requests were made in the last X time window from NOW.**

Example:
Rule = 100 requests / 60 seconds

At `12:30:20`
we check all requests between
`12:29:20` → `12:30:20`.

This avoids burst attacks.

---

# 3. How Sliding Window Works (Step-by-Step)

### 1. Store timestamp of every request

Each request gets stored with its timestamp.

### 2. Remove timestamps older than the window

Example: window = 60 seconds
During request at `t=100`, delete timestamps < `40`.

### 3. Count remaining timestamps

If count < LIMIT → allow request
Else → reject / throttled

### 4. Add current request’s timestamp

Store timestamp in Redis / memory.

---

# 4. Visualization (Simple Example)

Rule:

```
Limit = 5 requests per 10 seconds
```

Current time = 50 seconds
Stored timestamps:

```
41, 43, 44, 47, 49
```

Window: 40 → 50
Count = 5

New request at t = 50
→ Count = 5 >= limit
→ BLOCKED

At t = 52
timestamps:

```
43, 44, 47, 49, 50
```

Now window = 42 → 52
Count = 5
New request → BLOCKED

At t = 54
timestamps:

```
44, 47, 49, 50, 52
```

Window = 44 → 54
Count = 5
New request → BLOCKED

At t = 55
timestamps > 45 removed
Count drops to 4 → request allowed.

---

# 5. Data Structures Used

### Option 1: Redis Sorted Set (**most common**)

Key: user_id
Value: timestamps sorted

Operations:

* `ZADD` → add timestamp
* `ZREMRANGEBYSCORE` → remove expired timestamps
* `ZCOUNT` → check count

This is **production-grade** (Stripe, Cloudflare style).

### Option 2: In-memory Queue

Simpler but works only in single-node systems.

---

# 6. Sliding Window Precision vs Cost

### Pros

* Very accurate
* Prevents traffic spikes
* Fair distribution across time
* Ideal for high-scale distributed APIs
* Natural smoothing of request load

### Cons

* More memory: storing timestamps
* More computation: pruning old entries
* Harder than fixed window to implement

---

# 7. Sliding Window vs Other Algorithms

(Very Clear Table)

| Algorithm      | Accuracy | Prevents Burst     | Complexity | Use Case                      |
| -------------- | -------- | ------------------ | ---------- | ----------------------------- |
| Fixed Window   | Low      | Bad                | Very Easy  | Simple APIs                   |
| Sliding Window | High     | Excellent          | Moderate   | Fair + accurate rate limiting |
| Token Bucket   | Medium   | Good               | Medium     | Allow small bursts            |
| Leaky Bucket   | High     | Excellent (smooth) | Medium     | Smooth request flow           |

---

# 8. When Should You Use Sliding Window?

Use Sliding Window when:

* You want fairness
* Bursts must be prevented
* You need real-time rate limiting
* Strict throttling required
* High-traffic distributed systems
* APIs that shouldn’t allow spikes (login, payments, OTP)

Used by:

* Cloudflare
* NGINX rate limiting
* Stripe APIs
* API gateways
* Banking APIs

---

# 9. Real-World Examples

### Login throttling

“Max 5 login attempts in last 10 minutes.”

### OTP generation

Avoid flooding SMS providers.

### API Rate Limits

“100 requests per minute.”

### Payment APIs

Prevent accidental double-spends.

---

# 10. Interview-Ready Summary (30 seconds)

Sliding Window Rate Limiting ensures a client’s request count is checked against the **last rolling window** (like last 60 seconds) instead of fixed intervals.
It works by storing timestamps of each request, removing old ones, counting the remaining, and allowing/rejecting based on a threshold.

It prevents burst attacks better than fixed window and gives accurate, fair throttling.
Commonly implemented with Redis sorted sets.

---
