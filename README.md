

# ⚡🟩🔥 Git Commit Heatmaps → ClickUp Dashboard 💻📊🚀🎉🌈✨

Welcome, code warrior 🦸‍♂️🦸‍♀️!  
This repo turns your **GitHub repos** 🐙📂 into dazzling **contribution heatmaps** 🎨🟩🟩🟩 — published with **GitHub Pages** 🌐🚀 — and embeddable straight into your **ClickUp dashboards** 🗂️📊💡.  
No more boring dashboards… now you’ve got 💚**green power-ups**💚 every day you commit! ⚡🌟🔥

---

## 🎬 How It Works 🎥🤖🛠️💡

1. **GitHub Actions Workflow** 🤖⚙️🎯  
   - Runs **nightly** 🌙💤 *or* on-demand 🕹️▶️  
   - Clones your **target repo(s)** 📂📂📂  
   - Runs the **Python heatmap engine** 🐍🔥📜  
   - Builds a **SVG calendar-style heatmap** 📅🎨💚  
   - Publishes to **GitHub Pages** 🌍🚀✨  

2. **Result** 🏆🎉🌈  
   - Beautiful URLs like:  
     👉 `https://<you>.github.io/<heatmap-host>/heatmap-<repo>.svg`  
   - Paste straight into ClickUp ➕✅  
   - Boom 💥 — live contribution graphs inside your dashboards! 📊💚🔥  

---

## 🛠️ Setup Steps 📝🔧🚦

### 1️⃣ Clone this repo ⬇️💾
```bash
git clone https://github.com/<you>/<heatmap-host>.git
cd <heatmap-host>
````

### 2️⃣ Add your repo list 📜📂

In `.heatmap-repos.txt` write lines like:

```
owner1/repoA
owner2/repoB
```

👉 You can also drop in settings:

* `AUTHOR_EMAIL=you@example.com` 📧
* `IGNORE_MERGES=0` 🔀
* `LOOKBACK_DAYS=730` ⏳

### 3️⃣ Push changes ⬆️📤

```bash
git add .
git commit -m "✨🔥 setup heatmap workflow 🟩💻🚀"
git push origin main
```

### 4️⃣ Enable Pages 🌐🚀

* Repo → ⚙️ Settings → Pages → Source = **GitHub Actions** 🛠️
* Run the workflow once ▶️💡

### 5️⃣ Embed in ClickUp 🖼️📊

* Dashboard → ➕ Add **Custom Embed**
* Paste your SVG URL 🔗🌈
* Bask in the glory of your green squares 💚🟩💚

---

## 📦 Repo Contents 📂🧰

* `.github/workflows/heatmap.yml` 🤖⚡ — workflow brain
* `.github/workflows/heatmap_nightly.yml` ⏰🌙 — nightly auto-refresh
* `scripts/fetch_commits_and_render.py` 🐍🎨 — SVG maker
* `.heatmap-repos.txt` 📜🗂️ — repo list + config
* `public/heatmap-*.svg` 🟩✨ — your heatmaps 🌈

---

## 🌟 Example Output 🎨🟩

![example heatmap](https://github.githubassets.com/images/modules/profile/contributions/contributions.png)
(Yours will be **repo-specific** 🔧⚡💚)

---

## 💡 Tips & Tricks 🧠🛠️

* 🔒 Private repos? → Add a `TARGET_REPO_TOKEN` secret 🔑
* 🎨 Don’t like green? Edit `color_for_count()` to pick your palette 🌈🖌️
* ⏳ Want more history? Set `LOOKBACK_DAYS=1095` for 3 years 📜
* 📊 Multiple repos? → They’ll all show up on the **gallery page** 🌐✨

---

## 🎉 That’s it! 🎊🔥💻

Commit ➡️ Heatmap updates 🟩
Dashboard ➡️ Always fresh 📊
You ➡️ Motivated AF 🚀💪🔥

Happy coding, green-square hero! 🦸‍♂️🦸‍♀️💚⚡🌈🎉

```

Would you like me to also add a **tiny “Gallery Preview” section** at the top of the README that links directly to your live Pages site (so ClickUp and teammates can click it fast)?
```
