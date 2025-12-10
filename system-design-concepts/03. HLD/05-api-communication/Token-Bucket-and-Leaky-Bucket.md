
# Token Bucket and Leaky Bucket

---

Both algorithms are used for **rate limiting** in distributed systems.

They help control:

* Traffic spikes
* Abuse
* Burstiness
* API request overload

Used by:

* Cloudflare
* AWS API Gateway
* NGINX
* Stripe
* GCP load balancers

They work differently, so let's understand both clearly.

---

# 1. TOKEN BUCKET

![](https://bytebytego.com/images/courses/system-design-interview/design-a-rate-limiter/figure-4-5-FGZ35C5S.svg)
Allows **bursts** but keeps the **average rate** under control.

---

## Core Idea

A bucket contains tokens.
Each request **consumes 1 token**.
Tokens **refill at a fixed rate**.

If token available → request allowed
If no token → request denied (or queued)

---

## Example

Bucket capacity = 10
Refill rate = 5 tokens/sec
Each request = 1 token

At t=0: bucket full (10 tokens)

If user sends 10 requests instantly → all allowed (burst allowed).

If user sends 20 requests instantly →
10 allowed, 10 denied (unless bucket refills).

---

## Formula

Tokens refill over time:

```
new_tokens = refill_rate * time_passed
bucket_tokens = min(capacity, bucket_tokens + new_tokens)
```

---

## Pros

* Allows bursts (very useful for user experience)
* Simple to implement
* Controls average rate accurately
* Great for high-performance APIs

---

## Cons

* Bursts may overload downstream systems
* Attackers can use allowed bursts to spike traffic

---

## Best Use Cases

* User actions (clicks, likes, scrolls)
* API gateways
* Payment attempts
* Microservice internal throttling
* Rate-limiting with burst allowance

---

# 2. LEAKY BUCKET
![](https://bytebytego.com/images/courses/system-design-interview/design-a-rate-limiter/figure-4-7-AI26NI2Y.svg)

Smooth, constant outflow → **no bursts allowed**.

---

## Core Idea

Requests enter a bucket (queue).
Requests leave (leak) at a **fixed rate**.

If bucket overflows → request dropped.

---

## Example

Leak rate = 5 req/sec
Bucket capacity = 10

User sends 20 requests in 1 second:

* Only 5 requests get processed per second
* Extra requests stay queued → if queue full → dropped

**Output is always stable and constant.**

---

## Formula

If bucket not full → add request to bucket
Every tick: process 1 request (fixed leak rate)

---

## Pros

* Smooth request flow
* No bursts reaching backend
* Prevents overload very effectively
* Great for controlling downstream pressure

---

## Cons

* Not good for user-experience bursts
* Slow processing of sudden surges
* Queue size management required

---

## Best Use Cases

* Payment systems
* Databases (prevent overload)
* Messaging systems
* Network routers
* Strict throughput-limited APIs

---

# 3. Token Bucket vs Leaky Bucket

(Extremely Clear Comparison Table)

| Feature           | Token Bucket            | Leaky Bucket                   |
| ----------------- | ----------------------- | ------------------------------ |
| Allows bursts     | Yes                     | No                             |
| Output rate       | Burst allowed           | Always fixed                   |
| Complexity        | Easy                    | Medium                         |
| Queue             | Not needed              | Required                       |
| Best for          | User-facing APIs        | Backend protection             |
| Refill behavior   | Tokens refill over time | Requests leak at constant rate |
| Smoothness        | Medium                  | High                           |
| Latency           | Low                     | Can be high (queued)           |
| Prevents overload | Medium                  | Strong                         |

---

# 4. Visual Summary

(Explained in plain English)

### Token Bucket = Water tank + tap

* Water = tokens
* Quick large usage allowed
* Water refills slowly

### Leaky Bucket = Dripping bucket

* Water leaks at constant speed
* No burst escapes
* Smooth and stable output

---

# 5. Example in Real Systems

### Cloudflare

Uses Token Bucket for user rate limiting
Uses Leaky Bucket internally to protect backend services

### Stripe

Token Bucket for idempotency-safe retries
Leaky Bucket for internal worker queues

### NGINX

Supports both

* `burst` = token bucket
* `nodelay` = leaky bucket behavior

### APIs and Microservices

* Token Bucket → for user-friendly throttling
* Leaky Bucket → strict backend throughput control

---

# 6. When Should You Use What?

### Choose **Token Bucket** when:

* You allow small bursts
* User experience matters
* You want to smooth but not eliminate spikes
* API request limits like 100 req/min

### Choose **Leaky Bucket** when:

* Burst traffic must be eliminated
* Backend systems must receive constant rate
* DB/Payment/Message queues need protection
* You require predictable throughput

---

# 7. Interview-Ready 30-Second Answer

Token Bucket allows requests as long as tokens are available.
Tokens refill at a fixed rate, so bursts are allowed but average rate is controlled.

Leaky Bucket processes requests at a fixed constant rate.
Extra requests get queued, and if the queue is full, they're dropped.
It creates a smooth, stable flow with no bursts.

Token Bucket = burst-friendly rate limiting.
Leaky Bucket = burst-removal + backend protection.

---

# 8. Read more

[Design A Rate Limiter](https://bytebytego.com/courses/system-design-interview/design-a-rate-limiter)