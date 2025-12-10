# MODULE 2 — BRANCHING & MERGING

## Topic 3: **Fast-Forward vs Non-Fast-Forward Merges**

Understanding this topic is essential for mastering **merge behavior**, PR handling, and clean Git history.

Let’s break it down clearly.

---

# 1. What is a Merge?

A merge combines the commits of one branch into another.

Example:

```bash
git merge feature-login
```

This brings `feature-login` commits into `main`.

Git can perform this merge in **two different ways**:

* Fast-forward merge
* Non-fast-forward merge (merge commit)

---

# 2. Fast-Forward Merge (Simple Case)

### Concept

A **fast-forward** merge happens when:

* The target branch has **no new commits**
* The feature branch is **directly ahead** of the target branch

So Git simply moves the pointer of `main` forward.

### Visual

Before merge:

```
main:    C1 → C2
              \
feature:        C3 → C4
```

After fast-forward:

```
main:    C1 → C2 → C3 → C4
feature:        C3 → C4
```

No merge commit needed.

### Command

```bash
git merge feature-login
```

Git will choose fast-forward automatically.

### Use Case

* Simple features
* No parallel development
* Clean linear history

---

# 3. Non-Fast-Forward Merge (Merge Commit)

### Concept

A **non-fast-forward** merge creates a new commit called a *merge commit*.

This happens when:

* Both branches have diverged
* Both have independent commits

### Visual

Before merge:

```
main:       C1 → C2 → C3
                 \
feature:          C4 → C5
```

After merge:

```
main:    C1 → C2 → C3 → M  ← merge commit
                 \       ↗
feature:          C4 → C5
```

`M` = merge commit combining both histories.

### Command

```bash
git merge feature-login
```

Git will auto-create merge commit when required.

### Use Case

* Collaboration (multiple developers)
* Branches diverged
* PR merges
* Keeping full history

---

# 4. Forcing a Non-Fast-Forward Merge

Sometimes you want to keep a merge commit even if fast-forward is possible.

Use:

```bash
git merge --no-ff feature-login
```

This ensures a record of the merge action in history.

### Why use `--no-ff`?

* Keeps feature branches visible
* History becomes easier to read
* PR merges look cleaner
* Companies often enforce it

---

# 5. Forcing a Fast-Forward Only Merge

Rejects merge if FF is impossible:

```bash
git merge --ff-only feature-login
```

Used to avoid messy histories.

---

# 6. Summary Table

| Merge Type       | When Happens                     | Creates Merge Commit? | History              |
| ---------------- | -------------------------------- | --------------------- | -------------------- |
| Fast-forward     | Target branch has no new commits | No                    | Linear               |
| Non-fast-forward | Branches diverged                | Yes                   | Full branching tree  |
| `--no-ff`        | Forced NFF merge                 | Yes                   | Always               |
| `--ff-only`      | Merge only if FF possible        | No                    | Clean linear history |

---

# 7. Real Example (Try This)

```bash
git init
echo "first" > a.txt
git add .
git commit -m "C1"

git checkout -b feature
echo "feature" >> a.txt
git commit -am "C2 on feature"

git checkout main
git merge feature       # fast-forward
```

Now make them diverge:

```bash
echo "main edit" >> a.txt
git commit -am "C3 on main"

git checkout feature
echo "feature edit" >> a.txt
git commit -am "C4 on feature"

git checkout main
git merge feature       # non-fast-forward (merge commit)
```

---

# 8. Interview Answer (Perfect)

**Q: What is the difference between fast-forward and non-fast-forward merge?**

A fast-forward merge moves the branch pointer forward because the target branch has no new commits; it does not create a merge commit.
A non-fast-forward merge is used when branches diverge and Git must create a new merge commit to combine the histories. Teams often use `--no-ff` to preserve feature-branch history.

---

# 9. Mini Task

Explain in your own words:

1. When does fast-forward merge happen?
2. Why do companies prefer `--no-ff` merges for pull requests?
