# 🟩📊 Git Commit Heatmap → ClickUp Dashboard Embed 🚀✨🔥💻💡

Welcome to your **personal GitHub-style contribution graph** 🖥️✨ → rendered as an **SVG heatmap** 🎨🟢 → published with **GitHub Pages** 🌐🌍 → embedded right into **ClickUp** 🗂️📊💪.  

This repo is tiny but mighty 💥⚡: it takes commit history from **one repo of your choice** 🛠️🔧, generates a **green squares heatmap** 🟩🟩🟩, and makes it available at a stable URL 🔗🌈 for you to drop into a ClickUp **Custom Embed card** 🖼️📌🎯.

---

## ⚡ How it Works 🤖🛠️📅

1. **GitHub Actions Workflow** 🤖⚙️  
   - Runs nightly 🌙🌜 or on demand 🕹️▶️  
   - Checks out your **target repo** 📂🗃️  
   - Runs a Python script 🐍👨‍💻 to parse commit history (`git log`) 📜  
   - Generates a **SVG calendar heatmap** 📅✨🎨  
   - Publishes it via **GitHub Pages** 🌐🚀  

2. **Result** 🎯🥳  
   - A beautiful URL like:  
     👉 `https://<you>.github.io/<heatmap-repo>/heatmap.svg` 🌈  
   - Embed this directly into ClickUp ✅📊💡  

---

## 🛠️ Setup Steps 📝🔧🚦

1. **Clone this repo** 💾⬇️  
```bash
git clone https://github.com/<you>/<heatmap-repo>.git
cd <heatmap-repo>
```

2. **Configure workflow** 📝⚙️🔐  
In `.github/workflows/heatmap.yml` set environment variables:  
- `TARGET_REPO` → `"owner/name"` 🏷️  
- `AUTHOR_EMAIL` → `"you@example.com"` (optional 📧)  
- `IGNORE_MERGES` → `"1"` to hide merges 🙅‍♂️  
- `LOOKBACK_DAYS` → `"365"` or any number 📅⏳  

3. **Push changes** ⬆️📤🌟  
```bash
git add .
git commit -m "Initial setup 🌱✨💻"
git push origin main
```

4. **Enable GitHub Pages** 🌐🚀  
- Repo → ⚙️ **Settings** → **Pages** → Source: **GitHub Actions** 🔄  
- Run the workflow once manually ▶️💪  

5. **Embed in ClickUp** 🗂️📊🎉  
- Go to **Dashboard** 📊📈 → Add **Custom Embed card** ➕  
- Paste the `heatmap.svg` URL 🔗✨  
- Enjoy your live contribution graph inside ClickUp 🎉🥳🔥  

---

## 📦 Files in this repo 📂📝🛠️

- `.github/workflows/heatmap.yml` 🤖⚡ → Automation pipeline  
- `scripts/fetch_commits_and_render.py` 🐍📜 → SVG generator  
- `public/heatmap.svg` 🟩✨ → Output file (published to Pages)  
- `public/README.md` 📖📄 → Placeholder so folder exists  

---

## 🌈 Example Output 🟩🟩🟩

![example heatmap](https://github.githubassets.com/images/modules/profile/contributions/contributions.png)  
*(Yours will look like this, but scoped to your repo 👌🚀)*

---

## 💡 Notes & Tips 🧠📌💥

- Private repo? 🔒🔑 → Use a **PAT** token as `TARGET_REPO_TOKEN` secret.  
- Want multiple repos? 📂📂📂 → Duplicate workflow and output to `heatmap-repoA.svg`, `heatmap-repoB.svg`.  
- Don’t like green? 🎨🌈 → Edit `color_for_count()` in the script to customize the palette.  
- Need more history? ⏳⌛ → Increase `LOOKBACK_DAYS` to 730 (two years) or more.  

---

## 🎉 Done! 🥳🔥💻

Now every day you commit code 💻📜 → your ClickUp dashboard gets greener 🟩🟩🟩 → and you stay motivated 🚀🔥💪.  

Happy coding! ✨🐍⚡🟩🌟🎉
