# MTU and Packet Fragmentation

![](https://network-insight.net/wp-content/uploads/2015/10/rsz_1ipv6_path_mtu_discovery.png)

---

# 1. What is MTU?

**MTU = Maximum Transmission Unit**

Meaning:
The **largest possible packet size** that a network link can carry in one piece without breaking it.

Example MTU values:

* Ethernet: **1500 bytes**
* WiFi: around **2304 bytes**
* PPPoE: **1492 bytes**
* VPN tunnels: usually **lower** because extra headers are added

Think of MTU like:

**The maximum size of a parcel a courier company can deliver without splitting it.**

If packet size ≤ MTU → send in one piece
If packet size > MTU → must be **fragmented** (broken into smaller pieces)

---

# 2. Why MTU Matters

If MTU is too small → too many packets → slow
If MTU is too large → fragmentation → slow + overhead

So correct MTU is very important for:

* Network speed
* Latency
* Video streaming
* Gaming
* VPN connections
* API calls
* Cloud servers

---

# 3. What is Packet Fragmentation?

**When a packet is bigger than MTU, the network splits it into smaller packets.**

This process is called **fragmentation**.

Example:

If MTU = 1500 bytes
And packet size = 3000 bytes

Then packet becomes:

* Fragment 1: 1500 bytes
* Fragment 2: 1500 bytes

On the receiver side, these fragments get **reassembled** into the original packet.

---

# 4. Why Fragmentation Happens

Because different networks have **different MTU sizes**.

For example:

Your computer → Router (MTU 1500) → VPN Tunnel (MTU 1400) → Internet (MTU 1500)

If your computer sends a **1500-byte** packet, VPN tunnel cannot handle it.
So fragmentation happens.

---

# 5. Issues Caused By Fragmentation

Fragmentation slows everything down.

Common problems:

### 1. Lower performance

Fragments = multiple packets = more overhead.

### 2. Packet loss increases

If **one** fragment is lost, **entire original packet** is lost.

### 3. Firewalls may block fragments

Some firewalls drop fragmented packets for safety.

### 4. Path MTU issues

Sometimes, nodes do not allow ICMP messages, so sender cannot discover correct MTU.
This causes the famous:

**Black Hole MTU Problem**
Packets disappear silently.

---

# 6. Path MTU Discovery (PMTUD)

To avoid fragmentation, systems use **PMTUD**.

Idea:

Sender finds the **minimum MTU** on the path
and then sends packets of that size.

Example:

1500 → 1472 → 1460 → 1400 → finally finds the safe size.

---

# 7. Example: Why VPNs reduce MTU

VPN adds extra headers (50–70 bytes).
So MTU must be reduced.

Normal Ethernet: 1500
VPN MTU often: 1400 or 1380

If you don’t reduce MTU → fragmentation → slow VPN.

---

# 8. Simple Analogy

Imagine shipping a large item through a tunnel:

* Tunnel height = MTU
* Your item height = Packet size

If item > tunnel → you must cut it into smaller pieces.

---

# 9. Real Internet Example

HTTP request data: 5000 bytes
MTU: 1500 bytes

Actual packets sent:

Packet 1: 1500 bytes
Packet 2: 1500 bytes
Packet 3: 1500 bytes
Packet 4: 500 bytes

Receiver reassembles these 4 back into one data chunk.

---

# 10. LLD Concepts Involved (Important)

LLD interviews expect you to know:

* How large data is split
* How reassembly works
* Effect of fragmentation on performance
* When nodes should avoid fragmentation
* Why we adjust MTU to optimize performance
* How protocols like TCP try to avoid fragmented packets

These concepts directly relate to:

* Load balancers
* Reverse proxies
* API gateways
* High-performance servers
* Real-time apps
* Video streaming
* Microservices networking

---

# 11. Summary 

| Concept       | Meaning                                   |
| ------------- | ----------------------------------------- |
| MTU           | Maximum allowed packet size               |
| Fragmentation | Breaking a large packet into smaller ones |
| Why needed?   | When packet > MTU                         |
| Problem       | Slow, overhead, possible packet loss      |
| PMTUD         | Finds the best MTU automatically          |
| VPN/LB        | Often reduce MTU, causing fragmentation   |

---
