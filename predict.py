import keras
from keras.models import load_model
from keras.applications.inception_v3 import preprocess_input
from keras.preprocessing import image
import numpy as np
from keras.preprocessing.image import ImageDataGenerator, array_to_img, img_to_array, load_img

import sys
image_name = str(sys.argv[1])

target_size = (299, 299)

print("Loading metadata...")
class_to_ix = {}
ix_to_class = {}
with open('classes.txt', 'r') as txt:
    classes = [l.strip() for l in txt.readlines()]
    class_to_ix = dict(zip(classes, range(len(classes))))
    ix_to_class = dict(zip(range(len(classes)), classes))
    class_to_ix = {v: k for k, v in ix_to_class.items()}


print("loading Model .......")
model = load_model('model.hdf5')
print("Model 's loaded")

datagen = ImageDataGenerator(rescale=1./255)

img = load_img(image_name, target_size=target_size)

x = img_to_array(img)
x = x.reshape((1,) + x.shape)

input_image = datagen.flow(x, batch_size=1)

preds = model.predict_generator(input_image, 1)
maxindex = preds.argmax()

print('Predicted:', ix_to_class[maxindex])
