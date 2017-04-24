import keras
from keras.models import load_model
from keras.applications.inception_v3 import preprocess_input
from keras.preprocessing import image
import numpy as np
from keras.preprocessing.image import ImageDataGenerator, array_to_img, img_to_array, load_img

import cv2

target_size = (299, 299)

print("Loading metadata...")
class_to_ix = {}
ix_to_class = {}

#model = None

with open('../model/classes.txt', 'r') as txt:
    classes = [l.strip() for l in txt.readlines()]
    class_to_ix = dict(zip(classes, range(len(classes))))
    ix_to_class = dict(zip(range(len(classes)), classes))
    class_to_ix = {v: k for k, v in ix_to_class.items()}

print ("Loading model")
model = load_model('../model/model.hdf5')
print ("Loaded model")

def PredicImage(image_path, list_object_pos):
  list_lable = []
  num_object = 5
  pos_index = 4

  datagen = ImageDataGenerator(rescale=1./255)

  origin_img_data = cv2.imread(image_path)
  origin_img_data_convert_color = cv2.cvtColor(origin_img_data, cv2.COLOR_BGR2RGB)

  for object_idx in range (0, num_object):
    _object = origin_img_data_convert_color[list_object_pos[object_idx][1]:list_object_pos[object_idx][3],
                                            list_object_pos[object_idx][0]:list_object_pos[object_idx][2]]
    _object = cv2.resize(_object, (299, 299))
    object_to_array = img_to_array(_object)
    object_to_array = object_to_array.reshape((1,) + object_to_array.shape)

    input_predict = datagen.flow(object_to_array, batch_size=1)

    preds = model.predict_generator(input_predict, 1)
    maxindex = preds.argmax()
    list_lable.append(ix_to_class[maxindex])
  return list_lable

