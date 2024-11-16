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
from matplotlib import transforms
# Get foldername of this script
from utils import get_script_folder

# Data
image_sizes = ['64x64', '128x128', '192x192', '256x256', '320x320', '384x384', '448x448', '512x512']
image_sizes_numeric = [64, 128, 192, 256, 320, 384, 448, 512]
mAP50 = [4.1, 18.7, 35.1, 47.6, 62.4, 73.1, 80.2, 84.7]
energy_per_frame = [1.50, 1.98, 2.63, 3.87, 5.46, 7.29, 9.57, 12.99]
efficiency = map(lambda x, y: x / y, mAP50, energy_per_frame)
efficiency = list(efficiency)

print('Efficiency:', efficiency)

# Create figure and axes
fig, ax1 = plt.subplots(figsize = (10, 6))

# Font and marker size
marker_size = 150
font_size = 14

# Set x-axis
ax1.set_xlabel('Image Size [pixels]', fontsize = font_size)
ax1.set_xticks(image_sizes_numeric)
ax1.set_xticklabels(image_sizes, fontsize = font_size)

import matplotlib as mpl

mpl.rcParams['hatch.linewidth'] = 2.0
plt.rcParams['hatch.color'] = 'white'
# plt.rcParams['text.usetex'] = True
# Plot gray hatched bars for efficiency (on primary axis)
bars = ax1.bar(
    image_sizes_numeric,
    efficiency,
    color = 'gray',

    # edgecolor='black',
    hatch = '///',
    width = 20,
    linewidth = 20,
    label = 'Efficiency',
    zorder = 1,
)

# Plot energy/frame as scatter + trendline (on primary axis)
color2 = 'tab:red'
marker2 = ax1.scatter(image_sizes_numeric,
                      energy_per_frame,
                      color = color2,
                      marker = '^',
                      s = marker_size,
                      label = 'Energy/Frame',
                      zorder = 2)

poly_coeffs_energy = np.polyfit(image_sizes_numeric, energy_per_frame, 2)
poly_energy = np.poly1d(poly_coeffs_energy)
x_fit = np.linspace(min(image_sizes_numeric), max(image_sizes_numeric), 100)
marker2_fit = ax1.plot(
    x_fit,
    poly_energy(x_fit),
    color = color2,
    linestyle = ':',
    #  label ='Energy/Frame Fit',
    label = 'Poly. Fit (2nd order)',
    linewidth = 2,
    alpha = 0.7,
    zorder = 2)

# Custom dual-colored Y-axis label for ax1
trans = transforms.blended_transform_factory(fig.transFigure, ax1.transAxes)
fig.text(0.02,
         0.7,
         'Efficiency [pp/mJ]',
         color = "black",
         fontsize = font_size,
         rotation = 'vertical',
         ha = 'center',
         va = 'center',
         transform = trans)
fig.text(0.02,
         0.3,
         'Energy/Frame [mJ]',
         color = "tab:red",
         fontsize = font_size,
         rotation = 'vertical',
         ha = 'center',
         va = 'center',
         transform = trans)

ax1.set_ylabel(' ', fontsize = font_size)
ax1.tick_params(axis = 'y', labelsize = font_size)

# Plot mAP@50 as scatter + trendline (on secondary axis)
ax2 = ax1.twinx()
color1 = 'tab:blue'
marker1 = ax2.scatter(image_sizes_numeric,
                      mAP50,
                      color = color1,
                      marker = 'o',
                      s = marker_size,
                      label = r'$\mathrm{mAP}_{50}$',
                      zorder = 3)

# def fit_func(x, a, b, c):
#     return a * x * x + b * x + c

# popt, pcov = curve_fit(fit_func, image_sizes_numeric, np.array(mAP50)/10)
# x_fit = np.linspace(min(image_sizes_numeric), max(image_sizes_numeric), 100)
# marker1_fit = ax1.plot(
#     x_fit,
#     fit_func(x_fit, *popt),
#     label=r'$\mathrm{mAP}_{50}$ Fit',
#     color=color1,
#     linestyle=':',
#     linewidth=2,
#     alpha=0.7,
#     zorder=2
# )

poly_coeffs_mAP = np.polyfit(image_sizes_numeric, mAP50, 2)
poly_mAP = np.poly1d(poly_coeffs_mAP)
marker1_fit = ax2.plot(
    x_fit,
    poly_mAP(x_fit),
    # label=r'$\mathrm{mAP}_{50}$ Fit',
    label = 'Poly. Fit (2nd order)',
    color = color1,
    linestyle = ':',
    linewidth = 2,
    alpha = 0.7,
    zorder = 2)
ax2.set_ylabel(r'$\mathrm{mAP}_{50}$ [%]', color = color1, fontsize = font_size)
ax2.tick_params(axis = 'y', labelcolor = color1, labelsize = font_size)

# Y-axis limits
ymin = 0
ymax = 25
ax1.set_ylim(ymin, ymax)
ax2.set_ylim(0, 100)

from matplotlib.ticker import AutoMinorLocator

ax1.set_axisbelow(True)
ax1.yaxis.set_minor_locator(AutoMinorLocator())
ax2.yaxis.set_minor_locator(AutoMinorLocator())
ax1.grid(True, which = 'major', linestyle = '-', linewidth = 0.5, alpha = 1)
ax1.grid(which = 'minor', linestyle = '--', linewidth = 0.5, alpha = 0.7)

# Legend
handles = [marker2, marker2_fit[0], bars, marker1, marker1_fit[0]]
labels = [h.get_label() for h in handles]
# ax1.legend(handles, labels, loc='upper center', bbox_to_anchor=(0.5, -0.1), ncol=3, fontsize=font_size)
ax1.legend(handles, labels, loc = 'upper left', ncol = 2, fontsize = font_size)

fig.tight_layout()

script_folder = get_script_folder()

# Save figure
fig.savefig(f'{script_folder}/plot_results.png', dpi = 300, bbox_inches = 'tight')
fig.savefig(f'{script_folder}/plot_results.pdf', dpi = 300, bbox_inches = 'tight')

plt.show()
