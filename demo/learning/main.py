import argparse # Parse command-line arguments
import torch # PyTorch library for tensor computations
from torchvision import datasets, transforms # Datasets and transformations for computer vision

# Layers
#   conv(7,7)
#   tanh
#   pool(2,2)
#   conv(6,6)
#   tanh()
#   fc(128)
#   fc(10) +
#
# Parameters
#   batch: 128
#   learning rate: 0.1
#   momentum: 0.9
#   weight decay: 1e-5
#   kernels: 100
#   optimizer: sgd

class ShallowCnn(torch.nn.Module):
    def __init__(self):
        super.__init__(ShallowCnn, self)
        self.conv1 = torch.nn.conv2d(1, 50, 7, 1)
        self.conv2 = torch.nn.conv2d(50, 100, 6, 1)
        self.pool1 = torch.nn.functional.max_pool2d
        self.fc1   = torch.nn.Linear(3600, 128) # [28-6] -> [22/2] -> [11-5] -> [6*6*100]
        self.fc2   = torch.nn.Linear(128, 10)
        self.optim = torch.optim.sgd.SGD(self.parameters(), lr=0.1, momentum=0.9, weight_decay=1e-5)

    def Forward(self, x):
        x = torch.nn.conv2d(1, 50, 7, 1)

    def Train(self):
        print('dummy')

def main():
    cnn = ShallowCnn()

    threshold = 0.01 # Loss threshold

    for i in range(50):
        print('dummy')

if __name__ == __main__:
    main()