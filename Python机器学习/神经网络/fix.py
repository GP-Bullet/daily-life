import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
from sklearn.datasets import load_iris

# 加载数据集
iris = load_iris()
x = iris.data

y = iris.target

# 转换数据为张量
x_tensor = torch.tensor(x, dtype=torch.float32)
y_tensor = torch.tensor(y, dtype=torch.int64)

# 创建数据集对象
dataset = torch.utils.data.TensorDataset(x_tensor, y_tensor)

# 创建数据加载器
iris_loader = DataLoader(dataset, batch_size=32, shuffle=True)

# 定义模型
class IrisClassifier(nn.Module):
    def __init__(self):
        super(IrisClassifier, self).__init__()
        self.fc1 = nn.Linear(4, 16)
        self.fc2 = nn.Linear(16, 8)
        self.fc3 = nn.Linear(8, 3)

    def forward(self, x):
        x = nn.functional.relu(self.fc1(x))
        x = nn.functional.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# 定义模型和优化器
model = IrisClassifier()
optimizer = optim.Adam(model.parameters(), lr=0.01)

# 训练模型
for epoch in range(10):
    for x, y in iris_loader:
        optimizer.zero_grad()
        y_pred = model(x)
        loss = nn.functional.cross_entropy(y_pred, y)
        loss.backward()
        optimizer.step()
    print(f'Epoch {epoch + 1}, loss: {loss.item():.4f}')

# 在测试数据上评估模型
x_test = torch.tensor(iris.data, dtype=torch.float32)
y_test = torch.tensor(iris.target, dtype=torch.int64)

test_dataset = torch.utils.data.TensorDataset(x_test, y_test)
test_loader = DataLoader(test_dataset, batch_size=32)

correct = 0
total = 0
with torch.no_grad():
    for x, y in test_loader:
        y_pred = model(x)
        _, predicted = torch.max(y_pred.data, 1)
        total += y.size(0)
        correct += (predicted == y).sum().item()

accuracy = 100 * correct / total
print(f'Test accuracy: {accuracy:.2f}%')