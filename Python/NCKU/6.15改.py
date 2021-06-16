import torch
import torch.nn as nn
import torch.utils.data as Data
import torchvision
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import numpy as np
import pandas as pd
import os

os.environ["KMP_DUPLICATE_LIB_OK"] = "TRUE"
from torch.utils.data import Dataset


class CustomDataset(Dataset):
    def __init__(self, file_path, feature_names):
        self.samples = []

        data = pd.read_excel(file_path)

        for _, row in data.iterrows():
            temp = []
            for r in feature_names:
                temp.append(row[r])
            self.samples.append(torch.FloatTensor(temp))

    def __len__(self):
        return len(self.samples)

    def __getitem__(self, idx):
        return self.samples[idx], 0


# Hyper Parameters
EPOCH = 100
BATCH_SIZE = 50
LR = 0.01  # learning rate
file_path = 'C:\\Users\\user\\Documents\\GitHub\\adaptive_contrrol\\adaptive_control\\Python\\NCKU\\2000rpm_ub0_hsn.xlsx'
feature_names = ['rms_x_b', 'rms_y_b', 'rms_z_b', 'octave_x_b_8', 'octave_y_b_8', 'octave_z_b_8', 'octave_x_b_9',
                 'octave_y_b_9', 'octave_z_b_9', 'octave_x_b_10', 'octave_y_b_10', 'octave_z_b_10']

# Data Loader for easy mini-batch return in training, the image batch shape will be (50, 1, 28, 28)
customdataset = CustomDataset(file_path, feature_names)
train_loader = Data.DataLoader(dataset=customdataset, batch_size=BATCH_SIZE, shuffle=False)

# label
all_df = pd.read_excel(file_path)
cols = ['index']
all_df = all_df[cols]


# print(all_df)
def PreprocessData(raw_df):
    df = raw_df
    x_onehot_df = pd.get_dummies(data=df, columns=['index'])
    ndarray = x_onehot_df.values
    Label = ndarray[:, 0:3]
    return Label


data_Label = PreprocessData(all_df)


class AutoEncoder(nn.Module):
    def __init__(self):
        super(AutoEncoder, self).__init__()
        self.encoder = nn.Sequential(
            nn.Linear(len(feature_names), 128),

            # nn.Conv1d(128, 64, 3, stride=2),
            # nn.MaxPool1d(3, stride=2),
            nn.Tanh(),
            nn.Linear(128, 64),
            nn.Tanh(),
            nn.Linear(64, 12),
            nn.Tanh(),
            nn.Linear(12, 4),  # compress to 3 features which can be visualized in plt
        )

        self.decoder = nn.Sequential(
            nn.Linear(4, 12),
            nn.Tanh(),
            nn.Linear(12, 64),
            nn.Tanh(),
            nn.Linear(64, 128),
            nn.Tanh(),
            nn.Linear(128, len(feature_names)),
        )

    def forward(self, x):
        encoded = self.encoder(x)
        decoded = self.decoder(encoded)
        return encoded, decoded


autoencoder = AutoEncoder()

optimizer = torch.optim.Adam(autoencoder.parameters(), lr=LR)
loss_func = nn.MSELoss()


def list3dto2d(list_3d):
    #print(list_3d)
    points = []
    x = []
    y = []
    z = []
    c = []
    for list_2d in list_3d:
        #print(len(list_2d))
        for point in list_2d:
            #print(list_2d)
            points.append(point)
            x.append(point[0])
            y.append(point[1])
            z.append(point[2])
            c.append(point[3])
    return points, x, y, z, c


# print(train_loader)
for epoch in range(EPOCH):
    point = []
    for step, (x, b_label) in enumerate(train_loader):
        # print(len(x))
        b_x = x  # batch x, shape (batch, 28*28)
        b_y = x  # batch y, shape (batch, 28*28)

        encoded, decoded = autoencoder(b_x)
        print((encoded.size()))
        point.append(encoded.data.numpy().tolist())
        loss = loss_func(decoded, b_y)  # mean square error
        optimizer.zero_grad()  # clear gradients for this training step清除此訓練步驟的梯度
        loss.backward()  # backpropagation, compute gradients反向傳播，計算梯度
        optimizer.step()  # apply gradients應用梯度

        # if step % 100 == 0:
        # print('Epoch: ', epoch, '| train loss: %.4f' % loss.data.numpy())

    points, x, y, z ,c= list3dto2d(point)
    # print(len(point))

# print(loss.shape)
# plot 3D
fig = plt.figure(2)
ax = Axes3D(fig)
ax.scatter(x, y, z, c=c)
# x.scatter(x,y,z)
plt.show()

# # encoded data to excel
# # print(points)
# encoded_excel = pd.DataFrame(points)
# writer = pd.ExcelWriter('C:/Users/KLAB/Desktop/AIcode/2000rpm_ub0_hsn/encoded_2000rpm_ub0_hsn_3D_4.xls', engine='xlwt')
# encoded_excel.to_excel(writer,sheet_name='encoder',index=False)
# writer.save()

# # save model
torch.save(autoencoder,
           'C:\\Users\\user\\Documents\\GitHub\\adaptive_contrrol\\adaptive_control\\Python\\NCKU\\autoencoder_1500rpm_ub012_h_0.pkl')  # save entire net
# torch.save(autoencoder.state_dict(), 'C:/Users/KLAB/Desktop/AIcode/2000rpm_ub0_hsn/autoencoder_2000rpm_ub0_hsn_3D_4_params.pkl')   # save only the parameters