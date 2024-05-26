import os
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

bin_groups = [
    (-0.55, -0.45),
    (-0.45, -0.35),
    (-0.35, -0.25),
    (-0.25, -0.15),
    (-0.15, -0.05),
    (-0.05, 0.05),
    (0.05, 0.15),
    (0.15, 0.25),
    (0.25, 0.35),
    (0.35, 0.45),
    (0.45, 0.55),
]

group_counts = [0] * len(bin_groups)

# Directory containing the output files is current directory
output_dir = os.getcwd()

# Loop through each output file
for filename in os.listdir(output_dir):
    if filename.endswith(".out"):
        with open(filename, "r") as file:
            for line in file:
                position = float(line.strip())  # Assuming each line contains a single particle position
                for i, (group_start, group_end) in enumerate(bin_groups):
                    if group_start <= position < group_end:
                        group_counts[i] += 1
                        break

for (group_start, group_end), count in zip(bin_groups, group_counts):
    print(f"Group: ({group_start}, {group_end}), Count: {count}")