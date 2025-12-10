# MODULE 0 — FOUNDATIONS

## Topic 5: **Installing Git (Windows, Mac, Linux)**

This topic covers **how to install Git properly on all platforms** and how to check if installation succeeded.

---

# 1. Concept (Simple Explanation)

Before using Git commands, you must install the Git software on your machine.
Git provides:

* Git CLI (command line)
* Git Bash (on Windows)
* Git GUI tools (optional)

After installation, you can run Git in:

* Terminal (Mac/Linux)
* Git Bash (Windows)
* VS Code Terminal

---

# 2. Installing Git on **Windows**

### Step 1: Download Git

Go to:

```
https://git-scm.com/download/win
```

Download will start automatically.

### Step 2: Run the Installer

During installation choose:

* **Use Git from Git Bash and Command Prompt**
* **Checkout as-is, commit Unix-style line endings**
* **Use MinTTY terminal** (recommended)
* Keep defaults for others

### Step 3: Verify Installation

Open **Git Bash** or **Command Prompt** and run:

```bash
git --version
```

If you see something like:

```
git version 2.45.0
```

Git is installed successfully.

---

# 3. Installing Git on **MacOS**

### Option 1: Using Homebrew (recommended)

If Homebrew is installed:

```bash
brew install git
```

### Option 2: Xcode Command Line Tools

Mac will auto-install Git if you run:

```bash
git --version
```

If not installed, a popup will ask you to install Developer Tools → click **Install**.

### Verify Installation

```bash
git --version
```

---

# 4. Installing Git on **Linux**

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install git
```

### Fedora

```bash
sudo dnf install git
```

### Arch Linux

```bash
sudo pacman -S git
```

### Verify Installation

```bash
git --version
```

---

# 5. Set Global Username & Email (Important)

After installation, run:

```bash
git config --global user.name "Your Name"
git config --global user.email "your_email@example.com"
```

Check settings:

```bash
git config --global --list
```

### Why this is needed?

* Git uses this info to label your commits.
* GitHub maps commits to your account.

---

# 6. First-Time Setup (Optional but recommended)

### Default branch name

GitHub uses **main**, so set:

```bash
git config --global init.defaultBranch main
```

### Improve Git output color

```bash
git config --global color.ui auto
```

---

# 7. Interview-Level Notes

* Git must be installed locally before any version control work.
* Only Git CLI is required; GUI tools are optional.
* User identity (`name`, `email`) is required for commit metadata.
* Git Bash provides a Linux-like environment on Windows.

---

# 8. Mini Task (Do this on your PC)

1. Install Git on your system.
2. Run:

```bash
git --version
git config --global user.name "Your Name"
git config --global user.email "Your Email"
```
