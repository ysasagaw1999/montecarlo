import csv
import sys
import math
from pathlib import Path

if len(sys.argv) > 1:
    num = int(sys.argv[1])
else:
    print("Error: Specify the number of files to process as an argument.")
    sys.exit(1)

# データを保持するリストを初期化
data = [[0] * num for _ in range(26)]
count = []

# データを加算する
for i in range(num):
    file_name = f'count{i}.csv'
    if not Path(file_name).exists():
        print(f"Error: File {file_name} does not exist.")
        continue
    with open(file_name, 'r', newline='') as f:
        csvreader = csv.reader(f, delimiter=',')
        j = 0
        for row in csvreader:
            if len(row) < 2:  # 行が短い場合を無視
                continue
            elif row[1] != "Value":
                try:
                    value = int(row[1])
                    data[j][i] += value
                    j += 1
                except ValueError:
                    print(f"Warning: Invalid integer '{row[1]}' in {file_name}")

# 結果をresultに保存する
result = [["trials", data[0]]]
for i in range(16):
    j = 1 + i
    result.append([f'f_ch_{i}', data[j]])
for i in range(8):
    j = 17 + i
    result.append([f'r_ch_{i}', data[j]])
result.append(['all', data[25]])  # 全てのデータの合計を追加する

# 各データチャンネルのRMSを計算
for idx, channel_data in enumerate(data):
    channel_ave = sum(channel_data) / num
    channel_ms = sum((x - channel_ave) ** 2 for x in channel_data)
    channel_error = math.sqrt(channel_ms / (num * (num - 1)))
    channel_sa = channel_ave / (2*data[0][0])
    channel_saer = channel_error / (2*data[0][0])
    result[idx].append(channel_ave)
    result[idx].append(channel_error)
    result[idx].append(channel_sa*100)
    result[idx].append(channel_saer*100)

# 結果をresults.csvに書き込む
with open('results.csv', 'w', newline='') as f:
    csvwriter = csv.writer(f)
    csvwriter.writerows(result)
