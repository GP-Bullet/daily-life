import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
import collections as co

# 计算两点之间的欧式距离
def exp(i, j):
    return np.sqrt(np.sum(abs(i - j) ** 2))

def knn(k, predictpoint, x_train, y_train):
    dist = []
    for train_data in x_train:
        distance = exp(predictpoint, train_data)
        dist.append(distance)
    sortindex = np.argsort(dist)
    sortlabel = y_train[sortindex]
    return co.Counter(sortlabel[0:k]).most_common(1)[0][0]

if __name__ == '__main__':
    iris = load_iris()
    iris_feature = iris.data
    iris_label = iris.target

    k_values = range(1, 11)  # 设置不同的K值范围

    for k in k_values:
        accuracies = []
        for _ in range(10):  # 进行10次重复实验
            x_train, x_test, y_train, y_test = train_test_split(iris_feature, iris_label, test_size=0.3, random_state=30)

            count = 0
            predict = []
            for predictpoint in x_test:
                result = knn(k, predictpoint, x_train, y_train)
                predict.append(result)
            predict = np.array(predict)

            accuracy = np.sum((predict == y_test) / y_test.size)
            accuracies.append(accuracy)

        average_accuracy = np.mean(accuracies)
        std_deviation = np.std(accuracies)

        print(f"K = {k}:")
        print(f"Predictions: {predict}")
        print(f"True Labels: {y_test}")
        print(f"Accuracy: {average_accuracy:.4f} ± {std_deviation:.4f}\n")