# MODULE 2 — BRANCHING & MERGING

## Topic 7: **Git Branch Naming Conventions**

Branch naming conventions are extremely important in professional development.
They help teams work clearly, avoid confusion, identify branch purpose instantly, and maintain a clean workflow.

Let’s break it down properly.

---

# 1. Concept (Simple Explanation)

A **branch name** should clearly state:

* What the branch is for
* What type of work it contains
* What part of the system it affects

Good branch naming makes collaboration smooth and prevents misunderstandings.

---

# 2. Industry-Standard Branch Name Structure

A clean and widely used format:

```
<type>/<short-description>
```

Examples:

```
feature/login-api
fix/navbar-alignment
hotfix/payment-failure
refactor/user-service
docs/update-readme
release/v2.3.0
```

---

# 3. Common Branch Types (Very Important)

| Type            | Purpose                               |
| --------------- | ------------------------------------- |
| **feature/**    | New features                          |
| **fix/**        | Bug fixes                             |
| **hotfix/**     | Urgent production fixes               |
| **refactor/**   | Code restructure without logic change |
| **docs/**       | Documentation updates                 |
| **test/**       | Test files or test improvements       |
| **chore/**      | Minor tasks, config updates           |
| **release/**    | Release preparation                   |
| **experiment/** | Temporary testing branches            |

---

# 4. Good Branch Naming Examples

### Feature branches:

```
feature/add-user-auth
feature/cart-ui
feature/send-email-service
```

### Bug fix branches:

```
fix/null-pointer-login
fix/image-loading-issue
```

### Hotfix (urgent):

```
hotfix/prod-crash-on-startup
```

### Refactor:

```
refactor/split-user-controller
refactor/improve-database-layer
```

### Documentation:

```
docs/api-endpoints-update
docs/setup-instructions
```

### Testing:

```
test/add-auth-tests
test/improve-coverage
```

### Release:

```
release/v1.2.0
release/2025-12-10
```

---

# 5. Bad Branch Naming Examples (Avoid)

Bad:

```
newbranch
mybranch
finaltest
patch1
work123
dev2
bugfix
```

Problems:

* NOT descriptive
* Useless for teams
* Impossible to understand purpose

---

# 6. Rules for Naming Branches (Professional)

### Rule 1: Use lowercase

Git is case-sensitive.

### Rule 2: Use hyphens (`-`) not underscores (`_`)

Hyphens are standard for readability.

### Rule 3: Be descriptive but short

`feature/add-user-auth` is better than:

```
feature/adding-the-authentication-system-with-oauth2
```

### Rule 4: Start with branch type prefix

Your prefix describes intention before reading the full name.

### Rule 5: Use slashes for categorization

GitHub visually organizes them.

```
feature/ui/header
feature/ui/footer
```

### Rule 6: Avoid spaces

Branches cannot have spaces anyway.

### Rule 7: No weird characters

Stick to:

```
a-z
0-9
-
/
```

---

# 7. Examples Based on Real Companies

### Facebook / Meta style:

```
diff/fix-story-bug
diff/improve-feed-scroll
```

### Google style:

```
feature/maps-api-update
fix/auth-token-parsing
```

### Open-source style:

```
fix/typo-in-readme
feature/add-contribution-guide
```

---

# 8. GitHub Flow Recommended Names

For everyday development:

```
feature/<name>
fix/<name>
hotfix/<name>
```

For releases:

```
release/<version>
```

---

# 9. GitFlow Naming Pattern (for advanced workflows)

* `develop`
* `feature/*`
* `release/*`
* `hotfix/*`
* `support/*`

Example:

```
feature/search-bar
release/2.1.0
hotfix/production-crash
```

---

# 10. Interview Answer (Perfect)

**Q: What are Git branch naming conventions?**

Branch naming conventions provide a structured and descriptive way to name branches.
The standard pattern is `<type>/<description>`, where the type indicates the purpose (feature, fix, hotfix, refactor, docs, test, release).
Examples include `feature/login-api`, `fix/cart-bug`, `hotfix/payment-error`.
This improves team collaboration and makes the Git history cleaner and easier to understand.

---

# 11. Mini Task

Give correct branch names for the following scenarios:

1. Adding dark mode to UI
2. Fixing a login crash
3. Updating documentation for API usage
4. Urgent production issue: checkout button not working
5. Prepare release version **v3.0.0**

Send your branch names — I will check and refine them.

---
