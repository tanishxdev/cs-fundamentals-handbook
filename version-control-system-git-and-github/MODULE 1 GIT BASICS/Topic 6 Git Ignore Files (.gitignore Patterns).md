# MODULE 1 — GIT BASICS

## Topic 6: **Git Ignore Files (`.gitignore` Patterns)**

`.gitignore` is one of the most important files in any Git repository.
It prevents unnecessary or sensitive files from being tracked by Git.

---

# 1. Concept (Simple Explanation)

`.gitignore` tells Git:

**“Do NOT track these files or folders.”**

Many files in a project should NOT go into Git:

* Temporary files
* Logs
* Environment variables
* System files
* Build output
* Node modules
* IDE/config files

Git reads `.gitignore` to decide what to ignore.

---

# 2. Why `.gitignore` Is Needed

Without `.gitignore`, your repo becomes:

* messy
* heavy
* insecure
* unprofessional
* slow to clone
* difficult to collaborate

### Examples of files that must not be pushed:

* `node_modules/` (thousands of files)
* `.env` (API keys, secrets)
* `dist/`, `build/` (output files)
* `.vscode/` (your personal settings)
* `.DS_Store` (Mac OS trash file)
* `*.log` (logs grow large quickly)

---

# 3. How to Create a `.gitignore`

Inside your project root:

```bash
touch .gitignore
```

Or create file manually.

Git will automatically detect it.

---

# 4. Common `.gitignore` Patterns

### Ignore a file

```
secret.txt
```

### Ignore a folder

```
node_modules/
dist/
build/
```

### Ignore all files of a type

```
*.log
*.tmp
*.zip
*.env
```

### Ignore system files

```
.DS_Store
Thumbs.db
```

### Ignore environment files

```
.env
.env.local
.env.production
```

---

# 5. Example `.gitignore` for Node.js Projects

```
node_modules/
dist/
build/
.env
.env.*
logs/
*.log
npm-debug.log*
yarn-debug.log*
.DS_Store
```

---

# 6. Example `.gitignore` for React Projects

```
node_modules/
build/
dist/
.env*
coverage/
*.log
.DS_Store
```

---

# 7. Example `.gitignore` for Python Projects

```
__pycache__/
*.pyc
env/
venv/
*.log
.DS_Store
```

---

# 8. Example `.gitignore` for C++ Projects

```
*.out
*.exe
*.o
build/
bin/
```

---

# 9. Important Notes

### NOTE 1: `.gitignore` works only **before** tracking a file

If you already committed a file, Git will NOT ignore it automatically.

To remove it from tracking:

```bash
git rm --cached filename
```

### NOTE 2: A global `.gitignore` exists

You can tell Git to ignore files globally on your system:

```bash
git config --global core.excludesfile ~/.gitignore_global
```

Then add patterns:

```
.DS_Store
Thumbs.db
*.log
```

### NOTE 3: Ignore everything in a folder except one file

```
public/*
!public/index.html
```

---

# 10. Interview Answer (Perfect)

**Q: What is `.gitignore`?**

`.gitignore` is a configuration file that tells Git which files or directories should not be tracked. It prevents unwanted files such as logs, temporary files, build output, and secrets from entering the repository. It improves security, reduces repo size, and keeps the repo clean.

---

# 11. Practical Mini Task

Create a folder:

```
project/
   .gitignore
   secret.txt
   node_modules/
   app.js
```

Inside `.gitignore`, write:

```
node_modules/
secret.txt
*.log
```

Now run:

```bash
git init
git status
```

You should see ONLY:

```
app.js
```

Everything else is ignored.

---