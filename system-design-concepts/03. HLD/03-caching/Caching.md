# Caching - System Design Complete Guide

## The Problem: Why We Need Caching

### The Performance Bottleneck Problem

Consider a typical web application without caching:

```
User requests data → Application server → Database query → Process data → Return response
```

This process creates several performance issues:

1. **Database Overload**: Every request hits the database
2. **Network Latency**: Multiple network calls between components
3. **CPU Intensive Operations**: Repeated processing of same data
4. **Slow Response Times**: Users wait for complete processing cycles

### The Real-World Scenario: Viral Content

Imagine Twitter when a tweet goes viral:
- Millions of users request the same tweet simultaneously
- Without caching: Database gets hammered with identical queries
- Result: Slow responses, timeouts, or complete system failure
- With caching: First user fetches from database, millions served from cache

## The Solution: Caching

### What is Caching?

Caching is storing frequently accessed data in fast, temporary storage to reduce access time and improve system performance.

**Simple Analogy**: 
- Without cache: Every time you need a book, you go to the library (database)
- With cache: Keep frequently used books on your desk (cache) for quick access

### How Caching Works - Step by Step

![](https://media.geeksforgeeks.org/wp-content/uploads/20240110183740/Cache-Working.jpg)
#### First Request (Cache Miss)
```
User requests data → Check cache (not found) → Query database → Process data → Store in cache → Return response
```

#### Subsequent Requests (Cache Hit)
```
User requests same data → Check cache (found) → Immediately return cached data
```

### Cache Performance Impact

**Without Cache**:
- Response time: 200ms (database query + processing)
- Database load: 1000 queries/second

**With Cache**:
- Cache hit response time: 5ms (memory access)
- Database load: 100 queries/second (90% cache hit rate)
- 10x performance improvement

## Types of Caching Architectures

### 1. Application Server Cache

![](https://media.geeksforgeeks.org/wp-content/uploads/20240212140144/Application-Server-Cache-(1).webp)
#### How It Works
- Cache resides within the application server
- Each server maintains its own local cache
- Fastest access but limited scope

#### Architecture
```
[Load Balancer] → [App Server 1 + Cache] 
                → [App Server 2 + Cache]
                → [App Server 3 + Cache]
                → [Database]
```

#### Use Case
- Small to medium applications
- When data consistency requirements are moderate
- Limited number of application servers

#### Limitations
- **Cache Inconsistency**: Each server has different cached data
- **Memory Waste**: Same data cached multiple times
- **Scalability Issues**: Adding servers doesn't increase cache efficiency

### 2. Distributed Cache

![](https://media.geeksforgeeks.org/wp-content/uploads/20240110183539/Distributed-Cache.jpg)
#### How It Works
- Cache is distributed across multiple nodes
- Uses consistent hashing to route requests
- Each node stores a portion of the total cache

#### Architecture
```
[Client] → [Load Balancer] → [App Servers] → [Distributed Cache Cluster] → [Database]
```

#### Key Features
- **Horizontal Scaling**: Add more cache nodes as needed
- **Data Partitioning**: Cache divided using consistent hashing
- **High Availability**: Replication and failover mechanisms

#### Implementation Example
Using Redis Cluster:
- 6 nodes: 3 master, 3 replica
- Data automatically sharded across masters
- Automatic failover if master fails

### 3. Global Cache

![](https://media.geeksforgeeks.org/wp-content/uploads/20240110183609/Global-Cache.jpg)
#### How It Works
- Single, centralized cache space
- All application servers use the same cache
- Two variations:

**Version A - Cache manages data fetching**:
```
App Server → Global Cache → (if miss) → Database
```

**Version B - App manages data fetching**:
```
App Server → Global Cache → (if miss) → App Server → Database
```

#### Use Cases
- When strong cache consistency is required
- Systems with high read-to-write ratio
- Applications needing shared cache state

### 4. CDN (Content Delivery Network)

![](https://media.geeksforgeeks.org/wp-content/uploads/20240110183629/CDN-new.jpg)

#### How It Works
- Geographically distributed cache servers
- Serves static content from locations closest to users
- Reduces latency for global user base

#### Architecture
```
User in India → CDN Edge (Mumbai) → (if miss) → Origin Server
User in USA → CDN Edge (New York) → (if miss) → Origin Server
```

#### Content Types for CDN
- Static images, CSS, JavaScript files
- Videos and audio files
- Downloadable documents
- Static HTML pages

## Cache Invalidation Strategies

### The Cache Coherency Problem

When source data changes, cached copies become stale. We need strategies to keep cache and source data synchronized.

### 1. Time-Based Expiration (TTL)

**How it works**: Cache entries automatically expire after fixed time
```python
# Set cache with 1-hour expiration
cache.set("user:123", user_data, ttl=3600)
```

**Pros**: Simple to implement, predictable memory usage
**Cons**: Data may be stale before expiration, unnecessary refreshes

### 2. Write-Through Cache

**How it works**: Write operations update both cache and database simultaneously
```
Update user → Update cache → Update database → Return success
```

**Pros**: Strong consistency, cache always up-to-date
**Cons**: Higher write latency, both systems must be available

### 3. Write-Behind Cache

**How it works**: Write to cache immediately, batch updates to database later
```
Update user → Update cache → Return success → Async update database
```

**Pros**: Very fast writes, can batch database operations
**Cons**: Risk of data loss if cache fails, eventual consistency

### 4. Refresh-Ahead Cache

**How it works**: Proactively refresh cache before expiration
```python
# Refresh cache when 80% of TTL has passed
if cache.age("user:123") > 0.8 * ttl:
    background_refresh("user:123")
```

**Pros**: Eliminates cache miss penalties
**Cons**: Wasted resources if data not accessed

## Cache Eviction Policies

### The Memory Management Problem

Cache size is limited. When cache is full and new data needs to be stored, we must decide which existing data to remove.

### Common Eviction Policies

#### 1. LRU (Least Recently Used)
- Remove the item that hasn't been accessed for the longest time
- Based on temporal locality principle
- Implementation: Doubly linked list + Hash map

**Example**:
```
Cache: [A, B, C, D]  # A is oldest, D is newest
Access B → [B, C, D, A]  # B moved to most recent
Add E (cache full) → [C, D, A, E]  # B removed (least recently used)
```

#### 2. LFU (Least Frequently Used)
- Remove the item with the fewest accesses
- Tracks access frequency for each item
- Better for stable access patterns

**Example**:
```
Access counts: A=5, B=3, C=8, D=1
Add E (cache full) → Remove D (lowest frequency)
```

#### 3. FIFO (First-In-First-Out)
- Remove the oldest item regardless of usage
- Simple queue implementation
- Poor performance for frequently accessed items

#### 4. Random Replacement
- Randomly select an item to evict
- Simple implementation
- Reasonable performance for large caches

## Real-World Caching Applications

### 1. Web Page Caching

**Problem**: Slow page loads due to repeated processing
**Solution**: Cache rendered HTML pages
```nginx
# Nginx configuration for page caching
location /products {
    proxy_cache products_cache;
    proxy_cache_valid 200 10m;  # Cache successful responses for 10 minutes
}
```

### 2. Database Query Caching

**Problem**: Repeated expensive database queries
**Solution**: Cache query results
```sql
-- Without cache
SELECT * FROM users WHERE country = 'US' AND status = 'active';

-- With cache (pseudocode)
cache_key = "users:country:US:status:active"
result = cache.get(cache_key)
if not result:
    result = db.query("SELECT * FROM users WHERE country = 'US' AND status = 'active'")
    cache.set(cache_key, result, ttl=300)
```

### 3. Session Caching

**Problem**: User session data storage and retrieval
**Solution**: Store sessions in fast cache instead of database
```python
# Store user session in Redis
redis.setex(f"session:{session_id}", 3600, session_data)

# Retrieve session
session_data = redis.get(f"session:{session_id}")
```

### 4. API Response Caching

**Problem**: External API calls are slow and rate-limited
**Solution**: Cache API responses
```python
def get_weather_data(city):
    cache_key = f"weather:{city}"
    cached_data = cache.get(cache_key)
    
    if cached_data:
        return cached_data
    
    # Expensive API call
    fresh_data = weather_api.get_forecast(city)
    cache.set(cache_key, fresh_data, ttl=900)  # 15 minutes
    return fresh_data
```

## Cache Implementation Considerations

### When to Use Caching

#### Good Candidates for Caching
- **Read-heavy workloads**: 80% reads, 20% writes
- **Expensive computations**: Complex calculations or data processing
- **External API calls**: Rate-limited or slow external services
- **Static or semi-static data**: Product catalogs, user profiles, configuration

#### Poor Candidates for Caching
- **Write-heavy workloads**: Frequent updates make cache ineffective
- **Real-time data**: Stock prices, live sports scores
- **Highly personalized data**: User-specific calculations
- **Large binary data**: Better served by CDN or object storage

### Cache Size Planning

#### Calculating Optimal Cache Size
```
Required_cache_size = (working_set_size * safety_factor) / desired_hit_ratio

Where:
working_set_size = Amount of frequently accessed data
safety_factor = 1.2-1.5 (for overhead and growth)
desired_hit_ratio = Target cache hit rate (e.g., 0.8 for 80%)
```

#### Example Calculation
```
Frequently accessed user profiles: 100,000 records
Average profile size: 2 KB
Working set size = 100,000 * 2 KB = 200 MB
With safety factor 1.3 = 260 MB
Target 80% hit ratio → 260 MB / 0.8 = 325 MB cache needed
```

## Advanced Caching Patterns

### 1. Cache-Aside Pattern (Lazy Loading)

**Pattern**: Application code manages cache population
```python
def get_user(user_id):
    # Try cache first
    user = cache.get(f"user:{user_id}")
    if user:
        return user
    
    # Cache miss - load from database
    user = db.query("SELECT * FROM users WHERE id = ?", user_id)
    if user:
        cache.set(f"user:{user_id}", user, ttl=3600)
    return user
```

**Pros**: Simple, only caches requested data
**Cons**: Cache miss penalty, potential for stale data

### 2. Read-Through Pattern

**Pattern**: Cache automatically loads data on miss
```python
# Cache configured with read-through handler
cache = ReadThroughCache(
    backend=redis,
    loader=lambda key: db.get(key.split(":")[1])
)
```

**Pros**: Cleaner application code, automatic cache population
**Cons**: More complex cache configuration

### 3. Write-Through Pattern

**Pattern**: All writes go through cache to database
```python
def update_user(user_id, data):
    # Update cache and database
    cache.set(f"user:{user_id}", data)
    db.update("users", user_id, data)
```

**Pros**: Strong consistency, cache always current
**Cons**: Higher write latency

## Monitoring and Metrics

### Key Cache Metrics to Monitor

#### 1. Cache Hit Rate
```
Hit Rate = Cache Hits / (Cache Hits + Cache Misses)
```
- **Target**: 80-95% for most applications
- **Low hit rate indicates**: Wrong data cached, cache too small

#### 2. Cache Latency
- Average response time for cache operations
- Should be significantly faster than database

#### 3. Memory Usage
- Percentage of cache memory used
- Monitor for memory pressure and eviction rates

#### 4. Eviction Statistics
- Rate of cache evictions
- Indicates if cache size is appropriate

### Cache Monitoring Tools

#### Application Level
- Custom metrics in application code
- Logging cache performance statistics

#### Infrastructure Level
- Redis/Memcached monitoring tools
- System resource monitoring
- Distributed tracing

## Common Caching Pitfalls and Solutions

### 1. Cache Stampede

**Problem**: Many requests for same expired data cause simultaneous cache misses
**Solution**: Use cache locking or early refresh
```python
def get_with_lock(key, loader, ttl=300):
    with cache_lock(key):
        data = cache.get(key)
        if not data:
            data = loader()
            cache.set(key, data, ttl)
        return data
```

### 2. Thundering Herd

**Problem**: Many clients request same uncached data simultaneously
**Solution**: Use background refresh or exponential backoff
```python
def get_with_background_refresh(key, loader, ttl=300, refresh_ttl=60):
    data = cache.get(key)
    if not data:
        data = loader()
        cache.set(key, data, ttl)
    elif cache.ttl(key) < refresh_ttl:
        # Refresh in background
        threading.Thread(target=background_refresh, args=(key, loader, ttl)).start()
    return data
```

### 3. Cache Penetration

**Problem**: Requests for non-existent data cause cache misses
**Solution**: Cache negative results
```python
def get_user(user_id):
    cache_key = f"user:{user_id}"
    result = cache.get(cache_key)
    
    if result is None:  # Not in cache
        user = db.get_user(user_id)
        if user:
            cache.set(cache_key, user, ttl=3600)
        else:
            # Cache negative result for shorter time
            cache.set(cache_key, "NOT_FOUND", ttl=60)
        return user
    
    elif result == "NOT_FOUND":
        return None
    
    else:
        return result
```

## Summary

Caching is a critical performance optimization technique that addresses the fundamental problem of slow data access by storing frequently used data in fast, temporary storage.

### Key Takeaways:

1. **Use caching for**: Read-heavy workloads, expensive computations, static data
2. **Choose appropriate architecture**: Application cache, distributed cache, global cache, or CDN based on requirements
3. **Implement proper invalidation**: TTL, write-through, or write-behind based on consistency needs
4. **Monitor performance**: Track hit rates, latency, and memory usage
5. **Avoid common pitfalls**: Cache stampede, thundering herd, cache penetration

### When Implementing Caching:

- Start with simple application-level caching
- Progress to distributed caching as scale demands
- Use CDN for static content and global user base
- Always monitor and tune cache performance
- Plan cache size based on working set analysis

Caching, when properly implemented, can provide order-of-magnitude performance improvements and significantly reduce load on backend systems, making it an essential tool in modern system design.