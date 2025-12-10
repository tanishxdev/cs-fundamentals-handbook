# Cache Invalidation Strategies

Simple, clear, & complete explanation

---

# 1. What is Cache Invalidation?

Caching means storing data temporarily (Redis, CDN, Browser Cache) for faster reads.

But when the **original data changes**, the cached copy becomes **stale**.

Cache invalidation =
**How to update or remove old cache when data changes.**

This is one of the hardest problems in system design.

---

# 2. Why Cache Invalidation Is Hard

* Cached data becomes old
* Many services may use the same cached value
* Cache may be distributed across multiple servers
* Updates may happen at different times
* Real-time consistency is difficult

If invalidation fails:

* Users see stale data
* Bugs appear only sometimes
* Behavior becomes unpredictable

---

# 3. Goals of a Good Cache Strategy

* Fresh data
* Fast responses
* Low cache misses
* Minimal load on DB
* No stale reads
* Easy to scale

---

# 4. Main Cache Invalidation Strategies

(These are the ones interviewers care about)

---

# Strategy 1: **Cache Aside (Lazy Loading)**

![](https://media.licdn.com/dms/image/v2/D4D22AQH4HK0q1ZFUUw/feedshare-shrink_800/feedshare-shrink_800/0/1705046411944?e=2147483647&v=beta&t=DxV0m4Lpim8Fbl-AB2rGH04dcrUcpXXezXQl-iV93ko)
Most popular strategy (used by Netflix, Reddit, Uber, etc.)

## How it works

1. Application checks cache
2. If **miss** → fetch from DB → store in cache → return
3. If **hit** → return from cache
4. When data changes → **invalidate cache entry manually**

## Diagram Logic

```
Read:
 if cache has data -> return
 else -> read DB -> write to cache -> return

Write:
 write to DB
 delete cache entry
```

## Pros

* Simple
* Only caches what is needed
* DB is source of truth

## Cons

* First request after eviction is slow
* Cache & DB can become inconsistent for a short time

---

# Strategy 2: **Write-Through Cache**
![](https://substackcdn.com/image/fetch/$s_!sVbB!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F8f5705fc-d252-4c66-9bfd-209bd106a17a_2096x1086.png)

Every write goes to:

1. Cache
2. Database

At the same time.

## How it works

```
write(data):
  cache.set(key, data)
  db.write(data)
```

## Pros

* Cache always fresh
* No stale reads

## Cons

* Slower writes
* High write volume = expensive

Use when read consistency must be extremely strong.

---

# Strategy 3: **Write-Back (Write-Behind)**
![](https://substackcdn.com/image/fetch/$s_!ySIW!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F80993b71-e643-4fd7-9ea1-a968a7a5f2cf_2096x1086.png)


Application writes **only to cache**.
Cache asynchronously writes to DB in background.

## How it works

```
write(data):
  cache.set(key, data)
  background_worker.write_to_db_later()
```

## Pros

* Fast writes
* Good for high-write systems (logging, analytics)

## Cons

* Risk of data loss if cache crashes
* DB may lag
* Hard to implement

Used mainly when DB does not need real-time consistency.

---

# Strategy 4: **Time-to-Live (TTL)**
![](https://assets.gcore.pro/site-media/uploads-staging/what_is_time_to_live_how_it_works_1_9d2de95452.png)

Set an expiry time.

After TTL passes, cache entry auto-expires.

## Example

User profile cached for 10 minutes.

## Pros

* Simple
* Self-cleaning cache
* Reduces stale data problems

## Cons

* Stale data until TTL expires
* Popular items may expire while still needed

Used in CDNs, browsers, Redis keys, API caching.

---

# Strategy 5: **Refresh-Ahead (Proactive Refresh)**
![](https://www.enjoyalgorithms.com/static/refresh-ahead-caching-pattern-fe95cbadb7e89b4b9ed04bba3a130a1a.png)
Before cache expires, system refreshes it.

## How it works

If TTL = 60 sec,
At 55 sec → refresh data automatically.

## Pros

* No slow requests
* Cache stays warm

## Cons

* Might refresh unnecessary entries

Used in:

* Recommendation systems
* Dashboards
* Heavy-read endpoints

---

# Strategy 6: **Invalidate on Update**

Whenever the database item changes, remove or update the cache.

This is common with:

* Event-driven systems
* Pub/Sub (Redis, Kafka)
* Microservices

## How it works

1. DB is updated
2. Event triggers cache invalidation
3. All caches update themselves

## Pros

* Strong consistency
* Distributed systems stay in sync

## Cons

* Requires message queues
* Extra complexity

---

# 5. Choosing the Right Strategy (Very Simple Summary)

| Scenario                       | Best Strategy        |
| ------------------------------ | -------------------- |
| Mostly reads, few writes       | Cache-Aside          |
| Must always return fresh data  | Write-Through        |
| Very high-write systems        | Write-Back           |
| Don’t care about slight delay  | TTL                  |
| Need cache always warm         | Refresh-Ahead        |
| Distributed system with events | Invalidate on Update |

---

# 6. Real-world Examples

### Instagram Feed

Uses Cache-Aside + TTL

### Reddit Post Views

Uses Write-Back (bulk writes later)

### Amazon Product Catalog

Uses Write-Through (strong consistency)

### Netflix Catalog API

Uses Refresh-Ahead + distributed invalidation

---

# 7. Common Problems & Solutions

### 1. Stale Cache

Solution:
Invalidate on update, shorter TTL, write-through.

### 2. Thundering Herd Problem

Solution:
Refresh-ahead, request coalescing.

### 3. Cache Stampede

Many clients re-filling cache at once.
Solution:
Mutex locks, lazy reloading, jittered TTL.

### 4. Cache & DB Inconsistency

Solution:
Write-through or invalidate-on-update.

---

# 8. Interview Summary (30-second answer)

Cache invalidation ensures cached data stays consistent with the database.
Main strategies:

* Cache-Aside (read lazy, write invalidate) – most common
* Write-Through (write to both cache + DB)
* Write-Back (write to cache, later flush to DB)
* TTL expiration
* Refresh Ahead
* Event-driven invalidation

Each strategy balances speed, consistency, and complexity.

---