# 🌐 Deploy to GitHub Pages - Step by Step

## What is GitHub Pages?
GitHub Pages hosts your website directly from your GitHub repository for **FREE**. Your maze solver will be live at:
```
https://sxvyx.github.io/daa-maze-solver-dfs/
```

---

## 📋 Steps to Enable GitHub Pages

### Method 1: Using GitHub Website (Easiest)

1. **Go to your repository:**
   - Visit: `https://github.com/sxvyx/daa-maze-solver-dfs`

2. **Open Settings:**
   - Click the **"Settings"** tab (top right of repository)

3. **Navigate to Pages:**
   - In the left sidebar, click **"Pages"**
   - Or go directly to: `https://github.com/sxvyx/daa-maze-solver-dfs/settings/pages`

4. **Configure Source:**
   - Under **"Source"** section:
     - Branch: Select **"main"** from dropdown
     - Folder: Select **"/ (root)"**
   - Click **"Save"**

5. **Wait for deployment (1-2 minutes):**
   - GitHub will show: "Your site is ready to be published at..."
   - Refresh the page after a minute
   - You'll see: "Your site is live at https://sxvyx.github.io/daa-maze-solver-dfs/"

6. **Visit your live site:**
   - Click the link or visit: `https://sxvyx.github.io/daa-maze-solver-dfs/`

---

### Method 2: Using Command Line (Alternative)

If you prefer using commands, you can enable it via GitHub API:

```bash
# This requires GitHub CLI (gh)
gh api repos/sxvyx/daa-maze-solver-dfs/pages -X POST -f source[branch]=main -f source[path]=/
```

---

## ✅ Verification

Once enabled, verify your site is live:

1. Visit: `https://sxvyx.github.io/daa-maze-solver-dfs/`
2. You should see your beautiful maze solver with:
   - Modern dark theme UI
   - DFS visualization working
   - All controls functional

---

## 🎯 Benefits of GitHub Pages

✅ **Free hosting** - No cost whatsoever
✅ **Custom URL** - Professional looking link
✅ **Auto-updates** - Any push to main branch updates the site
✅ **Perfect for demos** - Share with professors/classmates
✅ **No server needed** - Everything runs in the browser

---

## 📝 Add to Your Project Submission

Include the live demo link in your project report:

```
🔗 Live Demo: https://sxvyx.github.io/daa-maze-solver-dfs/
🔗 GitHub Repo: https://github.com/sxvyx/daa-maze-solver-dfs
🔗 Presentation: https://www.canva.com/design/DAG56xbwWRQ/...
```

---

## 🐛 Troubleshooting

**Site not loading?**
- Wait 2-3 minutes after enabling Pages
- Clear browser cache (Ctrl + F5)
- Check Settings → Pages shows "Your site is live"

**Getting 404 error?**
- Make sure `index.html` is in the root directory ✓
- Verify main branch is selected
- Check the branch name is exactly "main"

**CSS/JS not loading?**
- All file references in `index.html` are relative ✓
- Files are in the same directory as `index.html` ✓

---

## 🚀 Your Live URLs

Once deployed:

- **Live Demo:** https://sxvyx.github.io/daa-maze-solver-dfs/
- **Repository:** https://github.com/sxvyx/daa-maze-solver-dfs
- **Canva Presentation:** [Your existing link]

Share these with anyone to showcase your project! 🎉

---

## 📸 Before Submitting

Take screenshots of:
1. ✅ The GitHub repository page
2. ✅ The live website running
3. ✅ The DFS algorithm solving a maze
4. ✅ Include in your project report

Good luck with your submission! 🎓
