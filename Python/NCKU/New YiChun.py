# -*- coding: utf-8 -*-
"""
Created on Fri Nov 22 14:04:44 2019

rebuild YC's ANN model
"""

"""
parameters
"""
num_class=3
epo = 50

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

"""
data process from file
"""
import numpy as np
import pandas as pd
filepath="4parameters.xlsx"
all_df=pd.read_excel(filepath)
all_df[:3]
cols=['worn','rpm','cutting depth','platform RMS','current mean','microphone RMS','platform rsf2','AE ROP 50k-100k','AE ROP 100k-150k']
all_df=all_df[cols]
all_df['worn']=all_df['worn']/5
all_df['rpm']=all_df['rpm']/10000
all_df[:3]
msk=np.random.rand(len(all_df))<0.7
train_df=all_df[msk] #70% data train
test_df=all_df[~msk] #30% data test
print('total:',len(all_df),'train:',len(train_df),'test:',len(test_df))
"""
preprocess data function
"""
def PreprocessData(raw_df):
    df=raw_df
    x_onehot_df=pd.get_dummies(data=df,columns=['worn'])
    ndarray=x_onehot_df.values
    Features=ndarray[:,0:8]
    Label=ndarray[:,8:11]
    return Features, Label
"""
preprocessing train and test data
"""
train_Features,train_Label=PreprocessData(train_df)
test_Features,test_Label=PreprocessData(test_df)

"""
model establishment
"""
from keras.models import Sequential
from keras.layers import Dense,Dropout
model = Sequential()
L=len(train_Features[0])
model.add(Dense(units = 100,input_shape = (L, ),kernel_initializer = 'uniform',activation = 'relu'))
#model.add(Dropout(0.2))
model.add(Dense(units = 100,kernel_initializer = 'uniform',activation = 'sigmoid'))
#model.add(Dropout(0.2))
model.add(Dense(units = num_class,kernel_initializer = 'uniform',activation ='softmax'))
print(model.summary())

"""
model compile and train
"""
model.compile(loss = 'categorical_crossentropy',optimizer = 'adam',metrics = ['accuracy'])
train_history = model.fit(x = train_Features,y = train_Label,validation_split = 0.1,shuffle=True,epochs = epo,batch_size = 1,verbose = 2)

"""
plot function
"""
import matplotlib.pyplot as plt
def show_train_history(train_history,train,validation):
    
    plt.plot(train_history.history[train])
    plt.axis([0, epo, 0, 1.1])
    plt.title('Train History')
    plt.ylabel('Accuracy')
    plt.xlabel('Epoch')
    plt.legend(['train'], loc='lower right')
    plt.show()
    show_train_history(train_history,'acc','val_acc')
scores=model.evaluate(x=test_Features,y=test_Label)
scores[1]

prediction=np.argmax(model.predict(test_Features), axis=-1)
prediction.shape
test_df['worn'].shape
show_train_history(train_history,train,validation)
"""
confusion matrix
pd.crosstab(test_df['worn'],prediction,rownames=['label'],colnames=['predict'])
pd=test_df
pd.insert(len(test_df.columns),'status prediction',prediction)
pd[pd['worn']!=pd['status prediction']]
"""