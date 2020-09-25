import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

'''
Script to make statistics from the times.csv file.
'''

pd.options.display.max_rows = 99999

df = pd.read_csv('times.csv')

distance_count = df.groupby(['Distance']).count()

# Discards distances that appeared less than 50 times in the dataframe.
counts = df['Distance'].value_counts()
df = df[df['Distance'].isin(counts[counts >= 50].index)]

avg_time_dist = df.groupby('Distance')['Time'].mean()

print('Count of values, grouped by the Distance: ' + str(distance_count))
print('Average time by distance: ' + str(avg_time_dist))

avg_time_dist.plot(label="x = distance, y = time")
plt.title("A* on a 100x100x100 cube: 40% obstacles, random start, random goal" + "\nTotal number of observations: " +  str(len(df)))
plt.xlabel("Distance (units)")
plt.ylabel("Average time (ms)")
plt.savefig("graph.png")
plt.show()
