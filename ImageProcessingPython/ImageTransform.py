
# coding: utf-8

# In[92]:

import numpy as np
from PIL import Image


# In[104]:

IMAGE_LOC = "Stars.png"
BRUSH_SIZE = 10


# In[105]:

def readPicture(picture):
    img = Image.open(picture)
    pix = img.load()
    return img, pix


# In[106]:

def colorMaps(size,pixels):
    red = Image.new("RGB",(size),255)
    green = Image.new("RGB",(size))
    blue = Image.new("RGB",(size))
    rp = red.load()
    gp = green.load()
    bp = blue.load()
    
    for i in range(size[0]):
        for j in range(size[1]):
            if (pixels[i,j][0] > 127):
                rp[i,j] = (255,0,0)
            else:
                rp[i,j] = (0,0,0)
            if (pixels[i,j][1] > 127):
                gp[i,j] = (0,255,0)
            else:
                gp[i,j] = (0,0,0)
            if (pixels[i,j][2] > 127):
                bp[i,j] = (0,0,255)
            else:
                bp[i,j] = (0,0,0)
            
    return red, green, blue


# In[107]:

def Left_Bias_Elaborate(cMap,bSize,color_index):
    color = (0,0,0);
    options = { 0: (255,0,0), 1: (0,255,0), 2: (0,0,255)}
    color = options[color_index]
    sum_brush = 0;
    pixels = cMap.load()
    for i in range(0,cMap.size[0] - bSize + 1,bSize):
        for j in range(0,cMap.size[1] - bSize + 1,bSize):
            for k in range(0,bSize):
                for l in range(0,bSize):
                    sum_brush = sum_brush + pixels[i + k, j + l][color_index]
            if(sum_brush > (255 * bSize * bSize)/2):
                for k in range(0,bSize):
                    for l in range(0,bSize):
                        pixels[i + k, j + l ] = color 
            else:
                for k in range(0,bSize):
                    for l in range(0,bSize):
                        pixels[i + k, j + l ] = (0,0,0);
            sum_brush = 0
    
    return


# In[108]:

def colorImpose(red,green,blue,size):
    white = Image.new("RGB",size,255)
    pix_white = white.load()
    pix_red = red.load()
    pix_green = green.load()
    pix_blue = blue.load()
    for i in range(size[0]):
        for j in range(size[1]):
            pix_white[i,j] = (pix_red[i,j][0],pix_green[i,j][1],pix_blue[i,j][2])
    return white
    
    
    


# In[110]:

image, pixels = readPicture(IMAGE_LOC)
red, green, blue = colorMaps(image.size,pixels)
Left_Bias_Elaborate(red,BRUSH_SIZE,0)
Left_Bias_Elaborate(green,BRUSH_SIZE,1)
Left_Bias_Elaborate(blue,BRUSH_SIZE,2)
#print(pixels[0,0])
red.show()
green.show()
blue.show()
newImage = colorImpose(red,green,blue,image.size)
newImage.show()
image.show()


# In[ ]:




# In[ ]:



