import argparse # Parse command-line arguments
import torch
from torchvision import datasets, transforms
from pytorch_metric_learning import losses

# Layers
#   conv(7,7)
#   tanh
#   pool(2,2)
#   conv(6,6)
#   tanh()
#   fc(128)
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
        super(ShallowCnn, self).__init__()
        self.conv1 = torch.nn.Conv2d(1, 30, 7, 1)
        self.conv2 = torch.nn.Conv2d(30, 100, 6, 1)
        self.pool1 = torch.nn.functional.max_pool2d
        self.fc1   = torch.nn.Linear(3600,128) # [28-6] -> [22/2] -> [11-5] -> [6*6*100]
        self.margin = 0.5
        self.tanh = torch.nn.Tanh()
        self.optim = self.optim = torch.optim.SGD(
            self.parameters(),
            lr=0.1,
            momentum=0.9,
            weight_decay=1e-5
        )

    def forward(self, x):
        x = self.conv1(x)
        x = self.tanh(x)
        x = torch.nn.functional.max_pool2d(x, kernel_size=2)
        x = self.conv2(x)
        x = self.tanh(x)
        x = torch.flatten(x,1)
        output = self.fc1(x) # output is 128-dimensional embedding

        return output

    def Train(self, trainLoader, device, epoch):
        self.train() # switch to train mode
        total = 0
        criterion = losses.TripletMarginLoss(margin=self.margin)
        for data, target in trainLoader:
            self.optim.zero_grad() # Reset gradients
            data = data.to(device) # Move samples to device
            target = target.to(device) # Move labels to device
            output = self(data)
            loss = criterion(output, target) # Calculate loss
            loss.backward() # Backward pass?
            total += loss.item()
            self.optim.step() # What does that do?

        meanLoss = total / len(trainLoader)
        print('Train Epoch: {} \tAverage loss: {:.6f}'.format(epoch, meanLoss))

    def Test(self, testLoader, device):
        self.eval()

        embeddings = []
        labels = []

        with torch.no_grad():
            for data, target in testLoader:
                data = data.to(device)

                embedding = self(data) # [batch_size, 128]

                embeddings.append(embedding.cpu())
                labels.append(target)

        embeddings = torch.cat(embeddings, dim=0)
        labels = torch.cat(labels, dim=0)

        N = embeddings.size(0)

        correct = 0

        for i in range(N):
            queryEmbedding = embeddings[i]

            # Distance from query to all embeddings
            distances = torch.norm(
                embeddings - queryEmbedding,
                dim=1
            )

            # Ignore self-match
            distances[i] = float('inf')

            nearest = torch.argmin(distances)

            predictedLabel = labels[nearest]
            trueLabel = labels[i]

            if predictedLabel == trueLabel:
                correct += 1

        accuracy = 100.0 * correct / N

        print(
            '1-NN Accuracy: {:.2f}% ({}/{})'.format(
                accuracy,
                correct,
                N
            )
        )


def main():
    # Loss threshold
    threshold = 0.01

    # Load train and test sets
    transform=transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
        ])
    dataset1 = datasets.MNIST('../data', train=True, download=True, transform=transform)
    dataset2 = datasets.MNIST('../data', train=False, transform=transform)
    trainLoader = torch.utils.data.DataLoader(dataset1,batch_size=128)
    testLoader = torch.utils.data.DataLoader(dataset2, batch_size=128)

    # Set the device
    device = torch.device('cpu')

    # Set the number of epochs
    epochs = 20

    # Instance of cnn in device
    cnn = ShallowCnn().to(device)

    for i in range(epochs):
        cnn.Train(trainLoader, device, i)

    cnn.Test(testLoader, device)

if __name__ == "__main__":
    main()