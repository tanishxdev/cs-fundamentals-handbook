# MODULE 2 — BRANCHING & MERGING

## Topic 5: **Resolve Merge Conflicts (Step-by-Step with Full Example)**

This topic gives you a **full practical conflict scenario**, how Git detects it, and how to resolve it correctly.
This is EXACTLY how it happens in real projects and interviews.

---

# 1. Setup: Create a Repo & First Commit

```bash
mkdir conflict-demo
cd conflict-demo
git init
echo "version 1" > app.txt
git add .
git commit -m "initial commit"
```

Now you have:

```
main
 └── C1
```

---

# 2. Step 1: Create a Feature Branch

```bash
git checkout -b feature
```

Modify the file:

```bash
echo "feature branch change" >> app.txt
git commit -am "update from feature branch"
```

Your history:

```
main:      C1
feature:   C1 → C2
```

---

# 3. Step 2: Switch Back to Main & Make Conflicting Change

```bash
git checkout main
```

Edit the same file but with **different content**:

```bash
echo "main branch change" >> app.txt
git commit -am "update from main branch"
```

Now history diverges:

```
main:      C1 → C3
feature:   C1 → C2
```

Both branches changed **the same line area**, so conflict will occur.

---

# 4. Step 3: Merge Feature into Main (Conflict Happens)

```bash
git merge feature
```

Git output:

```
Auto-merging app.txt
CONFLICT (content): Merge conflict in app.txt
Automatic merge failed; fix conflicts and commit the result.
```

This means:

* Git detected conflicting changes
* Git marked the conflict inside `app.txt`
* You must fix it manually

---

# 5. Step 4: Open the File — See Conflict Markers

Open `app.txt`, you’ll see something like:

```
version 1
<<<<<<< HEAD
main branch change
=======
feature branch change
>>>>>>> feature
```

Meaning:

* The section under `HEAD` = your current branch (`main`)
* The section under `feature` = incoming changes

This is the conflict.

---

# 6. Step 5: Resolve the Conflict Manually (4 Options)

### Option A: Keep main version

```
version 1
main branch change
```

### Option B: Keep feature version

```
version 1
feature branch change
```

### Option C: Combine both (often used)

```
version 1
main branch change
feature branch change
```

### Option D: Rewrite completely

You decide entirely new text.

**Important:**
Remove all conflict markers:

```
<<<<<<<
=======
>>>>>>>
```

---

# 7. Step 6: Stage the Resolved File

```bash
git add app.txt
```

Git now knows conflict is resolved.

---

# 8. Step 7: Complete the Merge with a Commit

```bash
git commit
```

Git automatically creates a merge commit:

```
Merge branch 'feature'
```

Your history becomes:

```
main:      C1 → C3 → M
                 ↘
feature:          C2
```

`M` = merge commit.

---

# 9. Step 8: Verify

```bash
git log --oneline --graph
```

You will see branching and merging clearly.

---

# 10. Full Conflict Resolution Flow (Diagram)

```
1. Edit same line in two branches
2. Merge
3. Git adds conflict markers
4. You fix manually
5. Stage resolved files
6. Commit merge
```

---

# 11. Typical VS Code Merge UI (Very Useful)

VS Code shows:

* Accept Current Change
* Accept Incoming Change
* Accept Both
* Compare

This is the easiest way to resolve conflicts.

---

# 12. Why Merge Conflicts Happen (Very Important for Interviews)

* Same line changed differently
* One branch deletes a file while the other modifies it
* Both branches add identical filenames
* Complex, long-lived branches

---

# 13. Interview Answer (Perfect)

**Q: How do you resolve merge conflicts in Git?**

When Git cannot automatically merge two branches, it marks conflicts inside the affected files using `<<<<<<<`, `=======`, and `>>>>>>>`.
To resolve the conflict, you open the file, manually decide the correct final content, remove conflict markers, stage the resolved file (`git add`), and create a merge commit (`git commit`). Once committed, the merge is complete.

---

# 14. Mini Practical Task (DO THIS)

Run the full commands below:

```bash
mkdir conflict-demo
cd conflict-demo
git init

echo "start" > file.txt
git add .
git commit -m "initial"

git checkout -b feature
echo "from feature branch" >> file.txt
git commit -am "feature update"

git checkout main
echo "from main branch" >> file.txt
git commit -am "main update"

git merge feature
```

You WILL get a merge conflict.

Now resolve manually and commit.

---
