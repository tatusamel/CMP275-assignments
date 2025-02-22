import matplotlib.pyplot as plt
import numpy as np

# Updated benchmark data (excluding "Load") for each API task.
# Values: Time (s)
data = {
    "Date Range Search": {
        "Seq AOO": 0.12938,
        "Par 2 AOO": 0.307812,
        "Par 4 AOO": 0.215125,
        "Par 8 AOO": 0.197377,
        "Par 16 AOO": 0.249921,
        "Par 2 OOA": 0.168711,
        "Par 4 OOA": 0.176306,
        "Par 8 OOA": 0.194987,
        "Par 16 OOA": 0.230484,
    },
    "Borough Search": {
        "Seq AOO": 0.369347,
        "Par 2 AOO": 0.673565,
        "Par 4 AOO": 0.588974,
        "Par 8 AOO": 0.593218,
        "Par 16 AOO": 0.544412,
        "Par 2 OOA": 0.673076,
        "Par 4 OOA": 0.514246,
        "Par 8 OOA": 0.590563,
        "Par 16 OOA": 0.601757,
    },
    "Zip Code Search": {
        "Seq AOO": 0.0829295,
        "Par 2 AOO": 0.198326,
        "Par 4 AOO": 0.140214,
        "Par 8 AOO": 0.129948,
        "Par 16 AOO": 0.144978,
        "Par 2 OOA": 0.0692444,
        "Par 4 OOA": 0.0959593,
        "Par 8 OOA": 0.107345,
        "Par 16 OOA": 0.123495,
    },
    "Injury Threshold Search": {
        "Seq AOO": 0.143168,
        "Par 2 AOO": 0.245274,
        "Par 4 AOO": 0.192813,
        "Par 8 AOO": 0.173892,
        "Par 16 AOO": 0.198615,
        "Par 2 OOA": 0.114497,
        "Par 4 OOA": 0.12525,
        "Par 8 OOA": 0.147917,
        "Par 16 OOA": 0.184352,
    },
    "Location Bounds Search": {
        "Seq AOO": 1.64788,
        "Par 2 AOO": 2.50908,
        "Par 4 AOO": 1.9738,
        "Par 8 AOO": 2.11721,
        "Par 16 AOO": 3.15521,
        "Par 2 OOA": 3.01326,
        "Par 4 OOA": 2.72888,
        "Par 8 OOA": 3.46847,
        "Par 16 OOA": 4.55543,
    },
}

# For each task, we want three values:
#   1. Sequential value (Phase1)
#   2. Best Phase2 value: minimum among keys starting with "Par" and containing "AOO" (but not OOA)
#   3. Best Phase3 value: minimum among keys containing "OOA"
best_data = {}
thread_info = {}  # to store the chosen key (which includes the thread count)
for task, results in data.items():
    seq_val = results["Seq AOO"]
    # Filter for Phase2 keys: those starting with "Par" and containing "AOO" but not "OOA"
    phase2_keys = [k for k in results.keys() if k.startswith("Par") and "AOO" in k and "OOA" not in k]
    best_AOO_key = min(phase2_keys, key=lambda k: results[k])
    best_AOO_val = results[best_AOO_key]
    
    # Filter for Phase3 keys: those containing "OOA"
    phase3_keys = [k for k in results.keys() if "OOA" in k]
    best_OOA_key = min(phase3_keys, key=lambda k: results[k])
    best_OOA_val = results[best_OOA_key]
    
    best_data[task] = [seq_val, best_AOO_val, best_OOA_val]
    thread_info[task] = (best_AOO_key, best_OOA_key)

# Define colors for each phase.
phase_colors = {
    "Phase1": "skyblue",    # Sequential
    "Phase2": "seagreen",   # Multithreading (AOO)
    "Phase3": "salmon"      # Multithreading (OOA)
}

# Tasks to display.
tasks = list(best_data.keys())
n_tasks = len(tasks)

# Prepare the data arrays for plotting.
phase1_times = [best_data[task][0] for task in tasks]
phase2_times = [best_data[task][1] for task in tasks]
phase3_times = [best_data[task][2] for task in tasks]

# Plot parameters.
bar_width = 0.25
x = np.arange(n_tasks)

fig, ax = plt.subplots(figsize=(12, 7))

# Plot three bars for each task: sequential, best Phase2, and best Phase3.
bars1 = ax.bar(x - bar_width, phase1_times, width=bar_width, color=phase_colors["Phase1"], label="Sequential (Phase1)")
bars2 = ax.bar(x, phase2_times, width=bar_width, color=phase_colors["Phase2"], label="Best Phase2\n(MT, AOO)")
bars3 = ax.bar(x + bar_width, phase3_times, width=bar_width, color=phase_colors["Phase3"], label="Best Phase3\n(MT, OOA)")

# Set x-axis labels.
ax.set_xticks(x)
ax.set_xticklabels(tasks, rotation=45, ha="right", fontsize=12)

ax.set_xlabel("API Task", fontsize=14)
ax.set_ylabel("Time (s)", fontsize=14)
ax.set_title("Efficient Benchmark Comparison by Task", fontsize=16)

# Annotate bars with time and thread count for Phase2 and Phase3.
def autolabel(bars, phase=None):
    for i, bar in enumerate(bars):
        height = bar.get_height()
        text = f"{height:.3f}"
        if phase in ["Phase2", "Phase3"]:
            task = tasks[i]
            key = thread_info[task][0] if phase == "Phase2" else thread_info[task][1]
            # Extract thread count from the key, e.g., "Par 8 AOO" -> "8"
            thread_count = key.split()[1]
            text += f"\n({thread_count} threads)"
        # Place annotation in the middle of the bar (or just above, if the bar is short)
        ax.annotate(text,
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha="center", va="bottom", fontsize=10)

autolabel(bars1)  # sequential bars (no thread info)
autolabel(bars2, phase="Phase2")
autolabel(bars3, phase="Phase3")

# Add legend.
ax.legend(fontsize=12)

plt.tight_layout()
plt.show()
