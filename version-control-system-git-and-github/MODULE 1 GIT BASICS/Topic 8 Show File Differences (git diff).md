# MODULE 1 — GIT BASICS

## Topic 8: **Show File Differences (`git diff`)**

`git diff` is the command that lets you **compare changes** in your files.
It is used constantly during debugging, reviewing changes, and understanding what exactly modified.

---

# 1. Concept (Simple Explanation)

`git diff` shows **line-by-line differences** between:

* your working directory
* staging area
* previous commits
* branches

It highlights:

* Added lines
* Removed lines
* Modified lines

### Output format

```
- lines removed
+ lines added
```

---

# 2. Why `git diff` Is Important

It helps you:

* Review your work before committing
* Understand code changes made by teammates
* Debug errors introduced by new modifications
* Compare branches before merging
* Check what changed in unstaged/staged files

If you want to be a PRO developer, you must use `git diff` regularly.

---

# 3. Basic `git diff` Commands

### 1. Compare **working directory** vs **staging area**

```bash
git diff
```

Shows changes that are **not staged yet**.

---

### 2. Compare **staging area** vs **last commit**

```bash
git diff --cached
```

or

```bash
git diff --staged
```

Shows changes that will go into next commit.

---

### 3. Compare working directory vs last commit (both unstaged + staged)

```bash
git diff HEAD
```

HEAD = your latest commit.

---

# 4. Compare Two Commits

```bash
git diff commit1 commit2
```

Example:

```bash
git diff 8ac1f2e 71cb8e1
```

You will see exact differences between two versions.

---

# 5. Compare Branches (Very Important)

```bash
git diff main feature-login
```

This shows what would change if `feature-login` is merged into `main`.

This is extremely useful **before merging**.

---

# 6. Compare a File in Different Branches

```bash
git diff main feature -- index.html
```

Shows the difference for only that file.

---

# 7. Visual Output Explanation

Example diff:

```
diff --git a/app.js b/app.js
index 23c1def..a159c43 100644
--- a/app.js
+++ b/app.js
@@ -1,3 +1,5 @@
-function sum(a, b) {
-  return a + b;
-}
+function sum(a, b, c = 0) {
+  return a + b + c;
+}
+
+console.log(sum(1, 2, 3));
```

Meaning:

* Lines removed begin with `-`
* Lines added begin with `+`
* `@@ ... @@` shows location
* Code block changed is shown below

---

# 8. Practical Example

Try this demo:

```bash
mkdir diff-demo
cd diff-demo
git init
echo "line1" > test.txt
git add test.txt
git commit -m "initial commit"
```

Modify file:

```bash
echo "line2" >> test.txt
```

Now check diff:

```bash
git diff
```

Output:

```
+ line2
```

Stage file:

```bash
git add test.txt
git diff --cached
```

Output:

```
+ line2
```

---

# 9. Common Use-Cases

### Before committing

```bash
git diff
```

### During code review

Compare branches:

```bash
git diff main feature
```

### During debugging

See what you changed:

```bash
git diff HEAD
```

### When merging

Preview changes:

```bash
git diff main..feature
```

---

# 10. Interview Answer (Perfect)

**Q: What does `git diff` do?**

`git diff` compares changes between the working directory, staging area, commits, or branches. It shows added, removed, and modified lines, helping developers understand exactly what changed before committing or merging.

---

# 11. Mini Task

Do this:

1. Create a new file
2. Add some text
3. Run `git diff`
4. Stage the file
5. Run `git diff --cached`
6. Commit
7. Modify file again
8. Compare with last commit using `git diff HEAD`

This will teach you all layers of diff.

---
