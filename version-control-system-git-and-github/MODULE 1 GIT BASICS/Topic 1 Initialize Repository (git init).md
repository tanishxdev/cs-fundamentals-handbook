# MODULE 1 — GIT BASICS

## Topic 1: **Initialize Repository (`git init`)**

This is the **first real Git command** every developer learns.
It converts a normal folder into a Git-tracked project.

---

# 1. Concept (Simple Explanation)

`git init` creates a **new empty Git repository** in your current project folder.
After this command, Git starts tracking your work.

It creates a hidden folder:

```
.git
```

This folder stores:

* commits
* branches
* logs
* staging index
* references
* configuration

### Without `.git` → Git cannot track anything.

### With `.git` → Your folder becomes a Git repo.

---

# 2. Why This Command Matters

* It begins your Git workflow
* Required before using `add`, `commit`, `branch`, etc.
* Converts ANY folder into a Git project
* Helps manage version history from the start

Every Git repo, local or cloned, **starts with either**:

* `git init`
* `git clone`

---

# 3. How to Initialize a Git Repository

### Step 1: Go to your project folder

```bash
cd my-project
```

### Step 2: Run initialization

```bash
git init
```

You will see:

```
Initialized empty Git repository in /path/to/my-project/.git/
```

---

# 4. Visual Explanation

Before:

```
my-project/
   index.html
   style.css
   script.js
```

After running:

```bash
git init
```

Git creates:

```
my-project/
   index.html
   style.css
   script.js
   .git/        <-- hidden folder
```

This `.git` folder is the entire brain of Git.

---

# 5. Important: `.git` Is the Whole Repo

If you delete `.git`, your project becomes a **normal folder again** (history lost).

If you copy only `.git` into another folder, that folder becomes a Git repo.

---

# 6. Initialize With Default Branch Name

Some older Git versions used `master` as default.
We want:

```bash
main
```

To set default branch for all future repos:

```bash
git config --global init.defaultBranch main
```

Then:

```bash
git init
```

Will create:

```
(main)
```

---

# 7. Common Mistakes Beginners Make

### Mistake 1: Running `git init` inside an already initialized repo

You should NOT run:

```
git init
```

inside:

```
myproject/.git
```

This corrupts repos.

### Mistake 2: Initializing Git inside the wrong folder

Always check:

```bash
pwd      # Mac/Linux
cd       # Windows shows current directory
```

### Mistake 3: Forgetting to create a `.gitignore` before first commit

We will cover `.gitignore` soon.

---

# 8. Interview-Ready Answer

**Q: What does `git init` do?**

`git init` creates a new local Git repository by generating a hidden `.git` directory that stores all version control data such as commits, branches, and history. It converts a normal folder into a repository that Git can track.

---

# 9. Mini Practical Exercise

Try this:

```bash
mkdir demo
cd demo
git init
echo "Hello Git" > a.txt
git status
```

Observe how Git shows:

```
Untracked files:
  a.txt
```
