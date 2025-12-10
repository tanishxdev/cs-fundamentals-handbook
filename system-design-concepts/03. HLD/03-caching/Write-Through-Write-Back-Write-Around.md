# Write-Through • Write-Back • Write-Around

![](https://media.licdn.com/dms/image/v2/D5622AQFV4WWu5TYZ2A/feedshare-shrink_800/B56ZgS4sTIHkAg-/0/1752663516595?e=2147483647&v=beta&t=UzY7Dqm-kBZx55l_S4Fr7lr_guPe4O2Y5uUNJolJT3Y)


These are **cache write strategies** that decide:

**When data is written to cache vs. written to database (DB).**

Used in:

* Redis
* Memcached
* CPU caches
* File systems
* Databases
* In-memory caching layers

---

# 1. Why do we need write strategies?

When an application updates data, we must answer:

### Should we update the DB first or the cache first?

### Should both be updated immediately?

### Should cache skip some writes?

These strategies control:

* Data consistency
* Performance
* Latency
* Cache freshness

---

# 2. Write-Through Cache

(Write to **cache + DB** together)

---

## Simple Meaning

Every write goes to **both**:

1. Cache
2. Database

Cache always stays fresh.

---

## How it Works (Very Simple)

```
write(data):
    cache.set(key, data)
    db.write(data)
    return success
```

---

## Pros

* Cache always contains the latest data
* Strong consistency
* No stale cache

---

## Cons

* Slower writes (because DB is always hit)
* High write workload causes performance drop

---

## Best Use Case

* Read-heavy systems
* Data must always be correct
* Product catalog, user profiles
* Systems where stale reads are unacceptable

---

# 3. Write-Back Cache

(Write to **cache only**, DB is updated **later**)

---

## Simple Meaning

Writes go to **cache first**.
Database is updated **asynchronously** by a background worker.

Fastest writing strategy.

---

## How it Works

```
write(data):
    cache.set(key, data)
    asyncQueue.add(key)
    return success
```

Background worker:

```
while tasks:
    db.write(key, data)
```

---

## Pros

* Very fast writes
* Great performance under heavy write load
* Reduces pressure on DB

---

## Cons

* Risk of data loss if cache crashes
* DB may lag behind cache
* Complex to implement
* Harder consistency guarantees

---

## Best Use Case

* Analytics
* Logging systems
* High-write workloads
* Systems that can tolerate eventual consistency

---

# 4. Write-Around Cache

(Write to **DB only**, skip the cache)

---

## Simple Meaning

New data is written **only to DB**,
cache is **not updated** immediately.

Cache is updated **only when read**.

---

## How it Works

```
write(data):
    db.write(data)   // cache not touched
```

On next read:

```
if cache miss:
     data = db.read()
     cache.set(data)
```

---

## Pros

* Reduces cache pollution
  (cache won’t store items that are rarely used)
* Good when writes are high but reads are low

---

## Cons

* First read after write = cache miss
* Cache may contain stale data until it expires

---

## Best Use Case

* Write-heavy, read-light workloads
* Logging
* Batch processing
* Data that is not frequently re-read

---

# 5. Comparison Table (Very Clear)

| Strategy      | Write Location        | Read Freshness   | Write Speed | Best For              | Weakness           |
| ------------- | --------------------- | ---------------- | ----------- | --------------------- | ------------------ |
| Write-Through | Cache + DB            | Always fresh     | Slow        | Strong consistency    | High write latency |
| Write-Back    | Cache only (DB later) | Very fresh cache | Fast        | Heavy writes          | Risk of data loss  |
| Write-Around  | DB only               | Stale until read | Medium      | Write-heavy workloads | First read miss    |

---

# 6. Real-World Examples

### Write-Through

* Redis persistence + immediate DB sync
* Financial systems
* Inventory counters

### Write-Back

* CPU cache
* Browser caching
* Message queues & log aggregators

### Write-Around

* Systems where write data is rarely re-read
* ETL pipelines

---

# 7. Which Should You Use?

### Choose Write-Through if:

* You need correctness
* You cannot tolerate stale data
* Reads are much more frequent than writes

### Choose Write-Back if:

* You want fastest writes
* Database is expensive to hit
* You can tolerate eventual consistency

### Choose Write-Around if:

* Writes are frequent
* Read-after-write is rare
* You want cache to remain clean

---

# 8. Interview Summary (Perfect 30-second answer)

Write-Through writes data to both cache and DB, giving strong consistency but slower writes.
Write-Back writes only to cache and flushes to DB later, giving the fastest writes but risks inconsistency.
Write-Around writes only to DB, avoiding cache pollution but causing cache misses on first read.
