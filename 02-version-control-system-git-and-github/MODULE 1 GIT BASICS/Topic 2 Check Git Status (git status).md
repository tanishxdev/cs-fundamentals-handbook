# MODULE 1 — GIT BASICS

## Topic 2: **Check Git Status (`git status`)**

This is one of the MOST used Git commands.
Developers run it 50–100 times a day.

---

# 1. Concept (Simple Explanation)

`git status` tells you the **current state of your working directory and staging area**.

It answers:

* What files changed?
* Are files tracked or untracked?
* Are files staged for commit?
* Which branch am I on?
* Does my branch have unpushed commits?

Think of it as a **health check** for your repo.

---

# 2. Why `git status` Is Important

It helps you avoid mistakes:

* Committing wrong files
* Forgetting to stage changes
* Understanding if merges or pulls are needed
* Detecting conflicts

You should run `git status` **before every add and commit**.

---

# 3. What `git status` Shows

Case 1: No changes

```
On branch main
nothing to commit, working tree clean
```

Case 2: New (untracked) files

```
Untracked files:
  (use "git add <file>..." to include in what will be committed)

        app.js
```

Case 3: Modified files not staged

```
Changes not staged for commit:
  modified:   index.html
```

Case 4: Staged files

```
Changes to be committed:
  new file:   style.css
```

Case 5: After merge conflict

```
Unmerged paths:
  both modified: index.html
```

---

# 4. Core Concepts Behind Status

### 1. **Untracked files**

Files Git doesn’t know yet.

### 2. **Tracked but modified**

Git knows them but you haven’t staged the new changes.

### 3. **Staged files**

Ready to commit.

### 4. **Clean working tree**

No pending work.

---

# 5. Practical Example

Try this:

```bash
mkdir status-demo
cd status-demo
git init
```

Create a file:

```
echo "hello" > a.txt
```

Check status:

```bash
git status
```

Output:

```
Untracked files:
   a.txt
```

Stage it:

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
git status
```

Output:

```
nothing to commit, working tree clean
```

---

# 6. Interview Answer (Perfect)

**Q: What does `git status` do?**

`git status` shows the current state of the working directory and staging area. It tells you which files are untracked, modified, or staged for commit, and which branch you are on. It helps developers understand what actions are needed before committing.

---

# 7. Real-World Usage

Developers run:

* Before adding files
* Before committing
* After pulling
* After merging
* When resolving conflicts

It prevents accidental mistakes.

---

# 8. Mini Task

Try these:

1. Modify a file
2. Delete a file
3. Create a new file

After each step, run:

```bash
git status
```

Observe how Git reacts.

---