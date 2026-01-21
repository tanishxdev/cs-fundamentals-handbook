# MODULE 2 — BRANCHING & MERGING

## Topic 4: **Merge Conflicts**

Merge conflicts are a core part of working with Git.
Every developer faces them, and knowing how to resolve them properly is a key skill.

This topic will explain:

* What a merge conflict is
* Why it happens
* How to detect it
* How to resolve it step-by-step

Let’s start.

---

# 1. Concept (Simple Explanation)

A **merge conflict** happens when Git cannot automatically merge changes because **two branches modified the same part of the same file** in different ways.

Example:

`main` has:

```
color: red;
```

`feature` has:

```
color: blue;
```

Git cannot decide which one to keep → conflict.

---

# 2. Why Merge Conflicts Happen

Conflicts occur when:

1. Two developers edit the same lines
2. A file is deleted in one branch but modified in another
3. Complex changes overlap
4. Rebase or cherry-pick touches conflicting lines
5. You merge branches with divergent histories

---

# 3. Visual Example of a Conflict

### In `main` branch:

```
title = "Welcome Page"
```

### In `feature` branch:

```
title = "Home Screen"
```

When merging:

```bash
git merge feature
```

Git sees different versions of same line → conflict.

---

# 4. How Git Shows Conflicts

Inside the file, Git marks conflict areas:

```
<<<<<<< HEAD
title = "Welcome Page"
=======
title = "Home Screen"
>>>>>>> feature
```

Meaning:

* **HEAD** = your current branch (e.g., main)
* **feature** = branch being merged

---

# 5. Step-by-Step Conflict Resolution

### Step 1: Attempt merge

```bash
git merge feature
```

### Step 2: Git warns:

```
CONFLICT (content): Merge conflict in app.js
Automatic merge failed; fix conflicts and commit result.
```

### Step 3: Open the file

You will see markers like:

```
<<<<<<< HEAD
current branch code
=======
incoming branch code
>>>>>>> feature
```

### Step 4: Manually edit the file

Remove conflict markers and finalize the correct code.

Example resolution:

```
title = "Home Screen"
```

### Step 5: Stage the resolved file

```bash
git add app.js
```

### Step 6: Commit the merge

```bash
git commit
```

Now merge is completed.

---

# 6. Ways to Resolve a Conflict

### Option 1: Keep HEAD code

Delete incoming part.

### Option 2: Keep incoming branch code

Delete HEAD part.

### Option 3: Combine both changes

Useful in UI files or functions.

### Option 4: Completely rewrite the section

When both versions are wrong or outdated.

---

# 7. Tools to Handle Merge Conflicts Easily

### CLI tools

* `git status` tells which files have conflicts
* `git diff` shows conflict areas

### GUI tools

* VS Code merge editor
* GitKraken
* SourceTree
* GitHub Desktop

VS Code shows clean options:

* Accept Current
* Accept Incoming
* Accept Both
* Compare Changes

---

# 8. Understanding Merge Conflict Flow

Diagram:

```
main:       A ---- B ---- C
                 \
feature:          D ---- E
```

If both changed same lines → conflict.

---

# 9. Common Conflict Scenarios

### 1. Same line edited differently

Most common.

### 2. One branch deletes a file, other edits it

Git doesn’t know what to do.

### 3. Both branches add a file with same name

File conflict.

### 4. Complex merges after long-lived feature branches

High conflict chance.

---

# 10. Avoiding Conflicts (Best Practices)

* Pull latest changes BEFORE starting new work
* Keep feature branches small
* Commit frequently
* Communicate with teammates
* Avoid editing same files simultaneously
* Use well-defined branching strategy (GitFlow, GitHub Flow)

---

# 11. Interview Answer (Perfect)

**Q: What is a merge conflict? How do you resolve it?**

A merge conflict occurs when Git cannot automatically combine changes from two branches because the same part of a file was modified differently. Git marks the conflicting section with conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`). To resolve it, open the file, manually fix the conflict, remove markers, stage the file, and commit the merge.

---

# 12. Mini Task

Try this:

1. Create a repo
2. Add a file `app.txt`
3. Commit
4. Create branch `feature`
5. Edit the same line in both `main` and `feature`
6. Try merging → You will get conflict
7. Resolve it manually
8. Commit the merge

This is the BEST way to learn.

---
