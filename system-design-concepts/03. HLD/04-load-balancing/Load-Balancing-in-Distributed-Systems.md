
# Load Balancing in Distributed Systems
![](https://substackcdn.com/image/fetch/f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F400e92f8-7e84-4ba6-9443-74368c1eaeb6_3735x3573.jpeg)


Load balancing is a **core pillar** of distributed system design.
Its goal is simple:

**Distribute workload across multiple nodes so no single node gets overloaded, and the system stays fast, scalable, and reliable.**

---

# 1. Why Do Distributed Systems Need Load Balancing?

Distributed systems have many servers/services working together.

If load is not balanced:

* One server gets overloaded
* Some servers stay idle
* Requests fail or slow down
* System becomes unreliable
* Traffic spikes crash the entire application

Load balancing ensures:

* **Equal load distribution**
* **High availability**
* **Fault tolerance**
* **Scalability**
* **Optimal resource usage**

---

# 2. What Does a Load Balancer Do in a Distributed System?

### 1. Distributes Requests

Spreads incoming requests across backend nodes.

### 2. Monitors Node Health

Checks if nodes are alive and fast.

### 3. Handles Failover

If a node dies → it's removed automatically.

### 4. Supports Auto-Scaling

New nodes can join smoothly.

### 5. Improves Performance

Minimizes latency by choosing the best node.

### 6. Provides Abstraction

Clients don’t know which node serves them.

---

# 3. Types of Load Balancing in Distributed Systems

Load balancing happens at multiple layers:

## A. **Client-Side Load Balancing**

Client picks the server.

Examples:

* gRPC client-side LB
* Netflix Ribbon
* Service mesh sidecars (Envoy)

Benefits:

* No central LB bottleneck
* Faster (no extra hop)

Drawback:

* Client must maintain service registry

---

## B. **Server-Side (Centralized) Load Balancing**

A central LB forwards requests to backend servers.

Examples:

* NGINX
* HAProxy
* AWS ELB / ALB / NLB
* Google Cloud LB

Benefits:

* Simpler for clients
* Best for web apps & APIs

Drawback:

* LB can become bottleneck (solve via Active-Active LBs)

---

## C. **DNS Load Balancing**

DNS returns multiple IPs → clients choose.

Used in:

* Google
* Cloudflare
* CDNs

Drawback:

* DNS caching = slow propagation

---

## D. **Global Load Balancing (GSLB)**

Used for **multi-region** architectures.

Decides:

* Which region to serve a user from
* Based on latency, geography, capacity

Examples:

* Route 53 latency routing
* Cloudflare Anycast
* Akamai GSLB

---

# 4. Load Balancing Algorithms (Very Important)

## 1. **Round Robin**

Each server gets equal requests.

## 2. **Weighted Round Robin**

Servers with more power get more load.

## 3. **Least Connections**

Server with fewest active connections gets the request.

## 4. **Shortest Response Time**

Choose server responding fastest.

## 5. **IP Hash**

Same user always maps to same server (sticky sessions).

## 6. **Consistent Hashing**

Used for distributed caching, sharding, microservices routing.

## 7. **Random + Power of Two Choices**

Pick 2 random servers → choose the less loaded one.
Super effective and widely used at scale.

---

# 5. Load Balancing in Microservices

Microservices require load balancing at:

### A. **Ingress Layer**

External traffic → API Gateway → Load Balancer → Services

### B. **Service-to-Service Load Balancing**

Service mesh handles routing internally.

Examples:

* Istio
* Linkerd
* Envoy

### C. **Database Layer Load Balancing**

Reads → replicas
Writes → primary

---

# 6. Load Balancing and Fault Tolerance

Load balancers help achieve HA:

1. Detect node failures
2. Stop routing traffic to unhealthy nodes
3. Reroute instantly to healthy ones
4. Auto-heal when failed nodes come back

This is why LB is a fundamental part of:

* Active-Active architectures
* Multi-zone deployments
* Blue-Green deployments
* Canary releases
* Auto-scaling groups

---

# 7. Placement of Load Balancers in Distributed Systems

Load balancers exist at **multiple layers**:

```
[Client]
   ↓
[Global Load Balancer]  (Geo routing)
   ↓
[Regional Load Balancer]  (Zone selection)
   ↓
[App Load Balancer]  (HTTP routing)
   ↓
[Service Mesh / Sidecar] (Internal service LB)
   ↓
[Backend Services]
   ↓
[Database / Cache Load Balancing]
```

Every stage smoothens load handling and failure recovery.

---

# 8. Advanced Load Balancing Concepts

### 1. Circuit Breakers

Stop sending traffic to overloaded instances.

### 2. Rate Limiting

Prevent a single client from overwhelming the system.

### 3. Backpressure

Slow down producers when consumers are overloaded.

### 4. Priority Routing

High-priority requests → best-performing servers

### 5. Blue-Green & Canary Routing

Traffic is split gradually during deployments.

---

# 9. Challenges in Load Balancing Distributed Systems

### 1. State Management

Stateful servers make balancing harder.
Solution → Use Redis for shared sessions.

### 2. Distributed Caching

Cache must stay consistent across nodes.

### 3. Failover Logic

Promoting new nodes must be fast and safe.

### 4. Network Latency Differences

LB must choose servers based on network health.

### 5. Hotspots & Uneven Load

Solved using:

* Consistent Hashing
* Power-of-two choices

### 6. Scalability Limits of LB

Fix by using:

* Multiple LBs in Active-Active
* DNS load balancing
* Anycast

---

# 10. Interview Summary (Perfect 30-second answer)

Load balancing distributes workload across multiple nodes to ensure scalability, high availability, and better performance in distributed systems. It can be client-side, server-side, DNS, or global.

Algorithms like Round Robin, Least Connections, and Consistent Hashing decide how requests are routed. Load balancers also perform health checks, handle failover, support auto-scaling, and improve system reliability.

Load balancing is essential for microservices, distributed databases, global architectures, and cloud-native applications.

---

If you want, say **next** and I’ll continue with:

* **next: Horizontal vs Vertical Scaling**
* **next: L4 vs L7 Load Balancing (deep dive)**
* **next: API Gateway vs Load Balancer**
* **next: Reverse Proxy vs Load Balancer**
* **next: Global Load Balancing (Anycast, GeoDNS, GSLB)**
