

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

````markdown
## 🍬🍭 Bubblegum Bonus: “How to Use This for **Your** Shizz” 💖🦄✨

Wanna spin up your **own** sparkle-tastic heatmaps? YAAAS 💅💚  
Here’s how *anyone* can copy this hotness and make it theirs (fork-safe, zero drama) 🎀🛡️

### 1) 🍴 Fork this repo (or clone it)
- Click **Fork** (top-right) → land it in your account 💼
- OR:  
  ```bash
  git clone https://github.com/<you>/<fork-name>.git
  cd <fork-name>
````

### 2) 🔐 Add your *own* token (for private repos)

> Public repos? Skip this 💨
> Private/cross-org? Add a Personal Access Token with **Contents: Read** (fine-grained) and SSO authorized if needed.

* Repo → **Settings → Secrets and variables → Actions → New repository secret**
* **Name:** `TARGET_REPO_TOKEN`
* **Value:** your PAT 🔑

*(Secrets never copy from my repo to yours — your fork is 💯 independent.)*

### 3) 🧾 Tell the workflow which repos to chart

Create or edit **`.heatmap-repos.txt`** (one per line):

```
owner1/repoA
owner2/repoB
# Optional global settings:
# AUTHOR_EMAIL=you@example.com
# IGNORE_MERGES=1
# LOOKBACK_DAYS=365
```

### 4) 🌐 Turn on GitHub Pages (the stage for your art)

* Repo → **Settings → Pages** → Source = **GitHub Actions** ✅

### 5) 🤖 Run the workflow (two flavors, same glow)

* **Manual**: Actions → **Build Heatmaps (Dynamic Prompt / Nightly)** → **Run workflow** ▶️
* **Nightly**: the scheduled job runs ~every day while you sleep 😴✨

### 6) 📎 Paste the magic links into ClickUp

After a run completes:

* **Gallery:** `https://<you>.github.io/<fork-name>/`
* **Per repo SVGs:** `https://<you>.github.io/<fork-name>/heatmap-<owner>-<repo>.svg`
* Drop those into **Custom Embed** widgets in ClickUp 💘📊

> 💡 Pro tip: if an embed looks cached, add `?v=YYYYMMDDHHMM` to the end of the URL for a fresh glow-up.

---

### 🛡️ Safety & Boundaries (aka “No Grief, All Glitter”) ✋✨

* Forks can reuse the **code**, but they **cannot** change **your** Pages or **your** ClickUp embeds.
* **Secrets don’t copy**, and `GITHUB_TOKEN` is scoped to their fork — they bring their own snacks 🍿.
* Want to keep things private? Make your repo **private** and invite collaborators only.
* Happy to share? Add a **license** (MIT, etc.) so folks know the vibes 💞📜.

Now go forth and **paint the dashboard green** 💚🟩💚 — one glorious commit at a time! 🚀🎉