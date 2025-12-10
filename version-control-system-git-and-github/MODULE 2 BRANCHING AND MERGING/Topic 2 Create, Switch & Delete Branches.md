# MODULE 2 — BRANCHING & MERGING

## Topic 2: **Create, Switch & Delete Branches**

This topic teaches you the essential branch operations used daily in Git.

---

# 1. Creating a Branch

There are **three** main ways to create branches.

### Method 1: Standard way

```bash
git branch feature-login
```

This **creates** the branch but does NOT switch to it.

---

### Method 2: Create + Switch

```bash
git checkout -b feature-login
```

or the modern version:

```bash
git switch -c feature-login
```

This is the most commonly used method.

---

### Method 3: Create branch from a specific commit

```bash
git branch feature-login <commit-hash>
```

Example:

```bash
git branch fix-bug 81ac3c4
```

This creates a branch starting from that commit.

---

# 2. Listing Branches

```bash
git branch
```

Output example:

```
* main
  feature-login
  hotfix/navbar
```

`*` indicates **current branch** (where HEAD is pointing).

---

# 3. Switching Between Branches

### Old way:

```bash
git checkout feature-login
```

### New recommended way:

```bash
git switch feature-login
```

Back to main:

```bash
git switch main
```

---

# Important Rule Before Switching Branches

You MUST commit or stash your changes before switching.
Otherwise, Git will show:

```
error: Your local changes would be overwritten
```

So do:

```bash
git add .
git commit -m "WIP"
```

or stash:

```bash
git stash
```

Then switch.

---

# 4. Renaming a Branch

Rename the branch you are currently on:

```bash
git branch -m new-name
```

Rename another branch:

```bash
git branch -m old-name new-name
```

---

# 5. Deleting a Branch

### Delete a fully merged branch:

```bash
git branch -d feature-login
```

### Force delete (if not merged):

```bash
git branch -D feature-login
```

Used when:

* You no longer need the branch
* It has experimental or broken code
* Feature got cancelled

---

# 6. Remote Branch Deletion

After pushing a branch to GitHub, delete it remotely:

```bash
git push origin --delete feature-login
```

or older syntax:

```bash
git push origin :feature-login
```

---

# 7. Visual Diagram of Create → Switch → Delete

```
(main)
   |
   C1 -- C2 --- C3
            \
             C4 -- C5   (feature/login)
```

After merging, delete the feature branch:

```
(main)
   |
   C1 -- C2 --- C3 --- C4 -- C5
```

Branches are only pointers → deleting breaks nothing.

---

# 8. Real Workflow Example (Very Common)

### Start feature:

```bash
git switch -c feature/cart-ui
```

### Do work and commit:

```bash
git commit -am "feat: add cart UI skeleton"
```

### Switch back:

```bash
git switch main
```

### Merge and delete branch:

```bash
git merge feature/cart-ui
git branch -d feature/cart-ui
```

---

# 9. Common Mistakes Beginners Make

### Mistake 1: Working on main

Always create feature branches.

### Mistake 2: Switching without committing

This causes conflicts.

### Mistake 3: Deleting unmerged branches accidentally

Avoid using `-D` unless sure.

### Mistake 4: Confusing local and remote branches

They are different:

```
Local:  git branch
Remote: git branch -r
```

---

# 10. Interview-Perfect Answer

**Q: How do you create and switch branches in Git?**

Branches can be created using `git branch <name>` and created + switched using `git checkout -b <name>` or `git switch -c <name>`. Switching branches is done with `git checkout <name>` or `git switch <name>`. Branches can be deleted using `git branch -d <name>` once merged, or `-D` for force delete.

---

# 11. Practical Mini Task

Run these commands:

```bash
git init
echo "Hello" > app.txt
git add .
git commit -m "initial"

git switch -c feature1
echo "Feature 1" >> app.txt
git commit -am "add feature 1"

git switch main
echo "Main change" >> app.txt
git commit -am "update main"

git switch feature1
git branch -d main  # expect error
```

Then observe what Git says.

---
