# MODULE 0 — FOUNDATIONS

## Topic 3: **Types of Version Control Systems (VCS)**


# 1. Concept (Simple Explanation)

Version Control Systems are tools that **track changes in files** and help developers collaborate.

There are **three types**:

1. **Local Version Control System (LVCS)**
2. **Centralized Version Control System (CVCS)**
3. **Distributed Version Control System (DVCS)** ← Git is here

Each type represents an evolution in how teams handle versions.

---

# 2. Type 1: Local Version Control Systems (LVCS)

### Concept

Version history is stored **only on your computer**, usually in a local database.

### Examples

* RCS (Revision Control System)

### How it works

Each file has diffs stored locally.

### Limitations

* No collaboration support
* If your system crashes → everything is lost
* History cannot be shared

### Visual

```
Your Laptop
   └── Local DB (history)
```

This system is outdated.

---

# 3. Type 2: Centralized Version Control Systems (CVCS)

### Concept

A single **central server** stores the repository.
Developers connect to it and download files.

### Examples

* SVN (Subversion)
* Perforce
* CVS

### How it works

```
          Central Server
        /       |       \
Developer A   Developer B   Developer C
```

### Advantages

* Simple to understand
* Central control

### Limitations

* If server goes down, **no one can work**
* No offline commits
* Single point of failure
* Slower for large teams

This was widely used before Git.

---

# 4. Type 3: Distributed Version Control Systems (DVCS)

### Concept

Every developer has the **full repository + history** on their machine.

Git and Mercurial belong to this category.

### How it works

```
Developer A     Developer B     Developer C
   |                |               |
Each has FULL repo + history
```

Central remote (GitHub) is optional.

### Advantages (why Git wins)

* Work offline (commit without internet)
* Faster operations
* No single point of failure
* Powerful branching & merging
* Multiple backups exist automatically
* Perfect for open source + teamwork

### Visual Understanding

```
GitHub Repo (Remote)
     ↑          ↑          ↑
   Full Repo  Full Repo  Full Repo
Developer A Developer B Developer C
```

Even if GitHub goes down, your local repo is intact.

---

# 5. Summary Table (Easy)

| Feature       | Local VCS | Centralized VCS | Distributed VCS (Git) |
| ------------- | --------- | --------------- | --------------------- |
| Offline work  | No        | No              | Yes                   |
| Collaboration | No        | Yes             | Yes (best)            |
| Data backups  | No        | Single server   | Many copies           |
| Branching     | No        | Weak            | Very strong           |
| Speed         | Medium    | Slow            | Fast                  |
| Example       | RCS       | SVN             | Git                   |

---

# 6. Interview Answer (Perfect)

**Q: What are the types of Version Control Systems?**

There are three types:

1. **Local VCS** – stores versions locally; no collaboration (e.g., RCS).
2. **Centralized VCS** – one central server, all developers connect to it (e.g., SVN).
3. **Distributed VCS** – every developer has a full copy of the repo, allowing offline work, powerful branching, and no single point of failure (e.g., Git).

Git is a Distributed VCS, which is why it is the modern standard.

---

# 7. Mini Task

In your own words, answer:

1. Why is centralized VCS considered risky?
2. Why is DVCS more powerful than CVCS?
