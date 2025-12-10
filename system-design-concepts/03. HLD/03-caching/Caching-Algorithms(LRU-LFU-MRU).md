# Caching Algorithms

(LRU, LFU, MRU)
Simple, clear, complete explanation

These algorithms decide **which item to remove** when the cache is full.

---

# 1. Why do we need caching algorithms?

A cache has **limited space**.

When cache is full and a new item must be added:

**Which old item should be removed?**

Caching algorithms solve this problem.

Main goals:

* Maximize hit-rate
* Reduce cache misses
* Keep most useful items in memory

---

# 2. LRU (Least Recently Used)

LRU removes the item that was **least recently accessed**.

Meaning:
“If you haven’t used it for a long time, you probably don’t need it.”

---

## How LRU Works

You maintain:

* A **doubly linked list** (order of usage)
* A **hash map** (key → node in list)

Every time an item is accessed:

1. Move it to the **front** (most recently used)
2. When cache is full: remove from the **end** (least recently used)

---

## Example

Access sequence:
A, B, C, A, D, E

Cache capacity: 3

Steps:

1. A
2. A B
3. A B C
4. A B C (A becomes most recently used)
5. A C D (B removed – least recently used)
6. C D E (A removed)

---

## Best Use Case for LRU

* Web caches
* Database caches
* OS memory pages

LRU works well when **recent items are likely to be reused**.

---

# 3. LFU (Least Frequently Used)

LFU removes the item that is **least frequently accessed**.

Meaning:
“If you rarely use it, you don't need it.”

---

## How LFU Works

You maintain:

* A **frequency count** for each item
* A list/bucket of items for each frequency
* A hash map (key → frequency bucket)

Every access:

```
freq[key] += 1
move key to corresponding frequency bucket
```

When cache is full:

* Remove the item with **lowest frequency**
* If multiple items have same frequency → remove one with least recent access (LFU + LRU tie-breaker)

---

## Example

Access sequence:
A, B, A, C, A, B

Frequency:

A → 3
B → 2
C → 1

If cache full → remove C (freq = 1)

---

## Best Use Case for LFU

* You want items with long-term popularity
* Fast-changing data where frequency matters
* Recommendation engines
* Analytics dashboards

LFU works well when **popular items stay popular for a long time**.

---

# 4. MRU (Most Recently Used)

MRU removes the item that was **most recently accessed**.

Meaning:
“If you just used it, you’re unlikely to use it again soon.”

Opposite of LRU.

---

## Why MRU Exists

Some workloads show this pattern:

* You open a large file
* You read a small part
* You never return to it again

Some database queries also show MRU patterns.

---

## How MRU Works

* Track the **most recently used** item
* When cache is full → remove that item
* Because recently accessed = unlikely to be reused in these workloads

---

## Best Use Case for MRU

* When access pattern is **scanning**
* When most recent item is less likely to be reused
* Certain DB page replacement strategies

Examples:

* File scanning
* Streaming large datasets
* Big ETL jobs

---

# 5. Comparison Table (Very Clear)

| Algorithm | Removes               | Good For                     | Bad For                   |
| --------- | --------------------- | ---------------------------- | ------------------------- |
| LRU       | Least recently used   | Web caches, apps             | Cyclic access patterns    |
| LFU       | Least frequently used | Popular items, stable access | Items that spike suddenly |
| MRU       | Most recently used    | Scanning workloads           | Normal application usage  |

---

# 6. Which One Should You Choose?

## Choose **LRU** if:

* Recent items are likely to be accessed again
* General-purpose caching
* Works best for 80% workloads

## Choose **LFU** if:

* You want long-term popularity tracking
* Read-heavy workloads
* Items with stable popularity

## Choose **MRU** if:

* Access pattern is sequential scan
* Most recent items are least likely to repeat

---

# 7. Real-World Usage

### LRU

* Redis default eviction mode (volatile-lru)
* Browser cache
* Operating system page replacement
* CDN caches

### LFU

* Redis (volatile-lfu, allkeys-lfu)
* Memcached advanced mode
* Recommendation systems

### MRU

* Database systems (PostgreSQL, Oracle options)
* File systems scanning large files

---

# 8. Data Structures Used

### LRU

* HashMap + Doubly Linked List
  (Operations are O(1))

### LFU

* HashMap + Min-Heap or
* HashMap + Frequency Buckets
  (Operations are O(1) with bucket approach)

### MRU

* Very similar to LRU, but eviction target is the head (most recent)

---

# 9. Example Scenario (Very Clear)

Assume cache size = 2
Access pattern: A, B, A, C

### LRU

1. A B
2. A B
3. A C (B is removed)

### LFU

Frequencies:
A = 2
B = 1
C = 1
Least freq = B or C → remove B
Cache: A C

### MRU

MRU = A → remove A
Cache: B C

---

# 10. Interview Summary (Short and Perfect)

LRU removes the least recently used item.
LFU removes the least frequently used item.
MRU removes the most recently used item.

LRU is best for general caching.
LFU is best for long-term popularity.
MRU is best for sequential access patterns.

---