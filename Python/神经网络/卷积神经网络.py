import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
from keras.optimizers import SGD,Adam
from keras.utils import to_categorical
from sklearn.metrics import confusion_matrix, classification_report, roc_auc_score
from sklearn.metrics import precision_score

# 数据读取与预处理
(X_train, y_train), (X_test, y_test) = mnist.load_data()

# 可视化数据集中的手写字体样本
fig, axes = plt.subplots(2, 5, figsize=(10, 4))
for i, ax in enumerate(axes.flat):
    ax.imshow(X_train[i], cmap='gray')
    ax.axis('off')
    ax.set_title(f"Label: {y_train[i]}")
plt.show()

# 数据预处理
X_train = X_train.reshape(-1, 28, 28, 1) / 255.0
X_test = X_test.reshape(-1, 28, 28, 1) / 255.0
y_train = to_categorical(y_train)
y_test = to_categorical(y_test)

# 模型构建
model = Sequential()
model.add(Conv2D(32, (3, 3), activation='sigmoid', input_shape=(28, 28, 1)))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Conv2D(64, (3, 3), activation='sigmoid'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Flatten())
model.add(Dense(128, activation='sigmoid'))
model.add(Dense(10, activation='softmax'))

# 定义优化器，学习率和损失函数
optimizer = Adam(lr=10)
model.compile(optimizer=optimizer, loss='categorical_crossentropy', metrics=['accuracy'])

# 训练模型
epochs = 10
batch_size = 32
history = model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, validation_data=(X_test, y_test))

# 可视化训练过程中的准确率和损失值
plt.figure(figsize=(12, 4))
plt.subplot(1, 2, 1)
plt.plot(history.history['accuracy'], label='Training Accuracy')
plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(history.history['loss'], label='Training Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.legend()
plt.show()

# 测试模型
test_loss, test_accuracy = model.evaluate(X_test, y_test, verbose=0)
print(f"Test Loss: {test_loss:.4f}")
print(f"Test Accuracy: {test_accuracy:.4f}")

# 预测测试集
y_pred = model.predict(X_test)
y_pred = np.argmax(y_pred, axis=1)  # 将概率转换为类别标签

# 计算混淆矩阵
cm = confusion_matrix(np.argmax(y_test, axis=1), y_pred)
print("Confusion Matrix:")
print(cm)

# 计算分类报告
report = classification_report(np.argmax(y_test, axis=1), y_pred)
print("Classification Report:")
print(report)

# 计算查全率（Recall）
recall = cm[1, 1] / (cm[1, 0] + cm[1, 1])
print(f"Recall: {recall:.4f}")

# 计算AUC
y_pred_prob = model.predict(X_test)
auc = roc_auc_score(y_test, y_pred_prob, multi_class='ovr')
print(f"AUC: {auc:.4f}")

# 计算查准率
precision = precision_score(np.argmax(y_test, axis=1), y_pred, average='macro')
print(f"Precision: {precision:.4f}")