import keras
from keras.models import load_model
from keras.applications.inception_v3 import preprocess_input
from keras.preprocessing import image
import numpy as np
from keras.preprocessing.image import ImageDataGenerator, array_to_img, img_to_array, load_img

model = load_model('model.hdf5')

datagen = ImageDataGenerator(rescale=1./255)

img = load_img('cache.png')  # this is a PIL image
x = img_to_array(img)  # this is a Numpy array with shape (3, 150, 150)
x = x.reshape((1,) + x.shape)

zzz = datagen.flow(x, batch_size=1)
preds = model.predict_generator(zzz, 1)
maxindex = preds.argmax()
print('Predicted:', maxindex, preds.shape)
