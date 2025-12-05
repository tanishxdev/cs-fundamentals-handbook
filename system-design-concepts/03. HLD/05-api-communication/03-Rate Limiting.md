# Rate Limiting Algorithms - System Design Complete Guide
![](https://media.geeksforgeeks.org/wp-content/uploads/20240725172750/What-is-Rate-Limiting.png)
## The Problem: Why We Need Rate Limiting

### The Unlimited Access Problem

Imagine a popular API service without rate limiting:

- One user can make millions of requests per hour
- Malicious bots can overwhelm the system
- Fair usage becomes impossible
- System resources get exhausted
- Genuine users experience downtime

### Real-World Scenarios

**Without Rate Limiting:**
```
User A: 10,000 requests/minute → System overwhelmed
User B: 5 requests/minute → Gets errors due to User A
System: Crashes or becomes unresponsive
```

**With Rate Limiting:**
```
User A: 100 requests/minute → Limited after threshold
User B: 5 requests/minute → Works perfectly
System: Stable and responsive for all users
```

## Core Rate Limiting Algorithms

### 1. Token Bucket Algorithm

![](https://media.geeksforgeeks.org/wp-content/uploads/20240725172832/Tocken-Bucket-Algorithm.png)
#### Concept: Token-Based Allowance

**Analogy**: Imagine a bucket that gets filled with tokens at a fixed rate. Each request consumes one token. If tokens are available, request is allowed; otherwise, it's rejected.

#### How It Works

```
Bucket Capacity: 10 tokens
Refill Rate: 2 tokens per second

Initial State: Bucket full (10 tokens)
Request 1: Use 1 token → 9 tokens remaining
Request 2: Use 1 token → 8 tokens remaining
...
After 5 seconds: 10 tokens (refilled)
```

#### Implementation

```cpp
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

class TokenBucket {
private:
    double capacity_;           // Maximum tokens bucket can hold
    double tokens_;            // Current tokens in bucket
    double refill_rate_;       // Tokens added per second
    std::chrono::steady_clock::time_point last_refill_;
    std::mutex mutex_;

public:
    TokenBucket(double rate, double capacity) 
        : capacity_(capacity), tokens_(capacity), 
          refill_rate_(rate), last_refill_(std::chrono::steady_clock::now()) {}
    
    bool allowRequest(int tokens_required = 1) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Refill tokens based on time elapsed
        auto now = std::chrono::steady_clock::now();
        double seconds_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - last_refill_).count() / 1000.0;
        
        tokens_ += seconds_elapsed * refill_rate_;
        tokens_ = std::min(tokens_, capacity_);
        last_refill_ = now;
        
        // Check if enough tokens available
        if (tokens_ >= tokens_required) {
            tokens_ -= tokens_required;
            return true;
        }
        return false;
    }
    
    double getAvailableTokens() {
        std::lock_guard<std::mutex> lock(mutex_);
        return tokens_;
    }
};

// Demonstration
void demonstrateTokenBucket() {
    std::cout << "=== Token Bucket Algorithm Demo ===" << std::endl;
    
    // 2 tokens per second, capacity of 5 tokens
    TokenBucket bucket(2.0, 5.0);
    
    for (int i = 1; i <= 10; i++) {
        if (bucket.allowRequest()) {
            std::cout << "Request " << i << ": ALLOWED - Tokens: " 
                      << bucket.getAvailableTokens() << std::endl;
        } else {
            std::cout << "Request " << i << ": DENIED - Tokens: " 
                      << bucket.getAvailableTokens() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
```

#### Benefits
- **Burst Handling**: Allows short bursts up to bucket capacity
- **Flexible**: Easy to adjust rate and capacity
- **Memory Efficient**: Only stores token count and timestamp

#### Challenges
- **Time Synchronization**: Requires accurate timekeeping
- **Burst Limits**: Large bursts can still overwhelm system

### 2. Leaky Bucket Algorithm

![](https://media.geeksforgeeks.org/wp-content/uploads/20240725172914/Leaky-Bucket-Algorithm.png)
#### Concept: Constant Output Rate

**Analogy**: Imagine a bucket with a small hole at the bottom. Requests pour in at variable rates, but they leak out at a constant rate.

#### How It Works

```
Bucket Capacity: 10 requests
Leak Rate: 2 requests per second

Request arrives → Add to bucket if space available
Bucket leaks at constant rate → Process requests steadily
If bucket full → Reject new requests
```

#### Implementation

```cpp
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>

class LeakyBucket {
private:
    size_t capacity_;          // Maximum queue size
    double process_rate_;      // Requests processed per second
    std::queue<std::chrono::steady_clock::time_point> queue_;
    std::chrono::steady_clock::time_point last_leak_;
    std::mutex mutex_;

public:
    LeakyBucket(size_t capacity, double process_rate) 
        : capacity_(capacity), process_rate_(process_rate),
          last_leak_(std::chrono::steady_clock::now()) {}
    
    bool allowRequest() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Process queued requests based on leak rate
        auto now = std::chrono::steady_clock::now();
        double seconds_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - last_leak_).count() / 1000.0;
        
        int requests_to_process = static_cast<int>(seconds_elapsed * process_rate_);
        
        for (int i = 0; i < requests_to_process && !queue_.empty(); i++) {
            queue_.pop();
        }
        
        last_leak_ = now;
        
        // Check if there's space for new request
        if (queue_.size() < capacity_) {
            queue_.push(now);
            return true;
        }
        return false;
    }
    
    size_t getQueueSize() {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }
};

// Alternative implementation using token-based approach
class SimpleLeakyBucket {
private:
    double capacity_;
    double water_level_;  // Current water level in bucket
    double leak_rate_;    // Leak rate per second
    std::chrono::steady_clock::time_point last_update_;
    std::mutex mutex_;

public:
    SimpleLeakyBucket(double rate, double capacity)
        : capacity_(capacity), water_level_(0.0), leak_rate_(rate),
          last_update_(std::chrono::steady_clock::now()) {}
    
    bool allowRequest(double request_size = 1.0) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Calculate water leaked since last update
        auto now = std::chrono::steady_clock::now();
        double seconds_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - last_update_).count() / 1000.0;
        
        water_level_ = std::max(0.0, water_level_ - seconds_elapsed * leak_rate_);
        last_update_ = now;
        
        // Check if request can be accommodated
        if (water_level_ + request_size <= capacity_) {
            water_level_ += request_size;
            return true;
        }
        return false;
    }
    
    double getWaterLevel() {
        std::lock_guard<std::mutex> lock(mutex_);
        return water_level_;
    }
};

// Demonstration
void demonstrateLeakyBucket() {
    std::cout << "\n=== Leaky Bucket Algorithm Demo ===" << std::endl;
    
    SimpleLeakyBucket bucket(2.0, 5.0);  // Leak 2 units/sec, capacity 5
    
    for (int i = 1; i <= 15; i++) {
        if (bucket.allowRequest()) {
            std::cout << "Request " << i << ": ALLOWED - Water Level: " 
                      << bucket.getWaterLevel() << std::endl;
        } else {
            std::cout << "Request " << i << ": DENIED - Water Level: " 
                      << bucket.getWaterLevel() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
```

#### Benefits
- **Smooth Output**: Provides consistent output rate
- **Memory Bound**: Fixed memory usage regardless of traffic
- **Predictable**: Easy to reason about system behavior

#### Challenges
- **No Burst Allowance**: Cannot handle legitimate bursts
- **Strict Enforcement**: May be too restrictive for some use cases

### 3. Fixed Window Algorithm

![](https://media.geeksforgeeks.org/wp-content/uploads/20240725172949/Fixed-Window-Algorithm.png)
#### Concept: Time-Based Windows

**Analogy**: Imagine counting requests in fixed time windows (e.g., per minute). Reset counter at the start of each new window.

#### How It Works

```
Window: 1 minute, Limit: 100 requests
Minute 1: 95 requests → Allowed
Minute 1: 5 more requests → Allowed (total 100)
Minute 1: 1 more request → Denied
Minute 2: Counter resets → Requests allowed again
```

#### Implementation

```cpp
#include <iostream>
#include <chrono>
#include <atomic>
#include <mutex>

class FixedWindow {
private:
    size_t max_requests_;
    std::chrono::seconds window_duration_;
    std::atomic<size_t> request_count_;
    std::chrono::steady_clock::time_point window_start_;
    std::mutex mutex_;

public:
    FixedWindow(size_t max_requests, std::chrono::seconds window_duration)
        : max_requests_(max_requests), window_duration_(window_duration),
          request_count_(0), window_start_(std::chrono::steady_clock::now()) {}
    
    bool allowRequest() {
        auto now = std::chrono::steady_clock::now();
        
        // Check if we're in a new window
        if (now - window_start_ >= window_duration_) {
            std::lock_guard<std::mutex> lock(mutex_);
            // Double-check after acquiring lock
            if (now - window_start_ >= window_duration_) {
                request_count_.store(0);
                window_start_ = now;
            }
        }
        
        // Check if under limit
        size_t current_count = request_count_.load();
        if (current_count < max_requests_) {
            // Atomically increment if still under limit
            while (!request_count_.compare_exchange_weak(current_count, current_count + 1)) {
                if (current_count >= max_requests_) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    
    size_t getCurrentCount() {
        return request_count_.load();
    }
    
    double getWindowProgress() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - window_start_);
        return static_cast<double>(elapsed.count()) / 
               static_cast<double>(window_duration_.count() * 1000);
    }
};

// Demonstration
void demonstrateFixedWindow() {
    std::cout << "\n=== Fixed Window Algorithm Demo ===" << std::endl;
    
    // 5 requests per 3-second window
    FixedWindow window(5, std::chrono::seconds(3));
    
    for (int i = 1; i <= 20; i++) {
        if (window.allowRequest()) {
            std::cout << "Request " << i << ": ALLOWED - Count: " 
                      << window.getCurrentCount() << "/5" 
                      << " Progress: " << (window.getWindowProgress() * 100) << "%" 
                      << std::endl;
        } else {
            std::cout << "Request " << i << ": DENIED - Count: " 
                      << window.getCurrentCount() << "/5" 
                      << " Progress: " << (window.getWindowProgress() * 100) << "%" 
                      << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
```

#### Benefits
- **Simple**: Easy to understand and implement
- **Memory Efficient**: Only stores counter and timestamp
- **Predictable**: Clear reset boundaries

#### Challenges
- **Boundary Bursts**: Allows bursts at window boundaries
- **Uneven Distribution**: Traffic can be uneven within window

### 4. Sliding Window Algorithm

![](https://media.geeksforgeeks.org/wp-content/uploads/20240725173030/Sliding-Window-Algorithm.png)
#### Concept: Moving Time Window

**Analogy**: Imagine a window that slides over time, only counting requests within the most recent time period.

#### How It Works

```
Window: 1 minute, Limit: 100 requests
Current time: 10:00:30
Count requests between 09:59:30 and 10:00:30
If count < 100 → Allow request
Else → Deny request
```

#### Implementation

```cpp
#include <iostream>
#include <chrono>
#include <deque>
#include <mutex>

class SlidingWindow {
private:
    size_t max_requests_;
    std::chrono::seconds window_duration_;
    std::deque<std::chrono::steady_clock::time_point> requests_;
    std::mutex mutex_;

public:
    SlidingWindow(size_t max_requests, std::chrono::seconds window_duration)
        : max_requests_(max_requests), window_duration_(window_duration) {}
    
    bool allowRequest() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto now = std::chrono::steady_clock::now();
        
        // Remove expired requests
        while (!requests_.empty() && 
               now - requests_.front() > window_duration_) {
            requests_.pop_front();
        }
        
        // Check if under limit
        if (requests_.size() < max_requests_) {
            requests_.push_back(now);
            return true;
        }
        return false;
    }
    
    size_t getCurrentCount() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto now = std::chrono::steady_clock::now();
        
        // Remove expired requests before counting
        while (!requests_.empty() && 
               now - requests_.front() > window_duration_) {
            requests_.pop_front();
        }
        return requests_.size();
    }
};

// Memory-optimized version using approximate counting
class ApproximateSlidingWindow {
private:
    size_t max_requests_;
    std::chrono::seconds window_duration_;
    std::deque<std::pair<std::chrono::steady_clock::time_point, size_t>> buckets_;
    size_t total_count_;
    std::chrono::steady_clock::time_point last_update_;
    std::mutex mutex_;

public:
    ApproximateSlidingWindow(size_t max_requests, std::chrono::seconds window_duration)
        : max_requests_(max_requests), window_duration_(window_duration),
          total_count_(0), last_update_(std::chrono::steady_clock::now()) {}
    
    bool allowRequest() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto now = std::chrono::steady_clock::now();
        
        // Remove expired buckets
        while (!buckets_.empty() && 
               now - buckets_.front().first > window_duration_) {
            total_count_ -= buckets_.front().second;
            buckets_.pop_front();
        }
        
        // Check if under limit
        if (total_count_ < max_requests_) {
            // Add to current bucket or create new one
            if (!buckets_.empty() && 
                now - buckets_.back().first < std::chrono::seconds(1)) {
                buckets_.back().second++;
            } else {
                buckets_.emplace_back(now, 1);
            }
            total_count_++;
            return true;
        }
        return false;
    }
};

// Demonstration
void demonstrateSlidingWindow() {
    std::cout << "\n=== Sliding Window Algorithm Demo ===" << std::endl;
    
    // 5 requests per 3-second window
    SlidingWindow window(5, std::chrono::seconds(3));
    
    for (int i = 1; i <= 20; i++) {
        if (window.allowRequest()) {
            std::cout << "Request " << i << ": ALLOWED - Count: " 
                      << window.getCurrentCount() << "/5" << std::endl;
        } else {
            std::cout << "Request " << i << ": DENIED - Count: " 
                      << window.getCurrentCount() << "/5" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
```

#### Benefits
- **Accurate**: Prevents boundary bursts
- **Fair**: More evenly distributes requests over time
- **Flexible**: Adapts to traffic patterns

#### Challenges
- **Memory Usage**: Stores individual request timestamps
- **Computational Overhead**: More complex than fixed window

## Advanced Implementation: Distributed Rate Limiting

### Redis-Based Distributed Rate Limiter

```cpp
#include <iostream>
#include <string>
#include <chrono>

// Simplified Redis client interface
class RedisClient {
public:
    bool setIfNotExist(const std::string& key, const std::string& value, 
                      int expiry_seconds) {
        // Implementation would connect to Redis
        std::cout << "Redis: SETNX " << key << " " << value 
                  << " EX " << expiry_seconds << std::endl;
        return true;
    }
    
    bool increment(const std::string& key) {
        std::cout << "Redis: INCR " << key << std::endl;
        return true;
    }
    
    int get(const std::string& key) {
        std::cout << "Redis: GET " << key << std::endl;
        return 0; // Simplified
    }
};

class DistributedRateLimiter {
private:
    RedisClient& redis_;
    std::string prefix_;
    
public:
    DistributedRateLimiter(RedisClient& redis, const std::string& prefix = "rate_limit")
        : redis_(redis), prefix_(prefix) {}
    
    bool allowRequest(const std::string& identifier, 
                     int max_requests, 
                     std::chrono::seconds window_duration) {
        std::string key = prefix_ + ":" + identifier;
        int window_seconds = window_duration.count();
        
        // Try to set key if not exists (start of window)
        bool is_new_window = redis_.setIfNotExist(
            key, "0", window_seconds);
        
        if (is_new_window) {
            // New window started, first request is allowed
            redis_.increment(key);
            return true;
        } else {
            // Existing window, check current count
            int current_count = redis_.get(key);
            if (current_count < max_requests) {
                redis_.increment(key);
                return true;
            }
            return false;
        }
    }
};
```

## Choosing the Right Algorithm

### Decision Framework

#### 1. Based on Traffic Pattern
- **Bursty Traffic**: Token Bucket
- **Steady Traffic**: Leaky Bucket  
- **Variable Traffic**: Sliding Window
- **Simple Needs**: Fixed Window

#### 2. Based on Implementation Complexity
- **Simple**: Fixed Window
- **Moderate**: Token Bucket, Leaky Bucket
- **Complex**: Sliding Window

#### 3. Based on Performance Requirements
- **High Performance**: Fixed Window, Token Bucket
- **Accuracy**: Sliding Window
- **Memory Efficiency**: Token Bucket, Fixed Window

#### 4. Comparison Table

| Algorithm | Burst Handling | Memory Usage | Accuracy | Implementation |
|-----------|----------------|--------------|----------|----------------|
| Token Bucket | ✅ Excellent | ✅ Low | ✅ Good | 🟡 Moderate |
| Leaky Bucket | ❌ Poor | ✅ Low | ✅ Good | 🟡 Moderate |
| Fixed Window | 🟡 Fair | ✅ Low | ❌ Poor | ✅ Easy |
| Sliding Window | ✅ Good | ❌ High | ✅ Excellent | ❌ Hard |

## Real-World Use Cases

### 1. API Rate Limiting
```cpp
class APIRateLimiter {
private:
    std::unordered_map<std::string, TokenBucket> user_buckets_;
    std::mutex mutex_;
    
public:
    bool allowAPIRequest(const std::string& user_id, const std::string& endpoint) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::string key = user_id + ":" + endpoint;
        
        // Create bucket if not exists
        if (user_buckets_.find(key) == user_buckets_.end()) {
            user_buckets_[key] = TokenBucket(10.0, 100.0); // 10 req/sec, burst 100
        }
        
        return user_buckets_[key].allowRequest();
    }
};
```

### 2. Login Attempt Limiting
```cpp
class LoginRateLimiter {
private:
    std::unordered_map<std::string, FixedWindow> attempt_counters_;
    std::mutex mutex_;
    
public:
    bool allowLoginAttempt(const std::string& ip_address) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (attempt_counters_.find(ip_address) == attempt_counters_.end()) {
            attempt_counters_[ip_address] = FixedWindow(5, std::chrono::minutes(1)); // 5 attempts per minute
        }
        
        return attempt_counters_[ip_address].allowRequest();
    }
    
    void resetAttempts(const std::string& ip_address) {
        std::lock_guard<std::mutex> lock(mutex_);
        attempt_counters_.erase(ip_address);
    }
};
```

## Best Practices

### 1. Graceful Response
```cpp
struct RateLimitResponse {
    bool allowed;
    int remaining;
    int reset_after; // seconds
    std::string limit_type;
};

class GracefulRateLimiter {
public:
    RateLimitResponse checkRateLimit(const std::string& user_id) {
        // Implementation that returns detailed response
        return RateLimitResponse{true, 95, 30, "user_hourly"};
    }
};
```

### 2. Hierarchical Rate Limiting
```cpp
class HierarchicalRateLimiter {
private:
    TokenBucket global_bucket_;
    std::unordered_map<std::string, TokenBucket> user_buckets_;
    
public:
    bool allowRequest(const std::string& user_id) {
        // Check global limit first
        if (!global_bucket_.allowRequest()) {
            return false;
        }
        
        // Then check user-specific limit
        // Implementation...
        return true;
    }
};
```

## Main Function with Demonstrations

```cpp
int main() {
    std::cout << "RATE LIMITING ALGORITHMS - SYSTEM DESIGN" << std::endl;
    std::cout << "========================================" << std::endl;
    
    demonstrateTokenBucket();
    demonstrateLeakyBucket();
    demonstrateFixedWindow();
    demonstrateSlidingWindow();
    
    std::cout << "\n=== All demonstrations completed ===" << std::endl;
    return 0;
}
```

## Summary

Rate limiting is essential for building scalable, secure, and fair systems. The choice of algorithm depends on your specific requirements:

- **Token Bucket**: Best for handling bursts while maintaining average rate
- **Leaky Bucket**: Best for smoothing out traffic and ensuring constant output rate  
- **Fixed Window**: Simplest to implement, good for basic needs
- **Sliding Window**: Most accurate, prevents boundary bursts

Consider your traffic patterns, performance requirements, and implementation complexity when choosing the right rate limiting strategy for your system.