# Git Setup & Push Guide for sxvyx Account

## 🎯 Repository Name
**Recommended:** `daa-maze-solver-dfs`

---

## 📋 Step-by-Step Instructions

### Step 1: Open Terminal/PowerShell

Navigate to your project folder:

```bash
cd "c:\Users\savy\OneDrive\Desktop\USB\DAA PROJECT MAZE\MazeSolver-master\MazeSolver-master"
```

---

### Step 2: Configure Git (One-time setup for this project)

Set your school account details for this project:

```bash
git config user.name "sxvyx"
git config user.email "YOUR_SCHOOL_EMAIL@example.com"
```

> Replace `YOUR_SCHOOL_EMAIL@example.com` with your actual email for the sxvyx account

---

### Step 3: Initialize Git Repository

```bash
git init
git add .
git commit -m "Initial commit: DAA Mini Project - Maze Solver using DFS Algorithm"
```

---

### Step 4: Create Repository on GitHub

1. **Login to GitHub** with your **sxvyx** account
2. Click the **"+"** icon (top-right) → **"New repository"**
3. Fill in:
   - **Repository name:** `daa-maze-solver-dfs`
   - **Description:** "DAA Mini Project: Web-based maze solver using Depth-First Search algorithm with real-time visualization"
   - **Visibility:** Public (or Private if you prefer)
   - **⚠️ IMPORTANT:** Leave ALL checkboxes UNCHECKED (don't add README, .gitignore, or license)
4. Click **"Create repository"**

---

### Step 5: Link & Push to GitHub

After creating the repository, run these commands:

```bash
git remote add origin https://github.com/sxvyx/daa-maze-solver-dfs.git
git branch -M main
git push -u origin main
```

---

### Step 6: Verify Upload

1. Go to: `https://github.com/sxvyx/daa-maze-solver-dfs`
2. You should see all your files including the beautiful README!

---

## 🔐 Authentication

When you push, GitHub will ask for credentials:
- **Username:** `sxvyx`
- **Password:** Use a **Personal Access Token** (not your password)

### How to create a Personal Access Token:
1. Go to: https://github.com/settings/tokens
2. Click "Generate new token" → "Generate new token (classic)"
3. Give it a name: "DAA Project Upload"
4. Select scopes: Check `repo` (full control)
5. Click "Generate token"
6. **Copy the token** and save it somewhere safe
7. Use this token as your password when pushing

---

## 📝 Quick Commands (Copy & Paste)

For your convenience, here are all commands in sequence:

```bash
# Navigate to project
cd "c:\Users\savy\OneDrive\Desktop\USB\DAA PROJECT MAZE\MazeSolver-master\MazeSolver-master"

# Configure Git
git config user.name "sxvyx"
git config user.email "YOUR_EMAIL@example.com"

# Initialize and commit
git init
git add .
git commit -m "Initial commit: DAA Mini Project - Maze Solver using DFS Algorithm"

# After creating repo on GitHub, push it
git remote add origin https://github.com/sxvyx/daa-maze-solver-dfs.git
git branch -M main
git push -u origin main
```

---

## ✅ Pre-Push Checklist

Before pushing, verify:
- [ ] Test that `index.html` works in browser
- [ ] README.md has your Canva presentation link ✓
- [ ] All files are in correct locations ✓
- [ ] Logged into **sxvyx** account on GitHub
- [ ] Created repository named `daa-maze-solver-dfs`
- [ ] Have Personal Access Token ready

---

## 🌟 After Upload

### Enable GitHub Pages (Optional - Host it live!)

1. Go to repository → **Settings** → **Pages**
2. Under "Source", select: **main** branch
3. Click **Save**
4. Your site will be live at: `https://sxvyx.github.io/daa-maze-solver-dfs/`

This way professors can see your project running live without downloading!

---

## 🎓 Repository URL

Your final repository will be at:
```
https://github.com/sxvyx/daa-maze-solver-dfs
```

Share this link for your project submission! 🚀

---

## 💡 Troubleshooting

**If you get "remote already exists" error:**
```bash
git remote remove origin
git remote add origin https://github.com/sxvyx/daa-maze-solver-dfs.git
```

**If you want to check current remote:**
```bash
git remote -v
```

**If you need to change the Git user:**
```bash
git config user.name "sxvyx"
git config user.email "your_email@example.com"
```

---

Good luck with your DAA mini project submission! 🎉
