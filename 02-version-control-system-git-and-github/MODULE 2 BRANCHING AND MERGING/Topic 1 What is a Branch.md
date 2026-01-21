# MODULE 2 — BRANCHING & MERGING

## Topic 1: **What is a Branch?**

Branching is one of the MOST powerful features of Git.
It allows you to work on multiple things **without breaking the main code**.

Let’s understand this slowly and clearly.

---

# 1. Concept (Simple Explanation)

A **branch** is a **separate line of development**.

It is like a *parallel universe* of your code.

Two branches can have different commits, and they don’t affect each other until you merge them.

### Default branch:

```
main
```

But developers create many feature branches like:

```
feature/login
fix/navbar-bug
hotfix/crash-issue
```

---

# 2. Why Branches Are Needed

Imagine you want to add a new feature:

Option 1 (wrong):
Edit code directly in `main` → if you break something, entire project breaks.

Option 2 (correct):
Create a branch:

```
feature/login
```

Work there safely.
Test → Review → Merge → Ship.

### Benefits:

* You experiment safely
* You don’t break others’ work
* Every feature has its own branch
* Easy for code review (Pull Requests)
* Easy to rollback to older branches

---

# 3. Visual Understanding

### Timeline without branches:

```
C1 → C2 → C3 → C4 → C5
(main)
```

### Timeline with branches:

```
main:    C1 → C2 → C3
                 ↘
feature-login:     C4 → C5 → C6
```

Branches are just pointers to commits.

---

# 4. What Git Actually Does Internally

In Git:

* A branch is **just a pointer** to a commit (SHA hash).
* Creating a branch is instant.
* Switching branches is fast.

Branches do NOT copy full project files → **they reuse history**.

This is why Git is so fast.

---

# 5. Real Example: Create a Branch

```bash
git branch feature-login
```

List all branches:

```bash
git branch
```

Output:

```
* main
  feature-login
```

Switch to branch:

```bash
git checkout feature-login
```

Or modern command:

```bash
git switch feature-login
```

---

# 6. Create + Switch Combined

```bash
git checkout -b feature-login
```

Or:

```bash
git switch -c feature-login
```

This is how 99% developers create branches.

---

# 7. Branch Naming Conventions (Industry Standard)

Good branch names:

```
feature/signup-api
feature/cart-ui
fix/header-alignment
hotfix/payment-error
release/v2.1.0
```

Bad branch names:

```
test
work
mybranch
devbranch2
```

Use **lowercase + hyphens** and meaningful names.

---

# 8. Branch States

### 1. HEAD → pointer to your current branch

Example:

```
HEAD -> main
```

When on another branch:

```
HEAD -> feature/login
```

### 2. Detached HEAD State

You are NOT on a branch, but on a specific commit.
This is dangerous for beginners.
We will cover it later.

---

# 9. When to Create a Branch (Practical Rules)

You should create a new branch when:

* Adding a new feature
* Fixing a bug
* Working on experiments
* Doing refactoring
* Writing tests
* Preparing a release
* Creating a hotfix

Companies follow strict branching strategies (later modules).

---

# 10. Interview Answer (Perfect)

**Q: What is a branch in Git?**

A branch is a lightweight pointer to a commit, representing an independent line of development. It allows developers to work on new features, bug fixes, or experiments without affecting the main project. Branching enables safe parallel development and smooth collaboration.

---

# 11. Mini Task

Run this:

```bash
git init
echo "Hello" > app.txt
git add .
git commit -m "initial commit"

git checkout -b feature1
echo "Feature 1 code" >> app.txt
git commit -am "Add feature 1"

git checkout main
echo "Main update" >> app.txt
git commit -am "Update main"
```

Now run:

```bash
git log --oneline --graph --decorate --all
```

You will SEE branching visually.

---
