# API Pagination Strategies
![](https://media.licdn.com/dms/image/v2/D4E22AQHvUuqR2g2CmA/feedshare-shrink_800/B4EZQUF.avHkAk-/0/1735503899211?e=2147483647&v=beta&t=wtzDgaUeOKTCuypFSNVEd4l87li_g6ln8RINtw1LVrc)

---

(Offset • Cursor • Keyset Pagination)
Simple, clean, complete explanation

Pagination is required when an API returns a **large dataset**, so we break the data into smaller pages.

Example uses:

* Feeds (Instagram, Twitter)
* Product lists (Amazon)
* Database search results
* Scrolling APIs

Different pagination strategies determine **how the API selects the next set of records**.

---

# 1. Offset Pagination

(`LIMIT` + `OFFSET`)
The simplest & most common method.

---

## How it works

Client requests:

```
GET /users?limit=10&offset=20
```

Meaning:

* Skip first 20 records
* Return next 10

SQL example:

```sql
SELECT * FROM users
ORDER BY id
LIMIT 10 OFFSET 20;
```

---

## Pros

* Very easy to implement
* Works in almost every database
* Simple mental model

---

## Cons

### 1. Slow for large offsets

OFFSET 100000 means the DB scans 100000 rows → very slow.

### 2. Unstable with real-time updates

If rows are inserted or deleted while paginating:

Page 2 results shift (duplicate/missing items).

### 3. Bad for infinite scroll

Offset breaks if user scrolls too fast or data changes constantly.

---

## Best use-case

* Admin dashboards
* Static data
* Low-volume APIs
* Simple apps where correctness is not critical

---

# 2. Cursor Pagination

(`cursor` identifies the last fetched item)

Used by: **Facebook, Twitter, Instagram, YouTube**

---

## How it works

Instead of page numbers, the API returns a **cursor**.

Client requests:

```
GET /feed?cursor=xyz&limit=10
```

Cursor = token representing **where to continue next**.

Server selects items **after** that cursor.

Example:

```
SELECT * FROM posts
WHERE created_at < cursor_timestamp
ORDER BY created_at DESC
LIMIT 10;
```

---

## Pros

### 1. Very fast (uses index scans)

No scanning skipped rows.

### 2. Stable under live updates

New posts do not break pagination order.

### 3. Perfect for infinite scrolling

Cursor always points to the last known item.

---

## Cons

* Harder to implement
* Cannot jump to an arbitrary page (page 50)
* Cursors must be opaque (encoded/hashed)

---

## Best use-case

* Social media feeds
* Messaging apps
* Activity logs
* Any real-time data with inserts/deletes

---

# 3. Keyset Pagination

Similar to cursor, but key-based.
Also called: **Seek Pagination**.

Used heavily by SQL databases & high-scale systems.

---

## How it works

Use the **last record’s key value** to fetch the next page.

Example:

Last record on page 1: `id = 50`

Next page query:

```sql
SELECT * FROM orders
WHERE id > 50
ORDER BY id
LIMIT 10;
```

---

## Pros

### 1. Fastest form of pagination

Uses indexes → O(1) page lookups.

### 2. Very stable for large datasets

No offset scanning.
No shifting results.

### 3. Perfect for sorted data

Efficient for log-style tables.

---

## Cons

* Requires sortable, indexed columns
* Cannot jump to page numbers
* Not ideal for un-ordered datasets

---

## Best use-case

* Event logs
* Order lists
* Financial transactions
* Large tables with stable sort keys
* Systems requiring **low latency**

---

# 4. Offset vs Cursor vs Keyset

(Very Clear Comparison Table)

| Feature                 | Offset Pagination    | Cursor Pagination | Keyset Pagination       |
| ----------------------- | -------------------- | ----------------- | ----------------------- |
| Performance             | Slow for big offsets | Fast              | Very Fast               |
| Scalability             | Poor                 | Good              | Excellent               |
| Stability with new data | Weak                 | Strong            | Very Strong             |
| Jump to any page        | Yes                  | No                | No                      |
| Complexity              | Low                  | Medium            | Medium                  |
| Uses index              | No                   | Yes               | Yes                     |
| Infinite scroll         | Bad                  | Excellent         | Excellent               |
| Best for                | Simple apps          | Social feeds      | Logs, events, large DBs |

---

# 5. Which Should You Use?

### Choose **Offset Pagination** if:

* Simplicity matters
* Data is small
* Page numbers needed
* Admin tools / dashboards

### Choose **Cursor Pagination** if:

* Real-time data changes frequently
* Feeds and scroll-based content
* You want consistent ordering

### Choose **Keyset Pagination** if:

* Very large tables
* Performance-critical APIs
* You paginate based on sorted keys (id, timestamp)
* You want zero-scan pagination

---

# 6. Real-World Examples

### Facebook / Instagram feed

→ Cursor-based pagination (scrolling must be stable)

### Twitter timeline

→ Cursor + keyset mix using tweet ID (Snowflake ID)

### Banking transactions

→ Keyset, ordered by timestamp or id

### Bookstore admin panel

→ Offset pagination (simple & sufficient)

---

# 7. Interview-Ready Summary (Perfect 30-second answer)

Offset pagination uses LIMIT + OFFSET; simple but slow and unstable for large datasets.
Cursor pagination uses a pointer to the last item, scales well, and works best for real-time data like social feeds.
Keyset pagination is the fastest and most stable; it uses an indexed column (such as id or timestamp) to fetch the next page, ideal for large datasets or logs.

Offset = simple but slow.
Cursor = scalable and stable.
Keyset = fastest for large sorted datasets.

---
