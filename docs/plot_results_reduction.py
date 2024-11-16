# ----------------------------------------------------------------------
#
# File: plot_results.py
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
# distributed under the License is distributed on an AS IS BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import matplotlib.pyplot as plt
import numpy as np
# Get foldername of this script
from utils import get_script_folder

WIDTH = 40

## Set font to Sans
plt.rcParams['font.family'] = 'Sans'

# Data
image_sizes1 = ['320\n×\n240', '640\n×\n240']
# image_sizes1 = ['320240\nQVGA', '640x480\nVGA']
energy_per_frame1 = [7.86, 20.62]
position1 = np.array([0, 5])

# image_sizes2 = ['64x64', '128x128', '192x192', '256x256', '320x320', '384x384', '448x448', '512x512']
image_sizes2 = [
    '64\n×\n64', '128\n×\n128', '192\n×\n192', '256\n×\n256', '320\n×\n320', '384\n×\n384', '448\n×\n448', '512\n×\n512'
]
# image_sizes2 = ['64', '128', '192', '256', '320', '384', '448', '512']
energy_per_frame2 = [3.46, 3.93, 4.58, 5.80, 7.38, 9.19, 11.45, 14.84]
position2 = np.array([1, 2, 3, 4, 6, 7, 8, 9])

image_sizes_numeric = []
image_sizes = []
for i in range(len(image_sizes1) + len(image_sizes2)):
    print(i)
    if i in position1:
        index = np.where(position1 == i)[0][0]
        image_sizes_numeric.append(position1[index] * WIDTH)
        image_sizes.append(image_sizes1[index])
    if i in position2:
        index = np.where(position2 == i)[0][0]
        image_sizes_numeric.append(position2[index] * WIDTH)
        image_sizes.append(image_sizes2[index])

# Create figure and axes
fig, ax1 = plt.subplots(figsize = (7, 5))

# Font and marker size
marker_size = 150
font_size = 14

# Set x-axis
# ax1.set_xlabel('Image Size [pixels]', fontsize = font_size)
ax1.set_ylabel("Energy/Frame [mJ]", fontsize = font_size)
ax1.set_xticks(image_sizes_numeric)
ax1.set_xticklabels(image_sizes)

import matplotlib as mpl

mpl.rcParams['hatch.linewidth'] = 2.0
plt.rcParams['hatch.color'] = 'white'

# Plot energy/frame as scatter

bars = ax1.bar(
    position1 * WIDTH,
    energy_per_frame1,
    color = '#a8322c',
    width = 20,
    linewidth = 20,
    label = 'Streaming\n(Full Image)',
    zorder = 1,
)

bars = ax1.bar(
    position2 * WIDTH,
    energy_per_frame2,
    color = '#168638',
    width = 20,
    linewidth = 20,
    label = 'AI Inference\n(Bounding Boxes)',
    zorder = 1,
)

# Y-axis limits
ymin = 0
ymax = 21
ax1.set_ylim(ymin, ymax)

# set yticks to 5 er step
ax1.set_yticks(np.arange(0, ymax + 1, 5))
ax1.set_yticklabels(np.arange(0, ymax + 1, 5))

from matplotlib.ticker import AutoMinorLocator

ax1.set_axisbelow(True)
ax1.yaxis.set_minor_locator(AutoMinorLocator())
ax1.grid(True, which = 'major', linestyle = '-', linewidth = 0.5, alpha = 1)
ax1.grid(which = 'minor', linestyle = '--', linewidth = 0.5, alpha = 0.7)
# ax1.tick_params(axis = 'both', which = 'major', labelsize = font_size-4)
# Make bold
for label in ax1.get_xticklabels():
    label.set_fontsize(font_size - 4)
    # label.set_weight('bold')
    label.set_linespacing(0.8)

# Legend
ax1.legend(loc = 'upper left', ncol = 1, fontsize = font_size)

fig.tight_layout()

script_folder = get_script_folder()

# Save figure
fig.savefig(f'{script_folder}/plot_results_reduction.png', dpi = 300, bbox_inches = 'tight')
fig.savefig(f'{script_folder}/plot_results_reduction.pdf', dpi = 300, bbox_inches = 'tight')

plt.show()
