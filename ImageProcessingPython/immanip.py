
# coding: utf-8

# In[2]:

import numpy as np
from PIL import Image


# In[3]:

def readPicture(picture):
    img = Image.open(picture)
    pix = img.load()
    return (img, pix)


# In[8]:

def colorDivide(image):
    red = Image.new("RGB",image[0].size)
    rp = red.load()
    green = Image.new("RGB",image[0].size)
    gp = green.load()
    blue = Image.new("RGB",image[0].size)
    bp = blue.load()
    for i in range(image[0].size[0]):
        for j in range(image[0].size[1]):
            rp[i,j] = (image[1][i,j][0],0,0)
            gp[i,j] = (0,image[1][i,j][1],0)
            bp[i,j] = (0,0,image[1][i,j][2])
    return red, blue, green
            


# In[1]:

def colorFlatten(value,image):
    pixels = image.load()
    for i in range(image.size[0]):
        for j in range(image.size[1]):
            if(pixels[i,j][0] != 0):
                pixels[i,j] = (value,0,0)
            if(pixels[i,j][1] != 0):
                pixels[i,j] = (0,value,0)
            if(pixels[i,j][2] != 0):
                pixels[i,j] = (0,0,value)


# In[ ]:



