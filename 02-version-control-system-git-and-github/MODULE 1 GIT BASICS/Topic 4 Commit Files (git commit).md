# MODULE 1 — GIT BASICS

## Topic 4: **Commit Files (`git commit`)**

A **commit** is the *heart* of Git.
Every saved version of your project is stored as a commit.

If Git was a time machine, **commits are its timelines**.

---

# 1. Concept (Simple Explanation)

A commit is a **snapshot of your staged changes** along with:

* A message
* Author name
* Timestamp
* Unique ID (SHA-1 hash)
* Parent commit reference

### You must stage files BEFORE committing:

```bash
git add file.txt
git commit -m "Meaningful message"
```

A commit is a permanent entry in your project history.

---

# 2. Why Commits Are Important

Commits give you:

* **Version history**
* Ability to **undo** mistakes
* Ability to **compare** versions
* Clean timelines for debugging
* Reliable collaboration

If something breaks, you can go back to a commit where it worked.

---

# 3. How to Make a Commit

### Step 1: Stage files

```bash
git add file.txt
```

### Step 2: Commit

```bash
git commit -m "Add file.txt"
```

### Output example:

```
[main 8ac1f2e] Add file.txt
 1 file changed, 1 insertion(+)
 create mode 100644 file.txt
```

---

# 4. Commit Anatomy (Very Important)

Each commit has a unique hash:

Example:

```
commit 8ac1f2eb3419b9c7854c773bece83d12fc301472
Author: Tanish <tanish@example.com>
Date:   Tue Dec 10 12:40 2025 +0530

    Add login feature
```

Breaking it down:

* `8ac1f2e...` = commit ID
* Author = who made the commit
* Date = timestamp
* Message = what was changed

---

# 5. Commit Best Practices

### Rule 1: Commit small, meaningful changes

Bad:

```
git commit -m "fixed things"
```

Good:

```
git commit -m "Fix null check in login controller"
```

### Rule 2: One purpose per commit

Don’t mix multiple features.

### Rule 3: Always write a clear commit message

(We will learn Conventional Commits in the next topics.)

---

# 6. Commands for Commit Variants

### Commit with message

```bash
git commit -m "Add feature"
```

### Commit all tracked changes without staging manually

```bash
git commit -am "Update code"
```

*Note:*
This command skips staging ONLY for modified files, not untracked ones.

### Modify last commit (message or files)

```bash
git commit --amend
```

---

# 7. How Git Stores Commits (Simple Internal View)

Git commits store:

* Snapshot metadata
* Tree object (folder structure)
* Blob objects (file content)

This is part of Git Internals (later module), but basic idea:

**Commit = pointer to a version of your project.**

---

# 8. Visual Diagram

```
Working Directory
     |
git add
     ▼
Staging Area
     |
git commit
     ▼
Local Repository (History)

Commit History:
C1 → C2 → C3 → C4 …
```

---

# 9. Practical Exercise

Try this step-by-step:

```bash
mkdir commit-demo
cd commit-demo
git init
echo "line 1" > test.txt
git add test.txt
git commit -m "Add test.txt"
echo "line 2" >> test.txt
git add test.txt
git commit -m "Update test.txt"
git log
```

Observe the history.

---

# 10. Git Log Example Output

```
commit d1a3f9c (HEAD -> main)
Author: You <you@example.com>
Date:   Today

    Update test.txt

commit 7f4bc0a
Author: You <you@example.com>
Date:   Today

    Add test.txt
```

This is how Git tracks versions.

---

# 11. Interview Answer (Perfect)

**Q: What is a commit in Git?**

A commit is a snapshot of the staged changes along with metadata such as message, timestamp, author, and a unique hash. Commits form the project’s version history and allow you to track, compare, and revert changes.

---

# 12. Mini Task

Do this in any folder:

1. Create 2 files
2. Modify both
3. Commit only one
4. Modify again
5. Commit both
6. Run `git log --oneline`

Observe the clean commit history.

---
