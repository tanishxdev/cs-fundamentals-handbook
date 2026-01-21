# MODULE 1 — GIT BASICS

## Topic 3: **Add Files to Staging (`git add`)**

`git add` is the command that prepares your changes for the next commit.
It is one of the **core fundamentals** of Git.

---

# 1. Concept (Simple Explanation)

Git has a **Staging Area** (also called Index).

`git add` moves files from:

```
Working Directory  →  Staging Area
```

Only staged files will go into the next commit.

### Think of staging like:

* Selecting items before billing
* Marking what will go into the final snapshot

If you forget `git add`, your commit will be empty.

---

# 2. Why Staging Area Exists (Intuition)

It allows you to:

* Commit only specific files
* Group related changes
* Create clean, meaningful commit history
* Avoid committing temporary files
* Review before committing

Example:
You modified 10 files but want only 3 to be part of next commit:

```bash
git add file1.js
git add file2.js
git add file3.js
git commit -m "Fix login bug"
```

Clean and professional.

---

# 3. Basic `git add` Commands

### Add a single file

```bash
git add index.html
```

### Add multiple files

```bash
git add index.html style.css
```

### Add all changes in the folder

```bash
git add .
```

### Add everything including deleted files

```bash
git add -A
```

### Add only modified files (not deleted)

```bash
git add -u
```

---

# 4. What Happens Internally

When you run:

```bash
git add file.txt
```

Git:

* Takes a snapshot of file content
* Stores it in the staging area
* Prepares it to be saved in next commit

Actual commit happens only when you run:

```bash
git commit
```

---

# 5. Practical Example

Try this:

```bash
mkdir staging-demo
cd staging-demo
git init
echo "hello" > a.txt
git status
```

Output:

```
Untracked file: a.txt
```

Now stage it:

```bash
git add a.txt
git status
```

Output:

```
Changes to be committed:
  new file: a.txt
```

Commit:

```bash
git commit -m "Add a.txt"
```

Now modify the file:

```bash
echo "world" >> a.txt
git status
```

Output:

```
modified: a.txt (not staged)
```

Stage modification:

```bash
git add a.txt
git commit -m "Update a.txt"
```

---

# 6. Important Notes for Beginners

### Note 1: `git add .` adds EVERYTHING

Be careful—this may include unwanted files.

### Note 2: `.gitignore` prevents files from being added

We will learn `.gitignore` later.

### Note 3: Adding does NOT mean saved

A commit is required to save permanently.

---

# 7. Interview Answer (Perfect)

**Q: What does `git add` do?**

`git add` moves changes from the working directory to the staging area. It prepares specific files to be included in the next commit. Without running `git add`, no changes will be recorded in the commit.

---

# 8. Mini Task

Create 3 files:

```
a.txt
b.txt
c.txt
```

Now:

1. Modify all three
2. Run `git status`
3. Stage only `a.txt` and `b.txt`
4. Commit
5. Check status again

This will deepen your understanding.

---
