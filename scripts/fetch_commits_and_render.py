#!/usr/bin/env python3
import os
import subprocess
import sys
from datetime import datetime, timedelta
from collections import defaultdict

def run(cmd, cwd=None):
    p = subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE, text=True, check=False)
    if p.returncode != 0:
        raise RuntimeError(
            f"Command failed ({p.returncode}): {' '.join(cmd)}\n"
            f"STDERR:\n{p.stderr}"
        )
    return p.stdout

def get_commit_dates(repo_dir, author_email=None,
                     ignore_merges=False, lookback_days=365):
    since = (datetime.utcnow() - timedelta(days=lookback_days)).strftime("%Y-%m-%d")
    cmd = ["git", "log", f"--since={since}", '--pretty=%ad', '--date=short']
    if author_email:
        cmd.insert(2, f'--author={author_email}')
    if ignore_merges:
        cmd.insert(2, '--no-merges')
    out = run(cmd, cwd=repo_dir)
    dates = [line.strip() for line in out.splitlines() if line.strip()]
    return dates

def generate_calendar_days(lookback_days=365):
    today = datetime.utcnow().date()
    start = today - timedelta(days=lookback_days)
    # align start to Sunday
    start_weekday = start.weekday()  # Monday=0 ... Sunday=6
    sunday_index = (start_weekday + 1) % 7
    start_aligned = start - timedelta(days=sunday_index)
    # extend to include today and align to Saturday
    end = today
    extra = (6 - ((end.weekday() + 1) % 7))
    end_aligned = end + timedelta(days=extra)
    days = []
    d = start_aligned
    while d <= end_aligned:
        days.append(d)
        d += timedelta(days=1)
    return days

def color_for_count(c):
    # GitHub-like green scale
    if c == 0:
        return "#ebedf0"
    elif c <= 3:
        return "#9be9a8"
    elif c <= 6:
        return "#40c463"
    elif c <= 9:
        return "#30a14e"
    else:
        return "#216e39"

def render_svg(daily_counts, days,
               cell_size=12, cell_gap=2,
               top_margin=20, left_margin=30,
               font_family="Inter,Segoe UI,Arial"):
    weeks = (len(days) + 6) // 7
    width = left_margin + weeks * (cell_size + cell_gap)
    height = top_margin + 7 * (cell_size + cell_gap)

    # month labels
    month_x = {}
    for idx, d in enumerate(days):
        if d.day == 1:
            week_idx = idx // 7
            x = left_margin + week_idx * (cell_size + cell_gap)
            month_x[d.strftime("%b")] = x

    svg = []
    svg.append(f'<svg xmlns="http://www.w3.org/2000/svg" '
               f'width="{width}" height="{height}" '
               f'font-family="{font_family}" font-size="10">')
    svg.append('<rect width="100%" height="100%" fill="white"/>')

    # month labels
    for label, x in month_x.items():
        svg.append(f'<text x="{x}" y="12" fill="#57606a">{label}</text>')

    # day labels (Mon, Wed, Fri)
    day_labels = {1: "Mon", 3: "Wed", 5: "Fri"}
    for di, text in day_labels.items():
        y = top_margin + di * (cell_size + cell_gap) + 9
        svg.append(f'<text x="0" y="{y}" fill="#57606a">{text}</text>')

    # cells
    for idx, day in enumerate(days):
        week_idx = idx // 7
        day_of_week = idx % 7
        x = left_margin + week_idx * (cell_size + cell_gap)
        y = top_margin + day_of_week * (cell_size + cell_gap)
        c = daily_counts.get(day, 0)
        fill = color_for_count(c)
        tooltip = f"{c} commits on {day.isoformat()}"
        svg.append(f'<rect x="{x}" y="{y}" width="{cell_size}" '
                   f'height="{cell_size}" rx="2" ry="2" fill="{fill}">')
        svg.append(f'  <title>{tooltip}</title>')
        svg.append('</rect>')

    # legend
    legend_x = width - 5 * (cell_size + cell_gap)
    legend_y = height - (cell_size + 6) + 20  # push legend further down
    svg.append(f'<g transform="translate({legend_x},{legend_y})">')

    svg.append('<text x="-42" y="10" fill="#57606a">Less</text>')
    for i, c in enumerate([0, 1, 4, 7, 10]):
        svg.append(f'<rect x="{i*(cell_size+cell_gap)}" y="0" '
                   f'width="{cell_size}" height="{cell_size}" '
                   f'rx="2" ry="2" fill="{color_for_count(c)}"/>')
    svg.append(f'<text x="{5*(cell_size+cell_gap)+4}" '
               f'y="10" fill="#57606a">More</text>')
    svg.append('</g>')

    svg.append('</svg>')
    return "\n".join(svg)

def main():
    repo_dir = os.environ.get("REPO_DIR", "target-repo")
    author_email = os.environ.get("AUTHOR_EMAIL", "").strip() or None
    ignore_merges = os.environ.get("IGNORE_MERGES", "0") == "1"
    lookback_days = int(os.environ.get("LOOKBACK_DAYS", "365"))
    output_svg = os.environ.get("OUTPUT_SVG", "public/heatmap.svg")

    def ensure_git_repo(path):
        try:
            p = subprocess.run(
                ["git", "-C", path, "rev-parse", "--is-inside-work-tree"],
                stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                text=True, check=True
            )
            if p.stdout.strip().lower() != "true":
                raise RuntimeError("Not inside a git work tree")
        except Exception as e:
            msg = getattr(e, "args", [""])[0] if isinstance(e, RuntimeError) else str(e)
            err = f'ERROR: "{path}" is not a git work tree. {msg}'
            # include git's stderr if available
            if "p" in locals() and p.stderr:
                err += f"\nGIT STDERR:\n{p.stderr}"
            print(err, file=sys.stderr)
            sys.exit(2)

    # …
    ensure_git_repo(repo_dir)

    dates = get_commit_dates(repo_dir,
                             author_email=author_email,
                             ignore_merges=ignore_merges,
                             lookback_days=lookback_days)

    counts = defaultdict(int)
    for d in dates:
        y, m, day = map(int, d.split("-"))
        counts[datetime(y, m, day).date()] += 1

    days = generate_calendar_days(lookback_days=lookback_days)
    daily_counts = {d: counts.get(d, 0) for d in days}

    svg = render_svg(daily_counts, days)

    os.makedirs(os.path.dirname(output_svg), exist_ok=True)
    with open(output_svg, "w", encoding="utf-8") as f:
        f.write(svg)

    print(f"Wrote {output_svg}")

if __name__ == "__main__":
    main()
