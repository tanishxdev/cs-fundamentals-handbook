# **Complete VS Code + Terminal Setup Documentation**

This document explains the full setup of my development environment including:

* VS Code configuration
* Git Bash terminal setup
* Custom prompt (PS1)
* Path, branch name, and colors
* Auto-formatting, ESLint, Prettier
* Extensions and UI
* Troubleshooting & fixes

---

# **1. 💻 VS Code Settings Overview**

I use a highly–optimized configuration for:

* Fast coding
* Auto-formatting
* Clean UI
* Beautiful terminal
* Accurate Git feedback
* Smooth JavaScript + C++ + Web Dev workflow

My complete **settings.json** is stored here for backup:

```json
{
  // ===============================
  // Auto Save & File Management
  // ===============================
  "files.autoSave": "afterDelay",
  "files.autoSaveDelay": 700,
  "files.eol": "\n",
  "explorer.confirmDragAndDrop": false,
  "explorer.confirmDelete": false,
  "explorer.confirmPasteNative": false,
  "workbench.startupEditor": "none",
  "workbench.editor.empty.hint": "hidden",
  "security.workspace.trust.untrustedFiles": "prompt",

  // ===============================
  // Git & Source Control
  // ===============================
  "git.autofetch": true,
  "git.openRepositoryInParentFolders": "never",
  "git.ignoreRebaseWarning": true,
  "git.suggestSmartCommit": false,
  "git.confirmSync": false,
  "diffEditor.ignoreTrimWhitespace": true,
  "diffEditor.renderSideBySide": true,

  // ===============================
  // Terminal Setup
  // ===============================
  "terminal.integrated.defaultProfile.windows": "Git Bash",

  "terminal.integrated.profiles.windows": {
    "Git Bash": {
      "path": "C:\\Program Files\\Git\\bin\\bash.exe",
      "args": ["--login", "-i"],
      "icon": "terminal-bash"
    }
  },

  "terminal.integrated.tabs.defaultIcon": "terminal-bash",
  "terminal.integrated.tabs.defaultColor": "terminal.ansiGreen",

  "terminal.integrated.fontFamily": "'JetBrains Mono', 'Fira Code', 'Cascadia Code', Consolas, monospace",
  "terminal.integrated.fontSize": 15,
  "terminal.integrated.lineHeight": 1.3,
  "terminal.integrated.mouseWheelZoom": true,
  "terminal.integrated.enableMultiLinePasteWarning": "never",
  "terminal.integrated.cwd": "${workspaceFolder}",

  // ===============================
  // Editor Font & UI
  // ===============================
  "editor.fontFamily": "Cascadia Code SemiBold, Cascadia Code, JetBrains Mono, monospace",
  "editor.fontSize": 16,
  "editor.lineHeight": 22,
  "editor.letterSpacing": 0.3,
  "editor.fontWeight": "600",
  "editor.fontLigatures": true,

  "editor.cursorBlinking": "smooth",
  "editor.cursorSmoothCaretAnimation": "on",
  "editor.mouseWheelZoom": true,
  "editor.linkedEditing": true,
  "editor.inlineSuggest.suppressSuggestions": false,
  "editor.renderWhitespace": "boundary",
  "editor.renderLineHighlight": "all",
  "editor.smoothScrolling": true,
  "editor.minimap.enabled": false,

  // ===============================
  // Indentation Guides & Brackets
  // ===============================
  "editor.guides.indentation": true,
  "editor.guides.highlightActiveIndentation": true,
  "editor.guides.bracketPairs": true,
  "editor.bracketPairColorization.enabled": true,
  "editor.bracketPairColorization.independentColorPoolPerBracketType": true,

  // (Deprecated keys removed)

  // ===============================
  // ESLint & UNIVERSAL Auto Formatting
  // ===============================
  "eslint.validate": ["javascript"],

  "editor.formatOnSave": true,
  "editor.formatOnPaste": true,
  "editor.formatOnType": true,

  "editor.codeActionsOnSave": {
    "source.fixAll": "explicit",
    "source.fixAll.eslint": "explicit",
    "source.organizeImports": "explicit"
  },

  "editor.defaultFormatter": "esbenp.prettier-vscode",

  "[html]": { "editor.defaultFormatter": "esbenp.prettier-vscode" },
  "[css]": { "editor.defaultFormatter": "esbenp.prettier-vscode" },
  "[javascript]": { "editor.defaultFormatter": "esbenp.prettier-vscode" },
  "[typescript]": { "editor.defaultFormatter": "esbenp.prettier-vscode" },
  "[json]": { "editor.defaultFormatter": "esbenp.prettier-vscode" },

  "[cpp]": {
    "editor.defaultFormatter": "ms-vscode.cpptools"
  },

  // ===============================
  // Extensions & Tools Behavior
  // ===============================
  "grunt.autoDetect": "on",
  "gulp.autoDetect": "on",
  "jake.autoDetect": "on",

  "tabnine.experimentalAutoImports": true,

  "code-runner.runInTerminal": true,
  "code-runner.saveAllFilesBeforeRun": true,
  "code-runner.ignoreSelection": true,
  "code-runner.fileDirectoryAsCwd": true,
  "code-runner.clearPreviousOutput": true,

  "liveServer.settings.donotShowInfoMsg": true,
  "liveServer.settings.donotVerifyTags": true,

  // ===============================
  // AI / Codeium / Copilot / Cody
  // ===============================
  "codeium.enableConfig": {
    "*": true,
    "javascriptreact": false
  },
  "codeium.enableCodeLens": false,
  "codeium.aggressiveShutdown": true,

  "github.copilot.enable": {
    "*": false,
    "plaintext": false,
    "markdown": false,
    "scminput": false
  },
  "github.copilot.nextEditSuggestions.enabled": true,

  "cody.suggestions.mode": "auto-edit",

  // ===============================
  // GitLens / AI Commit Message
  // ===============================
  "gitlens.ai.model": "vscode",
  "gitlens.ai.vscode.model": "copilot:gpt-3.5-turbo",

  "aicommitmessage.openAI.customEndpoint": "openai",
  "aicommitmessage.openAI.gptVersion": "gpt-4o-2024-05-13",
  "aicommitmessage.openAI.apiKey": "",
  "aicommitmessage.openAI.language": "English",

  // ===============================
  // UI/Theme Defaults
  // ===============================
  "workbench.preferredLightColorTheme": "GitHub Light Default",
  "workbench.colorTheme": "GitHub Dark",
  "window.commandCenter": false,

  "workbench.settings.applyToAllProfiles": ["editor.fontFamily"],

  // ===============================
  // Markdown Preview Enhanced
  // ===============================
  "markdown-preview-enhanced.previewTheme": "github-dark.css",
  "markdown-preview-enhanced.revealjsTheme": "serif.css",
  "markdown-preview-enhanced.codeBlockTheme": "github-dark.css",
  "markdown-preview-enhanced.enablePreviewZenMode": true,
  "markdown-preview-enhanced.alwaysShowBacklinksInPreview": false,

  "[markdown]": {
    "editor.defaultFormatter": "esbenp.prettier-vscode",
    "diffEditor.ignoreTrimWhitespace": false
  },

  // ===============================
  // Terminal Color Customization
  // ===============================
  "workbench.colorCustomizations": {
    "editor.background": "#0e1116",
    "editor.foreground": "#dfe2e7",
    "editorLineNumber.foreground": "#3b4252",
    "editorLineNumber.activeForeground": "#9aa5b8",

    "editorCursor.foreground": "#66ccff",
    "editor.selectionBackground": "#264f78aa",
    "editor.inactiveSelectionBackground": "#264f7833",
    "editor.selectionHighlightBackground": "#3a506699",

    "tab.activeBackground": "#1b1f27",
    "tab.inactiveBackground": "#0e1116",
    "tab.activeForeground": "#ffffff",
    "tab.inactiveForeground": "#8b929d",
    "tab.hoverBackground": "#252a33",
    "tab.border": "#00000000",

    "sideBar.background": "#0d1015",
    "sideBar.foreground": "#c7ccd5",
    "sideBar.sectionHeader.background": "#15181f",
    "sideBar.border": "#00000000",

    "statusBar.background": "#0d1218",
    "statusBar.foreground": "#cbd3dd",
    "statusBar.noFolderBackground": "#0d1218",
    "statusBar.debuggingBackground": "#8034d8",

    "activityBar.background": "#0b0e13",
    "activityBar.foreground": "#dfe2e7",
    "activityBar.activeBorder": "#66ccff",
    "activityBar.inactiveForeground": "#727b88",
    "activityBarBadge.background": "#66ccff",
    "activityBarBadge.foreground": "#0b0e13",

    "panel.background": "#10141b",
    "panel.border": "#1f2430",

    "breadcrumb.foreground": "#73808f",
    "breadcrumb.focusForeground": "#cfd7e3",

    "editorIndentGuide.background": "#2c323c",
    "editorIndentGuide.activeBackground": "#6b7080",

    "scrollbarSlider.background": "#5a637266",
    "scrollbarSlider.hoverBackground": "#6b748399",
    "scrollbarSlider.activeBackground": "#7d8899bb",

    "terminal.background": "#0e1116",
    "terminal.foreground": "#dfe2e7",

    "terminal.ansiBlack": "#000000",
    "terminal.ansiBlue": "#10037d",
    "terminal.ansiBrightBlue": "#1a01ff",
    "terminal.ansiCyan": "#025d96",
    "terminal.ansiBrightCyan": "#06a0ff",
    "terminal.ansiGreen": "#187501",
    "terminal.ansiBrightGreen": "#33ff00",
    "terminal.ansiMagenta": "#6a0261",
    "terminal.ansiBrightMagenta": "#ff00ea",
    "terminal.ansiRed": "#6a0202",
    "terminal.ansiBrightRed": "#ff0000",
    "terminal.ansiWhite": "#a1a1a1",
    "terminal.ansiBrightWhite": "#fbfbfb",
    "terminal.ansiYellow": "#6a6702",
    "terminal.ansiBrightYellow": "#fff700",
    "terminal.ansiBrightBlack": "#474747"
  },

  // ===============================
  // Icons & Misc
  // ===============================
  "material-icon-theme.folders.theme": "specific",

  "remote.SSH.remotePlatform": {
    "sandbox.rd8gq3.csb": "linux"
  },

  "database-client.autoSync": true,

  "python.defaultInterpreterPath": "c:\\Users\\Tanish\\AppData\\Local\\Microsoft\\WindowsApps\\python3.13.exe",

  "amp.url": "https://ampcode.com/",

  // ===============================
  // Code Runner Executor Maps
  // ===============================
  "code-runner.executorMap": {
    "javascript": "node",
    "java": "cd $dir && javac $fileName && java $fileNameWithoutExt",
    "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "python": "python -u",
    "typescript": "npx ts-node",
    "go": "go run",
    "rust": "cd $dir && rustc $fileName && $dir$fileNameWithoutExt",
    "dart": "dart",
    "php": "php",
    "swift": "swift",
    "r": "Rscript",
    "v": "v run"
  },

  "code-runner.executorMapByGlob": {
    "pom.xml": "cd $dir && mvn clean package"
  },

  // ===============================
  // Terminal Behavior Improvements
  // ===============================
  "terminal.integrated.cursorBlinking": true,
  "terminal.integrated.cursorStyle": "line",
  "terminal.integrated.cursorWidth": 2,
  "terminal.integrated.fastScrollSensitivity": 5,
  "terminal.integrated.scrollback": 10000,
  "terminal.integrated.drawBoldTextInBrightColors": true,
  "terminal.integrated.persistentSessionReviveProcess": "never",
  "terminal.integrated.minimumContrastRatio": 4.5,
  "terminal.integrated.enableFileLinks": "on",
  "terminal.integrated.copyOnSelection": true,
  "terminal.integrated.rightClickBehavior": "copyPaste",
  "terminal.integrated.tabs.enabled": true,
  "terminal.integrated.detectLocale": "off",
  "terminal.integrated.enableVisualBell": false,

  // ===============================
  // Developer Workflow Improvements
  // ===============================
  "editor.stickyScroll.enabled": true,
  "editor.unicodeHighlight.nonBasicASCII": false,
  "editor.hover.delay": 100,
  "editor.fastScrollSensitivity": 5,
  "editor.accessibilitySupport": "off",

  "breadcrumbs.enabled": true,

  "search.quickOpen.includeSymbols": true,
  "search.useIgnoreFiles": true,
  "search.useGlobalIgnoreFiles": true,

  "editor.detectIndentation": true,
  "editor.autoClosingBrackets": "always",
  "editor.autoClosingQuotes": "always",
  "editor.autoSurround": "languageDefined",

  "editor.quickSuggestionsDelay": 0,
  "editor.wordBasedSuggestions": "off",
  "editor.suggest.localityBonus": true,
  "editor.inlineSuggest.enabled": true,

  "editor.suggestSelection": "first",
  "editor.parameterHints.enabled": true,
  "editor.acceptSuggestionOnCommitCharacter": true,

  // ===============================
  // Debug Settings
  // ===============================
  "debug.console.fontFamily": "'JetBrains Mono', monospace",
  "debug.console.wordWrap": true,
  "debug.openDebug": "openOnSessionStart",
  "debug.showBreakpointsInOverviewRuler": true,

  "accessibility.signals.terminalBell": {
    "sound": "off"
  },

  "workbench.iconTheme": "material-icon-theme",

  "chat.instructionsFilesLocations": {
    ".github/instructions": true,
    "C:\\Users\\Tanish\\AppData\\Local\\Temp\\postman-collections-post-response.instructions.md": true,
    "C:\\Users\\Tanish\\AppData\\Local\\Temp\\postman-collections-pre-request.instructions.md": true,
    "C:\\Users\\Tanish\\AppData\\Local\\Temp\\postman-folder-post-response.instructions.md": true,
    "C:\\Users\\Tanish\\AppData\\Local\\Temp\\postman-folder-pre-request.instructions.md": true,
    "C:\\Users\\Tanish\\AppData\\Local\\Temp\\postman-http-request-post-response.instructions.md": true,
    "C:\\Users\\Tanish\\AppData\\Local\\Temp\\postman-http-request-pre-request.instructions.md": true,
    "C:\\Users\\TK\\AppData\\Local\\Temp\\postman-collections-post-response.instructions.md": true,
    "C:\\Users\\TK\\AppData\\Local\\Temp\\postman-collections-pre-request.instructions.md": true,
    "C:\\Users\\TK\\AppData\\Local\\Temp\\postman-folder-post-response.instructions.md": true,
    "C:\\Users\\TK\\AppData\\Local\\Temp\\postman-folder-pre-request.instructions.md": true,
    "C:\\Users\\TK\\AppData\\Local\\Temp\\postman-http-request-post-response.instructions.md": true,
    "C:\\Users\\TK\\AppData\\Local\\Temp\\postman-http-request-pre-request.instructions.md": true
  },

  "editor.inlineSuggest.showToolbar": "always",
  "postman.mcp.notifications.postmanMCP": false
}

```

---

# **2. 🖥 Terminal Setup (Git Bash Default)**

I set **Git Bash** as my default terminal because:

* It supports UNIX commands
* It works well with Node.js, Git, DSA, and MERN stack
* It gives a clean workflow inside VS Code

### **Setup in `settings.json`**

```json
"terminal.integrated.defaultProfile.windows": "Git Bash",

"terminal.integrated.profiles.windows": {
  "Git Bash": {
    "path": "C:\\Program Files\\Git\\bin\\bash.exe",
    "args": ["--login", "-i"],
    "icon": "terminal-bash"
  }
}
```

### **Why this configuration?**

| Setting                              | Purpose                                   |
| ------------------------------------ | ----------------------------------------- |
| `--login`                            | Loads `.bashrc` for prompt customization  |
| `-i`                                 | Interactive mode for Git branch detection |
| `terminal.integrated.defaultProfile` | Makes Git Bash the default                |
| Custom fonts                         | Makes terminal readable & aesthetic       |

---

# **3. 🎨 My Custom Bash Prompt**

### **Goal:**

A clean, readable prompt:

```
TK ~/Desktop/project (main)
$
```

### **Working final PS1 configuration**

Open `.bashrc`:

```bash
nano ~/.bashrc
```

Add:

```bash
parse_git_branch() {
  git rev-parse --abbrev-ref HEAD 2>/dev/null
}

PS1='\[\e[1;32m\]TK \[\e[36m\]\w \[\e[32m\]`parse_git_branch`\[\e[0m\]\n$ '
```

### **Why this works (important)**

| Component           | Meaning                            |
| ------------------- | ---------------------------------- |
| `TK`                | Your name tag                      |
| `\w`                | Current working directory          |
| `parse_git_branch`  | Detect Git branch                  |
| Colors (`\e[...]m`) | Green + Cyan theme                 |
| Newline `\n`        | Clean separation before `$` prompt |

---

# **4. 🧪 Common Problems & Fixes (Very Important)**

### **❌ Problem:**

`bash: command substitution: line 1: syntax error near unexpected token ')'`

### **✅ Fix:**

Use **backticks** instead of `$()` inside PS1:

```bash
`parse_git_branch`
```

Because Git Bash sometimes fails when PS1 uses `$()` inside quotes.

---

### **❌ Problem:** Branch not showing

### **Possible causes & fixes**

| Cause                  | Fix                                    |
| ---------------------- | -------------------------------------- |
| Not inside a Git repo  | Run: `git init`                        |
| Wrong function         | Use: `git rev-parse --abbrev-ref HEAD` |
| .bashrc not loaded     | Run: `. ~/.bashrc`                     |
| Terminal not restarted | Close & reopen VS Code terminal        |

---

### **❌ Problem:** `.bashrc` did not open (shows empty)

### **Fix:**

Run:

```bash
touch ~/.bashrc
nano ~/.bashrc
```

---

# **5. 🎯 Why I Use These Fonts & Settings**

### **Terminal Fonts**

```
'JetBrains Mono', 'Fira Code', 'Cascadia Code'
```

Benefits:

* Clean monospaced text
* Better alignment
* Optional ligatures
* No visual noise

---

# **6. 🌐 Git Settings Included**

* Auto-fetch
* No rebase warnings
* Clean Git diff
* Smarter commit environment

Your settings manage everything automatically.

---

# **7. ✨ Developer Quality settings**

Your setup includes:

| Feature                   | Purpose                  |
| ------------------------- | ------------------------ |
| Auto Save                 | Fast dev speed           |
| Format On Save            | Clean code               |
| ESLint + Prettier         | No style bugs            |
| Sticky Scroll             | Better navigation        |
| Smooth caret              | Better typing experience |
| Terminal scrollback 10000 | Debug long logs          |
| Tabs customization        | Cleaner multitasking     |
| Custom colors             | Reduce eye strain        |

---

# **8. 🧠 AI Tools Setup**

Your environment includes:

* Codeium
* Copilot (disabled by default)
* GitLens AI
* Cody AI
* ChatGPT integration

These settings optimize coding speed without making the editor heavy.

---

# **9. 🚀 Code Runner Setup**

Supports:

* JavaScript
* C, C++
* Java
* Python
* Rust
* Go
* PHP

Configured to run in terminal, not the output console.

---

# **10. 📌 Full Workflow Explanation**

### **Why Git Bash?**

* Cross-platform commands
* Works with Node, npm, git
* Stable for MERN development

### **Why this PS1?**

* Clean
* Minimal
* Helpful info only
* No slow or heavy features

### **Why this VS Code setup?**

* Productivity
* Speed
* No distractions
* Professional coding environment

---

# **11. 📄 How to Backup This Setup**

Run:

```bash
code ~/.config/Code/User/settings.json
```

Copy file into:

```
my-setup/settings.json
my-setup/terminal-guide.md
```

---

# **12. 📚 How to Restore Setup On New System**

1. Install VS Code
2. Install Git Bash
3. Install Nerd Font
4. Paste settings.json
5. Paste .bashrc
6. Restart VS Code

Done.
