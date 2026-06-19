import argparse # Parse command-line arguments
import torch # PyTorch library for tensor computations
from torchvision import datasets, transforms # Datasets and transformations for computer vision

class ShallowCnn(torch.nn.Module):
    def __init__(self):
        super.__init__(ShallowCnn, self)
        self.conv1 = torch.nn.conv2d(1, 50, 7, 1)
        self.conv2 = torch.nn.conv2d(50, 100, 6, 1)
        self.pool1 = torch.nn.functional.max_pool2d
        self.fc1   = torch.nn.Linear(8100, 128) # [28-6] -> [22-5] -> [17+1] -> [18/2] -> [9*9*100]
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