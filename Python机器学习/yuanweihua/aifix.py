import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier

if __name__ == '__main__':
    iris = load_iris()
    iris_feature = iris.data
    iris_label = iris.target

    k_values = range(1, 11)  # 设置不同的K值范围
    scaler = StandardScaler()
    iris_feature_scaled = scaler.fit_transform(iris_feature)

    x_train, x_test, y_train, y_test = train_test_split(iris_feature_scaled, iris_label, test_size=0.3, random_state=30)

    for k in k_values:
        knn = KNeighborsClassifier(n_neighbors=k)
        knn.fit(x_train, y_train)
        accuracy = knn.score(x_test, y_test)

        print(f"K = {k}:")
        print(f"Accuracy: {accuracy:.4f}\n")