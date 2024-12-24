import csv

import sys

if len(sys.argv) > 1:
    trials = int(sys.argv[1])
else:
    trials = 0

# Load data from calc.xlsx
data = []

file_name = "trials.txt"
with open(file_name, "r") as file:
    line = file.read()
value = line.strip()
cellAd = "trials"
data.append([cellAd, value])

for i in range(16):
    file_name = f"f_ch{i}.txt"
    with open(file_name, "r") as file:
        line = file.read()
    value = line.strip()
    cellAd = f"f_ch{i}"
    data.append([cellAd, value])

for i in range(8):
    file_name = f"r_ch{i}.txt"
    with open(file_name, "r") as file:
        line = file.read()
    value = line.strip()
    cellAd = f"r_ch{i}"
    data.append([cellAd, value])

file_name = "all.txt"
with open(file_name, "r") as file:
    line = file.read()
value = line.strip()
cellAd = f"all"
data.append([cellAd, value])

# Write data to a CSV file
with open(f"count{trials}.csv", "w", newline="") as csvfile:
    csv_writer = csv.writer(csvfile)
    csv_writer.writerow(["Cell Address", "Value"])  # Writing header
    csv_writer.writerows(data)
