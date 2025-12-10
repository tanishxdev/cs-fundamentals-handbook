# All the essential commands for:

- Windows Command Prompt (CMD)
- Linux / macOS Terminal (Bash / Git Bash)
- PowerShell

---
# PART 1: WINDOWS CMD — COMPLETE FOUNDATIONAL COMMANDS

CMD is the classic Windows shell. Simple, limited, but still very useful.

---

## 1. Navigation Commands

| Command | Meaning            | Example               |
| ------- | ------------------ | --------------------- |
| `cd`    | Change directory   | `cd C:\projects`      |
| `cd ..` | Go up one folder   |                       |
| `dir`   | List files/folders | `dir /b` (clean list) |
| `cls`   | Clear screen       |                       |

### Developer Use-Case

```
cd C:\Users\Tanish\work\mern-app
```

Navigate to your backend folder before running Node.

---

## 2. File CRUD

### Create

```
type nul > file.txt
```

### Read

```
type file.txt
```

### Update (append text)

```
echo Hello >> file.txt
```

### Delete

```
del file.txt
```

### Rename

```
rename old.txt new.txt
```

### Move

```
move file.txt C:\backup
```

### Copy

```
copy file.txt D:\folder
```

---

## 3. Folder CRUD

### Create

```
mkdir src
```

### Delete (empty)

```
rmdir src
```

### Delete (with content)

```
rmdir /s /q build
```

---

## 4. System Commands

```
tasklist       // list running programs  
taskkill /IM node.exe /F  
ipconfig       // network info  
ping google.com  
```

Developer use-case:

```
taskkill /IM node.exe /F    // stop a stuck Node server
```

---

## 5. Running Programs

```
node server.js
python app.py
java HelloWorld
```

---

# PART 2: LINUX / GIT BASH BASICS — SUPER IMPORTANT FOR FULLSTACK

Linux commands are the standard in **backend, devops, cloud, and server deployments**.
Git Bash = Linux terminal emulator for Windows → same commands.

---

## 1. Navigation

```
pwd           # show path
ls            # list files
ls -la        # detailed list
cd folder/
cd ..         # go up
```

---

## 2. File CRUD

### Create

```
touch file.txt
```

### Read

```
cat file.txt
```

### Edit inside terminal

```
nano file.txt
```

### Delete

```
rm file.txt
```

### Force delete

```
rm -rf node_modules/
```

### Copy

```
cp index.js backup.js
```

### Move / Rename

```
mv old.txt new.txt
mv file.txt ../folder/
```

---

## 3. Folder CRUD

```
mkdir src
mkdir -p a/b/c       # nested folder create
rm -rf dist          # remove folder
```

---

## 4. Permissions (DevOps / Backend)

```
chmod 755 script.sh
chmod +x run.sh
```

---

## 5. System Commands

```
ps aux | grep node     # processes  
kill -9 1234           # kill process  
top                    # system monitor  
df -h                  # disk usage  
free -m                # RAM usage  
```

---

## 6. Networking

```
curl https://api.github.com
wget https://example.com/file.zip
ping google.com
```

---

## 7. Package Managers

Linux:

```
sudo apt update
sudo apt install nginx
```

Git Bash (Node / npm):

```
npm install express
```

---

# PART 3: POWERSHELL — MODERN SHELL FOR WINDOWS

More powerful than CMD. Supports:

* Pipelines
* Objects (not text)
* Advanced scripts

---

## 1. Navigation

```
cd .\folder\
Get-ChildItem        # like ls, dir
```

Shortcut alias:

```
ls
```

## 2. File CRUD

### Create

```
New-Item file.txt -ItemType File
```

### Read

```
Get-Content file.txt
```

### Append

```
"hello" | Out-File file.txt -Append
```

### Delete

```
Remove-Item file.txt
```

### Copy

```
Copy-Item file.txt backup.txt
```

---

## 3. Folder CRUD

```
New-Item folder -ItemType Directory
Remove-Item folder -Recurse -Force
```

---

## 4. System Commands

```
Get-Process
Stop-Process -Name "node"
Get-NetIPAddress
```

---

## 5. Running Scripts

```
.\script.ps1
```

---

## 6. Using PowerShell for DevOps

```
Invoke-WebRequest
Start-Job
Get-Service
Restart-Service
```

---
