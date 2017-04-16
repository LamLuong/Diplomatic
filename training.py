from keras.utils.np_utils import to_categorical
from keras.applications.inception_v3 import InceptionV3
from keras.applications.inception_v3 import preprocess_input, decode_predictions
from keras.preprocessing import image
from keras.layers import Input
from keras.preprocessing.image import ImageDataGenerator
from keras.models import Sequential, Model
from keras.layers import Dense, Dropout, Activation, Flatten
from keras.layers import Convolution2D, MaxPooling2D, ZeroPadding2D, GlobalAveragePooling2D, AveragePooling2D
from keras.layers.normalization import BatchNormalization
from keras.preprocessing.image import ImageDataGenerator
from keras.callbacks import ModelCheckpoint, TensorBoard, CSVLogger, History, EarlyStopping
import keras.backend as K
from keras.optimizers import SGD, RMSprop, Adam

import matplotlib.pyplot as plt

import os
from os import listdir
from os.path import isfile, join
import numpy as np
import h5py
batch_size = 32

nb_train_samples = 70700
nb_validation_samples = 10100
nb_test_samples = 20200
nb_epoch = 60

train_data_dir = "data/train"
validation_data_dir = "data/valid"

print("Setting up ImageDataGenerator")

print("Setting up ImageDataGenerator")
datagen = ImageDataGenerator(
    featurewise_center=False,  # set input mean to 0 over the dataset
    samplewise_center=False,  # set each sample mean to 0
    featurewise_std_normalization=False,  # divide inputs by std of the dataset
    samplewise_std_normalization=False,  # divide each input by its std
    zca_whitening=False,  # apply ZCA whitening
    rotation_range=45,  # randomly rotate images in the range (degrees, 0 to 180)
    width_shift_range=0.125,  # randomly shift images horizontally (fraction of total width)
    height_shift_range=0.125,  # randomly shift images vertically (fraction of total height)
    horizontal_flip=True,  # randomly flip images
    vertical_flip=False, # randomly flip images
    rescale=1./255,
    fill_mode='nearest')
	
train_generator = datagen.flow_from_directory(
    train_data_dir,
    target_size=(299, 299),
    batch_size=batch_size,
    class_mode='categorical')

validation_generator = datagen.flow_from_directory(
    validation_data_dir,
    target_size=(299, 299),
    batch_size=batch_size,
    class_mode='categorical')


K.clear_session()
print("create model")

base_model = InceptionV3(weights="imagenet", include_top=False, input_tensor=Input(shape=(299, 299, 3)))
x = base_model.output
x = GlobalAveragePooling2D()(x)
# # x = Flatten()(x)
x = Dense(4096)(x)
x = BatchNormalization()(x)
x = Activation('relu')(x)
x = Dropout(.5)(x)
predictions = Dense(101, activation='softmax')(x)

model = Model(inputs=base_model.input, outputs=predictions)

#base_model = VGG16(weights='imagenet', include_top=False, input_shape=(224, 224, 3), input_tensor=Input(shape=(224, 224, 3)))
#print("done")
#x = base_model.output
#x = Flatten(input_shape=base_model.output_shape[1:])(x)
#x = Dense(4096)(x)
#x = Activation('relu')(x)
#x = Dropout(.5)(x)
#predictions = Dense(101, activation='softmax')(x)

#model = Model(inputs=base_model.input, outputs=predictions)
#print (base_model.output_shape[1:])
#top_model = Sequential()
#top_model.add(Flatten(input_shape=base_model.output_shape[1:]))
#top_model.add(Dense(4096, activation='relu'))
#top_model.add(Dropout(0.5))
#top_model.add(Dense(101, activation='sigmoid'))

#model.add(top_model)

for layer in base_model.layers:
    layer.trainable = False

model.compile(optimizer='rmsprop', loss='categorical_crossentropy',
              metrics=['accuracy'])

print("First pass")
checkpointer = ModelCheckpoint(filepath='first.3.{epoch:02d}-{val_loss:.2f}.hdf5', verbose=1, save_best_only=True)
csv_logger = CSVLogger('first.3.log')

model.fit_generator(train_generator,
                    validation_data=validation_generator,
                    validation_steps=(nb_validation_samples / batch_size),
                    steps_per_epoch=(nb_train_samples / batch_size),
                    epochs=7,
					callbacks=[csv_logger, checkpointer],
                    verbose=1)
					
for layer in model.layers[:172]:
    layer.trainable = False
for layer in model.layers[172:]:
    layer.trainable = True

print("Second pass")

history = History()
model.compile(optimizer=SGD(lr=0.0001, momentum=0.9), loss='categorical_crossentropy', metrics=['accuracy'])
checkpointer = ModelCheckpoint(filepath='second.3.{epoch:02d}-{val_loss:.2f}.hdf5', verbose=1, save_best_only=True)
csv_logger = CSVLogger('second.3.log')
early_stoping = EarlyStopping(monitor='val_loss', patience=5, min_delta=0.001, verbose=0)

model.fit_generator(train_generator,
                    validation_data=validation_generator,
                    validation_steps=(nb_validation_samples / batch_size),
                    steps_per_epoch=(nb_train_samples / batch_size),
                    epochs=nb_epoch,
                    verbose=1,
                    callbacks=[csv_logger, checkpointer, history, early_stoping])

					
plt.plot(history.epoch, history.history['acc'], color="red")
plt.plot(history.epoch, history.history['loss'], color="green")
plt.plot(history.epoch, history.history['val_acc'], color="blue")
plt.plot(history.epoch, history.history['val_loss'], color="black")

plt.ylabel('loss')
plt.xlabel('epoch')
plt.show()
