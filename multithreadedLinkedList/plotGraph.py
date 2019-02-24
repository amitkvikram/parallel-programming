import numpy as np
import matplotlib.pyplot as plt

threadCount = [1, 2, 4, 8, 16, 20]
timeTaken = []

for t in threadCount:
    tempTime = []
    for j in range(5):
        x = float(input())
        tempTime.append(x)
#         x = int(input())
        # print(x)
        
    x_mean = np.mean(tempTime)
    timeTaken.append(x_mean)
    print(x_mean)

# print(t)
# print(timeTaken)
plt.plot(threadCount, timeTaken, 'r--', marker = 'o')
plt.show()
# print("hii")
