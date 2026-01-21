# MODULE 0 — FOUNDATIONS

## Topic 6: **Basic Git Terms: Repository, Commit, Branch, Merge, Remote, Clone, Fetch, Pull**

This topic builds your vocabulary.
If you understand these words, **80% of Git becomes easy**.

---

# 1. What is a **Repository (Repo)**

A **repository** is your project folder tracked by Git.

When you run:

```bash
git init
```

Git creates a hidden folder:

```
.git
```

This stores:

* full history
* commits
* branches
* configurations

### Simple Meaning

**Repo = Your project + Git history.**

---

# 2. What is a **Commit**

A commit is a **saved version** of your project.

You first stage changes:

```bash
git add .
```

Then save them:

```bash
git commit -m "Meaningful message"
```

### Think of commit as:

* A snapshot
* A restore point
* One step in your project's timeline

---

# 3. What is a **Branch**

A branch is a **separate line of development**.

Default branch: `main`

Create new branch:

```bash
git branch feature-login
```

Switch branch:

```bash
git checkout feature-login
```

### Simple Meaning

A branch lets you work on new features **without touching main code**.

---

# 4. What is a **Merge**

Merge combines two branches.

Example:

```bash
git checkout main
git merge feature-login
```

This brings commits from `feature-login` into `main`.

### If changes conflict

Git shows **merge conflict**, you resolve manually, then commit.

---

# 5. What is a **Remote**

A remote is a **reference to an online repository** — like GitHub.

Add a remote:

```bash
git remote add origin https://github.com/user/repo.git
```

### Popular remote names

* `origin` → your GitHub repo
* `upstream` → original repo (if forked)

---

# 6. What is a **Clone**

Clone downloads a remote repo to your computer.

```bash
git clone https://github.com/user/repo.git
```

This gives you:

* full code
* full history
* full branches

---

# 7. What is **Fetch**

Fetch downloads **changes from remote** but does NOT merge them into your code automatically.

```bash
git fetch origin
```

Meaning:
"Show me new changes, but don’t touch my working files."

---

# 8. What is **Pull**

Pull = fetch + merge

```bash
git pull origin main
```

It fetches updates and immediately merges into your branch.

### Difference

| Command   | What it does           |
| --------- | ---------------------- |
| **fetch** | Downloads changes only |
| **pull**  | Downloads + merges     |

---

# 9. Visual Summary

```
Local Repo                Remote Repo (GitHub)
-----------               ---------------------
working directory   <-->  clone / fetch / pull / push
staging area
local history
branches
```

---

# 10. Interview-Level Short Definitions

| Term       | Short Interview Definition                   |
| ---------- | -------------------------------------------- |
| Repository | A Git-tracked project and its full history   |
| Commit     | A snapshot of changes with a message         |
| Branch     | A separate line of development               |
| Merge      | Combining changes from one branch to another |
| Remote     | Online repo reference (usually GitHub)       |
| Clone      | Creating a local copy of a remote repo       |
| Fetch      | Download remote changes without merging      |
| Pull       | Fetch + merge                                |

---

# 11. Mini Practical Exercise

Run these commands in any new folder:

```bash
git init
echo "hello" > file.txt
git add file.txt
git commit -m "Add file.txt"
git branch test
git checkout test
echo "from test branch" >> file.txt
git commit -am "Update in test branch"
git checkout main
git merge test
```

This gives real feel of repo → commit → branch → merge.

---
