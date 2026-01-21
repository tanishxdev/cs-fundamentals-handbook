# MODULE 1 — GIT BASICS

## Topic 7: **Git Log & History Exploration (`git log`)**

`git log` is how you **see your entire commit history**.
It’s the main tool developers use to understand how a project evolved.

---

# 1. Concept (Simple Explanation)

`git log` shows:

* commit IDs
* authors
* dates
* commit messages
* parent-child relationships

It is like browsing the **timeline of your project**.

---

# 2. Basic Command

```bash
git log
```

Example output:

```
commit 81ac3c4b2c9d7f8fbb32d0cfa1d2e1f3ff119ab1
Author: Tanish <tanish@example.com>
Date:   Tue Dec 10 15:30 2025 +0530

    feat: add login API

commit 7c19f1e48d84ff239b5c6af9748c3b9db890d411
Author: Tanish <tanish@example.com>
Date:   Tue Dec 10 14:10 2025 +0530

    chore: setup project structure
```

---

# 3. Why `git log` Is Important

It helps you:

* Debug by checking past versions
* See who made which change
* Identify bug-introducing commits
* Understand project evolution
* Review commit messages and authors
* Prepare for merges and rebases

In companies, log history is frequently checked.

---

# 4. Useful Git Log Variants (Very Important)

### 1. One-Line Summary View

```bash
git log --oneline
```

Example:

```
81ac3c4 feat: add login API
7c19f1e chore: setup project structure
```

Great for quick reviews.

---

### 2. Show Graph View (Best for branching)

```bash
git log --oneline --graph
```

Example:

```
* 81ac3c4 (HEAD -> main) feat: add login API
* 7c19f1e chore: setup project structure
```

With branches:

```
* a1b2c3d (feature) update profile UI
| * 71cb8e1 fix logout bug
|/
* 54ac2de init project
```

---

### 3. Show branches + graph + decorator (Most Popular)

```bash
git log --oneline --graph --decorate --all
```

This is the MOST powerful history command.

---

### 4. Limit number of commits

```bash
git log -5
git log --oneline -10
```

---

### 5. Show commits by a specific author

```bash
git log --author="Tanish"
```

---

### 6. Search commits by keyword

```bash
git log --grep="login"
```

---

### 7. Show changes inside commits (patch view)

```bash
git log -p
```

This shows diffs of each commit.

---

# 5. Exploring Specific Commits

### Show a commit’s details

```bash
git show <commit-hash>
```

Example:

```bash
git show 81ac3c4
```

This returns:

* message
* file changes
* diffs

---

# 6. Visual Diagram: How `git log` Displays History

```
HEAD → C5
        ↑
      C4
        ↑
      C3
        ↑
      C2
        ↑
      C1
```

`git log` simply walks backward through commit history.

---

# 7. Common Mistakes

### Mistake 1

Expecting `git log` to show uncommitted changes → It shows **only committed** history.

### Mistake 2

Hyperlong logs → Use `--oneline`.

### Mistake 3

Forgetting `--graph` when working with branches.

---

# 8. Interview Answer (Perfect)

**Q: What is `git log`?**

`git log` is a command that displays the commit history of the repository, including commit hashes, authors, dates, and messages. It helps developers explore project history, debug issues, and understand branching and merging activities. Options like `--oneline`, `--graph`, and `--decorate` make history easier to read.

---

# 9. Practical Mini Task

Run:

```bash
git log
git log --oneline
git log --graph --oneline --decorate
```

Then:

```bash
git show HEAD~1
```

Observe how commits and diffs appear.

---
