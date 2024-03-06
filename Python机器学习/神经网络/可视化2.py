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
    num_examples = 1000  # 要显示的示例数量
    num_per_page = 16  # 每页显示的数字数量
    num_pages = (num_examples - 1) // num_per_page + 1  # 计算总页数
    current_page = 0
    fig, axes = plt.subplots(4, 4, figsize=(10, 10))

    for i, (images, labels) in enumerate(test_loader):
        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

        for j in range(images.shape[0]):
            if current_page * num_per_page + j >= num_examples:
                break
            ax = axes[j // 4, j % 4]
            ax.imshow(images[j].squeeze(), cmap='gray')
            ax.set_title(f'Predicted:{predicted[j]}, Label:{labels[j]}')
            ax.axis('off')

        if (i+1) % (num_per_page // images.shape[0]) == 0:
            plt.tight_layout()
            plt.show()
            current_page += 1
            if current_page >= num_pages:
                break

    print(f'模型在{len(test_dataset)}个测试图像上的准确率：{100 * correct / total}%')