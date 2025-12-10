# Course: “System Design Math for Engineers”

## 🎯 Goal

To make you **comfortable doing quick back-of-the-envelope calculations** like:

* “How many requests per second?”
* “How much storage do we need per year?”
* “How many servers are required?”
* “Is this architecture scalable?”

This is **not hard math** — it’s **approximation thinking**.

---

# 📘 Table of Contents

### **Module 1: Core Thinking**

1. What is System Design Math?
2. The 3-Step Estimation Framework
3. Unit Conversions Made Easy
4. Rounding Rules for Quick Estimates

---

### **Module 2: Traffic Estimation**

1. Requests per Day → Requests per Second
2. Users vs Active Users vs Concurrent Users
3. Example: How many users can our server handle?

---

### **Module 3: Storage Estimation**

1. Calculating Storage per Object (image, video, post, etc.)
2. Growth per Month / Year
3. Compression & Retention
4. Example: Storage for a YouTube-like System

---

### **Module 4: Bandwidth & Throughput**

1. Understanding Mbps vs MB/s
2. Estimating Data Transfer per Day
3. Caching Effect on Bandwidth

---

### **Module 5: Real System Examples**

1. URL Shortener capacity planning
2. Instagram-like photo sharing app
3. Messaging app (WhatsApp scale)
4. YouTube video storage example

---

---

# 🧩 Module 1 — Core Thinking

## 1️⃣ What is “System Design Math”?

It’s **approximation math** that helps you estimate:

* Load
* Storage
* Bandwidth
* Compute power

You **don’t need perfect numbers** — just *ballpark* correctness.

---

## 2️⃣ 3-Step Framework

| Step | Question                  | Example          |
| ---- | ------------------------- | ---------------- |
| 1    | What is the scale?        | 30 million users |
| 2    | How often does it happen? | Every month      |
| 3    | For how long?             | 5 years          |

Then multiply:

```
30M * 12 (months per year) * 5 years = 1.8B total operations
```

That’s where your example came from.

---

## 3️⃣ Quick Multiplication Tricks

| Concept | Example       | Shortcut |
| ------- | ------------- | -------- |
| 1K      | 1,000         | 10³      |
| 1M      | 1,000,000     | 10⁶      |
| 1B      | 1,000,000,000 | 10⁹      |

So:
`30 million * 60 months = 30 * 60 * 10⁶ = 1.8 * 10⁹ = 1.8 billion`

---

## 4️⃣ Approximation Rounding Rules

* Always round up for safety (design for peak load)
* Drop tiny numbers (like 1.8B ≈ 2B)
* For easy mental math:

  * `1 year = 12 months ≈ 365 days ≈ 31M seconds`

---

# ⚙️ Module 2 — Traffic Estimation

### Example:

You have **10 million daily active users (DAU)**.

**Q: How many requests per second (RPS)?**

1. Each user makes 5 requests/day.
   → `10M * 5 = 50M requests/day`

2. 1 day = 86,400 seconds.
   → `50M / 86,400 ≈ 578 RPS`

**✅ So system must handle ~600 requests/sec on average.**

Peak can be 10× → **6K RPS at rush hours.**

---

# 💾 Module 3 — Storage Estimation

### Example:

Each URL record = 100 bytes (shortID + longURL).
Total = `1.8B URLs`.

`Storage = 1.8B * 100 bytes = 180B bytes ≈ 180 GB`

That’s small enough for a few servers — not huge.
So you can confidently say:

> “We can store all mappings in a single sharded DB easily.”

---

# 📡 Module 4 — Bandwidth Estimation

If each redirect response = 500 bytes,
and we serve 1M redirects/day:

`500 bytes * 1M = 500 MB/day ≈ 15 GB/month`

So a small load balancer cluster is enough.

---

# 🧱 Module 5 — Practice Scenarios

### (1) URL Shortener

* 30M new URLs/month
* 5 years lifetime
* 100 bytes per mapping

👉 **1.8B total URLs**
👉 **≈ 180 GB storage needed**

### (2) Instagram

* 100M users, each uploads 1 photo/day = 100M/day
* Photo size: 1MB
  → 100 TB/day → 36 PB/year

### (3) WhatsApp

* 500M users × 20 messages/day = 10B messages/day
* Message size: 200 bytes
  → 2 TB/day → 60 TB/month

---

# 🧩 Cheatsheet Summary

| Metric  | Conversion     |
| ------- | -------------- |
| 1 day   | 86,400 seconds |
| 1 month | 30 days        |
| 1 year  | 365 days       |
| 1 GB    | 10⁹ bytes      |
| 1 TB    | 10³ GB         |
| 1 PB    | 10³ TB         |

---

# 🧠 Quick Mental Math Examples

| Example                  | Result    |
| ------------------------ | --------- |
| 10M users * 5 years      | 600M      |
| 2M/day * 30 days         | 60M/month |
| 1B records * 200 bytes   | 200 GB    |
| 100 req/sec * 86,400 sec | 8.6M/day  |

---

# 🧭 Final Notes

* Focus on **order of magnitude**, not exact number.
* Always **state assumptions** in interviews.
* Use **round numbers** (10M, 1GB, 1MB) for clarity.
* Estimation is about *thinking like a system*, not *being a calculator*.
