# MODULE 1 — GIT BASICS

## Topic 5: **Write Proper Commit Messages (Conventional Commits)**

Most beginners write commit messages like:

```
fixed code
final changes
update file
done
```

These messages are **unprofessional** and **useless** in real projects.

Companies expect **clean, structured, meaningful commit messages**.

That’s why we use **Conventional Commits**.

---

# 1. Concept (Simple Explanation)

**Conventional Commits** is a standard format to write commit messages.

Format:

```
<type>: <short description>

(optional body)

(optional footer)
```

Example:

```
feat: add login API
```

or:

```
fix: handle null password in login API
```

This makes your commit history structured and readable.

---

# 2. Why Conventional Commits Are Important

* Improves collaboration
* Helps during code review
* Makes debugging easier
* Automatically generates changelogs
* CI/CD pipelines use them to decide release versions
* Professional teams strictly follow this

Using this format makes you look like a **serious developer**.

---

# 3. Commit Types (Very Important)

| Type         | Meaning                              |
| ------------ | ------------------------------------ |
| **feat**     | New feature                          |
| **fix**      | Bug fix                              |
| **docs**     | Documentation changes                |
| **style**    | Code formatting (no logic change)    |
| **refactor** | Code restructuring (no new features) |
| **test**     | Adding or updating tests             |
| **perf**     | Performance improvements             |
| **build**    | Build system changes                 |
| **ci**       | CI/CD changes                        |
| **chore**    | Minor tasks, maintenance             |
| **revert**   | Reverting a commit                   |

---

# 4. Examples of Good Commit Messages

### 1. Feature Commit

```
feat: add user registration endpoint
```

### 2. Bug Fix Commit

```
fix: correct email validation regex
```

### 3. Code Refactor

```
refactor: extract auth middleware into separate function
```

### 4. Documentation Update

```
docs: update README with setup instructions
```

### 5. Style Change

```
style: format code using Prettier
```

### 6. Tests Added

```
test: add unit tests for user service
```

### 7. Performance Improvement

```
perf: optimize database query using index
```

### 8. Revert Commit

```
revert: revert "feat: add payment gateway"
```

---

# 5. Commit Message Structure (With Body)

Example:

```
feat: add JWT authentication middleware

- implemented token verification
- added protection to private routes
- updated error handling

BREAKING CHANGE: routes now require authorization header
```

* Title → short
* Body → detailed explanation
* Footer → breaking change / issue reference

---

# 6. When to Use Capital Letters

Type must be **lowercase**, example:

```
feat: ...
fix: ...
```

Description may use lowercase or sentence case.

---

# 7. Real Git Commands

```bash
git commit -m "feat: implement product search API"
```

Multi-line commit:

```bash
git commit
```

Then editor opens:

```
feat: improve caching strategy

Reduced API response time by 40%.
```

---

# 8. Common Mistakes to Avoid

❌ Bad:

```
update project
```

❌ Bad:

```
done changes
```

❌ Bad:

```
fix login maybe
```

✔ Correct:

```
fix: handle wrong password error in login route
```

---

# 9. Interview Answer (Perfect)

**Q: What are Conventional Commits?**

Conventional Commits define a structured format for writing commit messages using types such as feat, fix, docs, etc. This improves readability, automates changelog generation, and supports semantic versioning in CI/CD pipelines. It helps maintain a clean and professional commit history.

---

# 10. Mini Task (Practice)

Write proper commit messages for:

1. Created a new React component
2. Fixed a CSS issue
3. Updated README setup steps
4. Improved API response time
5. Removed unused imports from code

