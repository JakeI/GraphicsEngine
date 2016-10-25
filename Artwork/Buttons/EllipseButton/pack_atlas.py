# inclompleat work

import numpy as np
import scipy.misc as misc
import matplotlib.pyplot as plt

import os

class Image:
    img
    name
    width
    hight

    def _set_name_form_filepath(self, path):
        path = path.replace('\\', '/')
        path = path.split('/')
        self.name = path[-1]

    def __init__(self, file):
        self._set_name_form_filepath(file)
        img = misc.imread(file)
        s = img.shape
        width = s[0]
        hight = s[1]


input_file_list = []
for (dirpath, dirnames, filenames) in os.walk(os.getcwd()):
    input_file_list = [f for f in filenames if f.endswith(".png")]
    break

print("Input files: %s" % input_file_list)

input_images = [Image(f) for f in input_file_list]

def compare(item1, item2):
    if fitness(item1) < fitness(item2):
        return -1
    elif fitness(item1) > fitness(item2):
        return 1
    else:
        return 0
