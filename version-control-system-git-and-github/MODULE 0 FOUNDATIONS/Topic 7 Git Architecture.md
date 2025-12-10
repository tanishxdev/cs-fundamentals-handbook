# MODULE 0 — FOUNDATIONS

## Topic 7: **Git Architecture — Working Directory, Staging Area, Local Repository, Remote Repository**

---

# 1. Concept (Simple Explanation)

Git workflow has **4 layers**:

1. **Working Directory**
2. **Staging Area (Index)**
3. **Local Repository (.git folder)**
4. **Remote Repository (GitHub)**

Each command moves your changes from one layer to the next.

---

# 2. Layer 1 — Working Directory

This is your **actual project folder** where you edit files.

Example:

* You write code in VS Code
* You modify files
* You delete files

These changes are **NOT tracked** until you tell Git.

### Commands affecting this layer:

* Creating/editing files
* `git status` → shows what changed

---

# 3. Layer 2 — Staging Area (Index)

Staging area is like a **shopping cart**.

You choose which files you want to include in next commit.

You add files:

```bash
git add file1.js
git add .
```

Now these files are **ready to be committed**.

### Why staging area?

* You can choose specific files
* You control what goes into commit
* You can create clean commit history

---

# 4. Layer 3 — Local Repository

When you commit:

```bash
git commit -m "message"
```

Your changes are permanently stored in the **local repo**, inside `.git` folder.

This contains:

* all commits
* full history
* branches
* tags

### Important:

Local repo works **offline**.
You don’t need GitHub for this part.

---

# 5. Layer 4 — Remote Repository (GitHub)

GitHub stores your repo **online**.

To send your local commits:

```bash
git push origin main
```

To get updates:

```bash
git pull origin main
```

Remote repo enables:

* collaboration
* backups
* pull requests
* code reviews

---

# 6. Master Diagram (Very Important)

```
┌───────────────────────────┐
│  Working Directory         │
│  (your files)             │
└───────────▲───────────────┘
            │  git restore
            │
            │  git add
            ▼
┌───────────────────────────┐
│  Staging Area (Index)     │
│  (files ready to commit)  │
└───────────▲───────────────┘
            │  git commit
            ▼
┌───────────────────────────┐
│  Local Repository (.git)  │
│  (full history)           │
└──────────▲────────────────┘
           │   git push
           ▼
┌───────────────────────────┐
│  Remote Repository         │
│  (GitHub)                  │
└────────────────────────────┘
```

---

# 7. Meaning of Major Commands in Architecture

| Command       | Moves From → To                                 |
| ------------- | ----------------------------------------------- |
| `git add`     | Working Directory → Staging Area                |
| `git commit`  | Staging Area → Local Repo                       |
| `git push`    | Local Repo → Remote Repo                        |
| `git pull`    | Remote Repo → Working Directory (fetch + merge) |
| `git fetch`   | Remote Repo → Local Repo (no merge)             |
| `git restore` | Undo changes in Working Directory               |
| `git reset`   | Move commits between local layers               |

---

# 8. Real Example (Simple)

You create a file:

```txt
hello.txt
```

Now:

```bash
git add hello.txt
git commit -m "Add hello"
git push origin main
```

Behind the scenes:

```
hello.txt → staging → local repo → GitHub
```

---

# 9. Interview Definition (Perfect)

**Q: Explain Git architecture.**

Git uses a 4-layer architecture:

1. **Working Directory** – where files are edited.
2. **Staging Area (Index)** – where files are prepared for commit.
3. **Local Repository** – where commits and history are stored offline.
4. **Remote Repository** – hosted online (GitHub) for collaboration.

Commands like `git add`, `git commit`, and `git push` move changes between these layers.

---

# 10. Mini Task (Practical Exercise)

Run these and observe output:

```bash
git status
echo "test" > a.txt
git status
git add a.txt
git status
git commit -m "Add a.txt"
git status
```

Notice how the file moves through layers.

---
