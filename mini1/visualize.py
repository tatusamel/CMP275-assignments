import matplotlib.pyplot as plt
import numpy as np

# Updated benchmark data for each API task.
# Values: Time (s)
benchmark_data = {
    "Load": {
        "Seq AOO": 12.3954,
        "Par 2 AOO": 10.4273,
        "Par 4 AOO": 8.25447,
        "Par 8 AOO": 6.81033,
        "Par 2 OOA": 5.69145,
        "Par 4 OOA": 3.59584,
        "Par 8 OOA": 2.33215,
    },
    "Date Range Search": {
        "Seq AOO": 1.84084,
        "Par 2 AOO": 3.04861,
        "Par 4 AOO": 2.74213,
        "Par 8 AOO": 2.74882,
        "Par 2 OOA": 3.6841,
        "Par 4 OOA": 3.9461,
        "Par 8 OOA": 2.91046,
    },
    "Borough Search": {
        "Seq AOO": 0.307546,
        "Par 2 AOO": 0.491375,
        "Par 4 AOO": 0.486035,
        "Par 8 AOO": 0.459866,
        "Par 2 OOA": 0.552908,
        "Par 4 OOA": 0.47747,
        "Par 8 OOA": 0.433623,
    },
    "Zip Code Search": {
        "Seq AOO": 0.185716,
        "Par 2 AOO": 0.187902,
        "Par 4 AOO": 0.167609,
        "Par 8 AOO": 0.143947,
        "Par 2 OOA": 0.0935798,
        "Par 4 OOA": 0.12004,
        "Par 8 OOA": 0.232731,
    },
    "Injury Threshold Search": {
        "Seq AOO": 0.104813,
        "Par 2 AOO": 0.18945,
        "Par 4 AOO": 0.187283,
        "Par 8 AOO": 0.163831,
        "Par 2 OOA": 0.11032,
        "Par 4 OOA": 0.130446,
        "Par 8 OOA": 0.15099,
    },
    "Location Bounds Search": {
        "Seq AOO": 0.977417,
        "Par 2 AOO": 2.1197,
        "Par 4 AOO": 1.84341,
        "Par 8 AOO": 2.07033,
        "Par 2 OOA": 2.93392,
        "Par 4 OOA": 2.10901,
        "Par 8 OOA": 2.96771,
    },
}

# We'll aggregate the data as follows:
# Phase1: "Seq AOO"
# Phase2: Average of "Par 2 AOO", "Par 4 AOO", "Par 8 AOO"
# Phase3: Average of "Par 2 OOA", "Par 4 OOA", "Par 8 OOA"
phases = ["Phase1", "Phase2", "Phase3"]

# Prepare aggregated data per task
aggregated_data = {}
for task, results in benchmark_data.items():
    phase1 = results["Seq AOO"]
    phase2 = np.mean([results["Par 2 AOO"], results["Par 4 AOO"], results["Par 8 AOO"]])
    phase3 = np.mean([results["Par 2 OOA"], results["Par 4 OOA"], results["Par 8 OOA"]])
    aggregated_data[task] = [phase1, phase2, phase3]

# Tasks to display
tasks = list(aggregated_data.keys())
n_tasks = len(tasks)

# Define colors for each phase.
phase_colors = {
    "Phase1": "skyblue",    # No multithreading, Array of Objects
    "Phase2": "seagreen",   # Multithreading, Array of Objects
    "Phase3": "salmon"      # Multithreading, Object of Arrays
}

# Plot parameters
bar_width = 0.25
x = np.arange(n_tasks)

fig, ax = plt.subplots(figsize=(12, 7))

# Extract the times for each phase across tasks.
phase1_times = [aggregated_data[task][0] for task in tasks]
phase2_times = [aggregated_data[task][1] for task in tasks]
phase3_times = [aggregated_data[task][2] for task in tasks]

# Plot bars for each phase with a slight shift.
bars1 = ax.bar(x - bar_width, phase1_times, width=bar_width,
               color=phase_colors["Phase1"], label="Phase1\n(No MT, Array of Objects)")
bars2 = ax.bar(x, phase2_times, width=bar_width,
               color=phase_colors["Phase2"], label="Phase2\n(MT, Array of Objects)")
bars3 = ax.bar(x + bar_width, phase3_times, width=bar_width,
               color=phase_colors["Phase3"], label="Phase3\n(MT, Object of Arrays)")

# Set x-axis with task names.
ax.set_xticks(x)
ax.set_xticklabels(tasks, rotation=45, ha="right", fontsize=12)

# Set labels and title.
ax.set_xlabel("API Task", fontsize=14)
ax.set_ylabel("Time (s)", fontsize=14)
ax.set_title("Performance Comparison: Phase1 vs Phase2 vs Phase3", fontsize=16)

# Add data labels above each bar.
def autolabel(bars):
    for bar in bars:
        height = bar.get_height()
        ax.annotate(f"{height:.2f}",
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),
                    textcoords="offset points",
                    ha="center", va="bottom", fontsize=10)

autolabel(bars1)
autolabel(bars2)
autolabel(bars3)

# Add a legend.
ax.legend(fontsize=12)


plt.tight_layout()
plt.show()
