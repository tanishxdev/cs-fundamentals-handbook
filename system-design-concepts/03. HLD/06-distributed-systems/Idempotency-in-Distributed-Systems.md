

# Idempotency in Distributed Systems

---

Idempotency ensures that repeating the same operation **one or many times** results in the **same final state**.

In distributed systems, idempotency is **critical** because:

* Networks fail
* Clients retry
* Servers crash
* Messages duplicate
* APIs time out
* Distributed queues may re-deliver messages

Without idempotency, retries can cause:

* Double payments
* Duplicate orders
* Duplicate jobs
* Overwritten data
* Inconsistent state

Idempotency gives **safe retries**.

---

# 1. What Is Idempotency? (Clear Definition)

An operation is idempotent if:

```
1 call  → correct result
10 calls → same correct result
100 calls → still same correct result
```

No extra side-effects, no duplication.

---

# 2. Why Idempotency Is Essential in Distributed Systems

Distributed systems are inherently unreliable:

### 1. Network calls may time out

Client retries the same request.

### 2. Messages may be delivered multiple times

Kafka, SQS, RabbitMQ = **at-least-once delivery**.

### 3. Server may crash after executing but before responding

Client thinks request failed → retries → duplicate work.

### 4. Microservices often chain calls

If intermediate service retries → duplicates may propagate.

### 5. Payment and order systems require strict correctness

Double-run = catastrophic.

Idempotency ensures **repeat execution is safe**.

---

# 3. Idempotent vs Non-Idempotent Examples

### Idempotent Operations

* `PUT /user/123` (replace data)
* `DELETE /order/55` (delete multiple times = no-effect)
* `SET balance = 100`
* `UPDATE last_login_time = now()`

### Non-Idempotent Operations

* `POST /orders` (creates new order each time)
* `POST /payments` (charges every retry)
* `INSERT INTO table VALUES (...)`

These require **idempotency enforcement**.

---

# 4. Techniques to Achieve Idempotency in Distributed Systems

Idempotency is not automatic — you **design for it**.

Below are six real-world strategies.

---

## Technique 1: Idempotency Keys

(The most widely used strategy)

Client attaches a unique key to request:

```
Idempotency-Key: abc-123
```

Server stores:

```
abc-123 → existing response
```

If client retries → server returns stored response,
NOT re-run business logic.

Used by:

* Stripe
* PayPal
* Razorpay
* Amazon Pay

---

## Technique 2: Deduplication Store (Redis / DB)

Server stores **request hash** or **message ID**:

```
if request_id exists → skip
else → process and store it
```

Common in message processing systems.

---

## Technique 3: Logical Upserts

Replace instead of insert:

```
INSERT ... ON CONFLICT UPDATE
```

Upsert makes retries safe.

---

## Technique 4: Versioning / Compare-And-Set

Use optimistic concurrency:

```
UPDATE table SET balance = 100
WHERE version = 7
```

If version mismatch → retry logic applies.

---

## Technique 5: Message De-duplication in Queues

Many queues deliver messages **multiple times** by design.

Solutions:

* Kafka: use message key → dedupe by key
* SQS FIFO: dedupe window
* Redis Streams: track XREAD IDs
* Kafka Streams: idempotent producer

---

## Technique 6: Stateless Microservices + Deterministic Logic

If your write logic is deterministic (same input → same output),
repeat execution produces same result.

Example:

```
calculate_price() always returns same result for same cart
```

---

# 5. Idempotency in Workflows / Sagas

Distributed workflows = multiple microservices.

Problems:

* A step may run twice
* Two services may retry independently
* Compensation actions must also be idempotent

Solution:

* **Each step must be idempotent**
* Every Saga action AND compensation must tolerate duplicates
* Maintain per-step idempotency keys

---

# 6. Idempotency in Event-Driven Systems

Events may be:

* Re-delivered
* Replayed
* Delivered out of order

Idempotent subscriber design:

1. Each event includes unique `event_id`
2. Subscriber checks if `event_id` processed before
3. If yes → skip
4. If no → process → mark stored

Used in:

* Kafka consumers
* Event Sourcing
* CQRS projectors
* Change Data Capture (CDC)

---

# 7. Idempotency in Distributed Databases

Databases also require idempotent writes:

### A. Upserts

Avoids duplicate insert.

### B. Monotonic counters

Use CAS or atomic increments.

### C. Cassandra lightweight transactions

Ensure only one write succeeds.

### D. DynamoDB conditional writes

```
PUT item only if attribute does NOT exist
```

---

# 8. Idempotency vs Exactly-Once Delivery

(VERY IMPORTANT distinction)

**Idempotency = safe to retry**
**Exactly-once = duplicate delivery never happens**

Distributed systems **cannot guarantee exactly-once delivery** without idempotency + dedupe + transactions.

So real-world systems use:

* At-least-once delivery
* Idempotent operations
* Deduplication

To simulate "effectively once" processing.

---

# 9. Common Real-World Examples

### Payment APIs

Client retry → charge must only happen once.

### Order processing

Retrying POST /orders should not create duplicates.

### Job schedulers

Workers must not run same job twice.

### Email / SMS sending

Retry should not send the message twice.

### Distributed file processing

Retry must not write duplicate outputs.

---

# 10. Best Practices for Idempotency (Production Level)

### 1. Always use idempotency keys for POST operations

Especially payments, orders, booking, transactions.

### 2. Store idempotency keys with TTL

E.g., 24 hours (Stripe uses 24–48h window)

### 3. Use request hashing to detect tampering

If same key is used with different payload → reject.

### 4. Deduplicate events by ID

Especially in distributed messaging.

### 5. Ensure all microservice steps are idempotent

In Sagas, workflows, event handlers.

### 6. Use strong unique identifiers

UUIDv4, Snowflake ID, ULID.

### 7. Avoid relying only on application memory

Use Redis or a resilient store.

---

# 11. Interview-Ready Summary (30 seconds)

Idempotency in distributed systems ensures that repeating the same request multiple times results in the same final state.
It handles retries, duplicate messages, network failures, and at-least-once delivery.
Techniques include idempotency keys, deduplication stores, upserts, conditional writes, optimistic concurrency, and deterministic idempotent logic.
Systems like Stripe, Kafka, DynamoDB, SQS FIFO, and microservice workflows rely heavily on it.

Idempotency makes retries safe and provides **effectively-once processing** in distributed architectures.
