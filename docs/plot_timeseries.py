# ----------------------------------------------------------------------
#
# File: plot_timeseries.py
#
# Last edited: 17.04.2025
#
# Copyright (c) 2025 ETH Zurich and University of Bologna
#
# Authors:
# - Philip Wiese (wiesep@iis.ee.ethz.ch), ETH Zurich
#
# ----------------------------------------------------------------------
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the License); you may
# not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an AS IS BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

font_size = 20

# Get foldername of this script
from utils import get_script_folder

script_folder = get_script_folder()

voltage = 3.6

# Load CSV file (update path if needed)
# file_path = f"{script_folder}/512x512_Idle_GAP_ppk-20250416T215043.csv"
file_path = f"/Users/wiesep/Polybox/Projects/SENSEI/Results/512x512_Idle_3V6_ppk-20250416T215043.csv"

# Read CSV and fix header
df = pd.read_csv(file_path, sep = ",")
df.columns = [col.strip() for col in df.columns]

# Convert relevant columns
df = df.astype({'Timestamp(ms)': float, 'Current(uA)': float, 'D1': int})

print(df["Timestamp(ms)"].min())
# Remove timestamp bias
df["Timestamp(ms)"] = df["Timestamp(ms)"] - df["Timestamp(ms)"].min()

df = df[df["Timestamp(ms)"] >= 0]

# Extract first change of D1
first_d1_change = df[df["D1"] != df["D1"].iloc[0]].index[0]

jumps = np.diff(df["D1"])
jumps = np.where(jumps != 0)[0] + 1
print("Jumps:", jumps)
timestamps_jumps = df["Timestamp(ms)"].iloc[jumps] - df["Timestamp(ms)"].iloc[jumps[0]]
print("Timestamp jumps:", timestamps_jumps)

df["Timestamp(ms)"] = df["Timestamp(ms)"] - (df["Timestamp(ms)"].iloc[jumps[0]])

df = df[df["Timestamp(ms)"] >= 0]

# Extract data
time_ms = df["Timestamp(ms)"]
current_uA = df["Current(uA)"]
d1_signal = df["D1"]

# Convert to power in mW assuming 3.6V
current_mA = current_uA / 1000
power_mW = current_mA * voltage

# nRF Standby Power
# power_offset = 4.21*1.8

# Total Standby Power - GAP9 Standby Power
power_offset = 8.86 * voltage - 11.505 * 1.8

print("Power Offset:", power_offset)
power_mW -= power_offset

# Calculate 1ms moving average
sampling_interval_ms = np.mean(np.diff(time_ms))
window_size_1ms = max(1, int(1 / sampling_interval_ms))
moving_avg_power = power_mW.rolling(window = window_size_1ms, center = True).mean()

# Detect D1 transitions to mark sections
sections = []
start_idx = 0
for i in range(1, len(d1_signal)):
    if d1_signal.iloc[i] != d1_signal.iloc[i - 1]:
        sections.append((time_ms.iloc[start_idx], time_ms.iloc[i]))
        start_idx = i
sections.append((time_ms.iloc[start_idx], time_ms.iloc[-1]))

# Fuse the section after NMS with the NMS secton
# sections[4] = (sections[4][0], sections[5][1])
# sections = sections[:5] + [sections[6]]  # Remove the last section

# Section labels (last inherits first's label/color)
labels = ["Image\nAcquisition", "Image\nPreprocessing", "NN\nInference", "NMS"]

# Prepare color palette
palette = sns.color_palette("pastel", len(sections))
region_colors = list(palette)
region_colors[3] = "red"

print("Sections:")
for i, (start, end) in enumerate(sections):
    if i < len(labels):
        print(
            f"Section {i}: {labels[i].replace('\n', ' ')} from {start:.1f}ms to {end:.1f}ms, color {region_colors[i]}")
    else:
        print(f"Section {i}: Unknown from {start:.1f}ms to {end:.1f}ms")

# Plotting
fig, ax = plt.subplots(figsize = (14, 6))

# Draw shaded regions and annotations
for i, (start, end) in enumerate(sections):
    ax.axvspan(start, end, fc = region_colors[i], alpha = 0.3, ec = region_colors[i], linewidth = 2)
    if i < len(labels):
        mid = (start + end) / 2
        # if i == 1:
        #     mid -= 2
        # elif i == 2:
        #     mid += 2
        if i == 3:
            mid -= 4
        ax.annotate(labels[i],
                    xy = (mid, 0.90),
                    xycoords = ("data", "axes fraction"),
                    ha = 'center',
                    va = 'center',
                    fontsize = font_size,
                    color = 'black',
                    backgroundcolor = 'white')

# Plot original and smoothed power signals
ax.plot(time_ms, power_mW, color = 'black', linewidth = 0.8, label = 'Power (mW)')
ax.plot(time_ms, moving_avg_power, color = 'red', linewidth = 1.5, label = '1ms Moving Average')

# Plot average reference line
# ax.axhline(103.2, color='red', linestyle=':', linewidth=1.5, label='Avg Power (103.2 mW)')

# Final plot styling
ax.set_xlim(left = timestamps_jumps.iloc[0], right = timestamps_jumps.iloc[-2])
ax.set_ylim(bottom = 0, top = 225)
ax.set_xlabel("Time [ms]", fontsize = font_size)
ax.set_ylabel("Power [mW]", fontsize = font_size)
# Set font size for ticks
ax.tick_params(axis = 'both', which = 'major', labelsize = font_size - 4)
ax.grid(True)

# Legend below the plot
ax.legend(loc = 'upper center', bbox_to_anchor = (0.5, -0.12), ncol = 2, fontsize = font_size)

plt.tight_layout()

# Save figure
fig.savefig(f'{script_folder}/plot_timeseries.png', dpi = 600, bbox_inches = 'tight')
fig.savefig(f'{script_folder}/plot_timeseries.pdf', dpi = 600, bbox_inches = 'tight')

# Calculate the average in the tamefimre window
time_window = (timestamps_jumps.iloc[0], timestamps_jumps.iloc[-2])
mask = (time_ms >= time_window[0]) & (time_ms <= time_window[1])
average_power = moving_avg_power[mask].mean()
print(f"Average power in the time window {time_window[0]}ms to {time_window[1]}ms: {average_power:.2f} mW")

plt.show()
