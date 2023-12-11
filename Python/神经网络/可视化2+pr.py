import numpy as np
from sklearn.metrics import precision_recall_curve
from sklearn.metrics import auc
# 在测试数据上评估模型
import torch
import torch.nn as nn
import torch.optim as optim
from torchvision.datasets import MNIST
from torchvision.transforms import ToTensor
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt

# 加载 MNIST 数据集
train_dataset = MNIST(root='./data', train=True, transform=ToTensor(), download=True)
test_dataset = MNIST(root='./data', train=False, transform=ToTensor(), download=True)

# 创建数据加载器
train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=64, shuffle=False)

# 定义神经网络模型
class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.fc1 = nn.Linear(28*28, 128)
        self.fc2 = nn.Linear(128, 64)
        self.fc3 = nn.Linear(64, 10)

    def forward(self, x):
        x = x.view(-1, 28*28)
        x = nn.functional.relu(self.fc1(x))
        x = nn.functional.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# 定义模型和优化器
model = NeuralNetwork()
optimizer = optim.Adam(model.parameters(), lr=0.01)

# 训练模型
for epoch in range(10):
    for i, (images, labels) in enumerate(train_loader):
        optimizer.zero_grad()
        outputs = model(images)
        loss = nn.functional.cross_entropy(outputs, labels)
        loss.backward()
        optimizer.step()

        if (i+1) % 100 == 0:
            print(f'Epoch [{epoch+1}/{10}], Step [{i+1}/{len(train_loader)}], Loss: {loss.item():.4f}')
# 在测试数据上评估模型
model.eval()
with torch.no_grad():
    correct = 0
    total = 0
    num_examples = 16 # 要显示的示例数量
    fig, axes = plt.subplots(4, 4, figsize=(10, 10))

    for i, (images, labels) in enumerate(test_loader):
        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

        for j in range(images.shape[0]):
            if i * images.shape[0] + j >= num_examples:
                break
            ax = axes[j // 4, j % 4]
            ax.imshow(images[j].squeeze(), cmap='gray')
            ax.set_title(f'Predicted:{predicted[j]}, Label:{labels[j]}')
            ax.axis('off')

    plt.tight_layout()
    plt.show()

    print(f'模型在{len(test_dataset)}个测试图像上的准确率：{100 * correct / total}%')

# PR曲线
# 在测试数据上评估模型
model.eval()
with torch.no_grad():
    probabilities = []
    true_labels = []

    for images, labels in test_loader:
        outputs = model(images)
        probabilities.extend(torch.softmax(outputs, dim=1)[:, 1].tolist())
        true_labels.extend(labels.tolist())

    probabilities = np.array(probabilities)
    true_labels = np.array(true_labels)

    precision, recall, _ = precision_recall_curve(true_labels, probabilities)
    pr_auc = auc(recall, precision)

    # 绘制PR曲线
    plt.figure()
    plt.plot(recall, precision, color='blue', label=f'PR曲线 (AUC = {pr_auc:.2f})')
    plt.xlabel('召回率')
    plt.ylabel('精确率')
    plt.title('精确率-召回率曲线')
    plt.legend(loc='lower left')
    plt.show()

    print(f'模型在{len(test_dataset)}个测试图像上的准确率：{100 * correct / total}%')
    print(f'PR曲线下的面积 (AUC): {pr_auc:.2f}')