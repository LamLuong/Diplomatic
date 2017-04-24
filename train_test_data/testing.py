from keras.models import load_model
from keras.preprocessing.image import ImageDataGenerator
from keras.optimizers import SGD, RMSprop, Adam
import numpy as np

test_data_dir = 'data/test'
batch_size = 32
nb_test_samples = 20200

model = load_model('model.hdf5')

datagen = ImageDataGenerator(rescale=1./255)

test_generator = datagen.flow_from_directory(
                                      test_data_dir,
                                      target_size=(299, 299),
                                      batch_size=batch_size,
                                      class_mode='categorical')

model.compile(optimizer=SGD(lr=0.0001, momentum=0.9),
              loss='categorical_crossentropy',
              metrics=['accuracy'])

scores = model.evaluate_generator(test_generator,
                         steps=(nb_test_samples/batch_size))
print("\n%s: %.2f%%" % (model.metrics_names[1], scores[1]*100))from keras.models import load_model
from keras.preprocessing.image import ImageDataGenerator
from keras.optimizers import SGD, RMSprop, Adam
import numpy as np

test_data_dir = 'data/test'
batch_size = 32
nb_test_samples = 20200

model = load_model('model.hdf5')

datagen = ImageDataGenerator(rescale=1./255)

test_generator = datagen.flow_from_directory(
                                      test_data_dir,
                                      target_size=(299, 299),
                                      batch_size=batch_size,
                                      class_mode='categorical')

model.compile(optimizer=SGD(lr=0.0001, momentum=0.9),
              loss='categorical_crossentropy',
              metrics=['accuracy'])

scores = model.evaluate_generator(test_generator,
                         steps=(nb_test_samples/batch_size))
print("\n%s: %.2f%%" % (model.metrics_names[1], scores[1]*100))
