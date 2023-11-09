import torch
import torch.nn as nn
import torch.optim as optim
#import torchvision.datasets as datasets
from torch.utils.data import DataLoader
import sklearn.datasets as datasets
# 定义数据集转换器
def transform(sample):
    x, y = sample
    return torch.tensor(x, dtype=torch.float32), torch.tensor(y, dtype=torch.int64)


# 加载数据集
iris = datasets.Iris(root='./data', train=True, download=True)
iris_test = datasets.Iris(root='./data', train=False, download=True)

# 转换数据集为 DataLoader
iris_loader = DataLoader(iris, batch_size=32, shuffle=True, collate_fn=transform)
iris_test_loader = DataLoader(iris_test, batch_size=32, shuffle=False, collate_fn=transform)

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
correct = 0
total = 0
with torch.no_grad():
    for x, y in iris_test_loader:
        y_pred = model(x)
        _, predicted = torch.max(y_pred.data, 1)
        total += y.size(0)
        correct += (predicted == y).sum().item()

accuracy = 100 * correct / total
print(f'Test accuracy: {accuracy:.2f}%')