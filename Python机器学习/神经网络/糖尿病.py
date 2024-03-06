import torch
import torch.nn as nn
import torch.optim as optim
from sklearn.datasets import load_diabetes
from sklearn.model_selection import train_test_split
from torch.utils.data import DataLoader, TensorDataset

# 加载糖尿病数据集
diabetes = load_diabetes()

# 分割数据集为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(diabetes.data, diabetes.target, test_size=0.2, random_state=42)

# 转换数据为张量
X_train = torch.tensor(X_train, dtype=torch.float32)
X_test = torch.tensor(X_test, dtype=torch.float32)
y_train = torch.tensor(y_train, dtype=torch.float32)
y_test = torch.tensor(y_test, dtype=torch.float32)

# 转换数据为 DataLoader
train_dataset = TensorDataset(X_train, y_train)
test_dataset = TensorDataset(X_test, y_test)

train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=32, shuffle=False)

# 定义神经网络模型
class DiabetesClassifier(nn.Module):
    def __init__(self):
        super(DiabetesClassifier, self).__init__()
        self.fc1 = nn.Linear(10, 16)
        self.fc2 = nn.Linear(16, 8)
        self.fc3 = nn.Linear(8, 1)

    def forward(self, x):
        x = nn.functional.relu(self.fc1(x))
        x = nn.functional.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# 定义模型和优化器
model = DiabetesClassifier()

# 训练模型
for epoch in range(10):
    for x, y in train_loader:
        optimizer.zero_grad()
        y_pred = model(x)
        loss = nn.functional.mse_loss(y_pred, y.view(-1, 1))
        loss.backward()
        optimizer.step()
        print(f'Epoch {epoch + 1}, loss: {loss.item():.4f}')

# 在测试数据上评估模型
with torch.no_grad():
    y_pred = model(X_test)
    mse = nn.functional.mse_loss(y_pred, y_test.view(-1, 1))
    print(f'MSE on test data: {mse.item():.4f}')