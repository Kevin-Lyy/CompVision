import cv2
import numpy as np
import imutils
import PIL
from PIL import Image
import matplotlib.pyplot as plt
from PIL import ImageColor
from colormath.color_objects import sRGBColor, LabColor
from colormath.color_conversions import convert_color
from colormath.color_diff import delta_e_cie2000


Lego_colors = []
def LegoDatabase():
    legos_colors = open('LegoColors.txt','r')
    colors = legos_colors.readlines()
    for color in colors:
        color = "#" + color.strip()
        color = ImageColor.getcolor(color,"RGB")
        Lego_colors.append(color)

def convertToPixels(image,size):
    img = Image.open("threshold.jpg")
    pixelated = img.resize(size,Image.BILINEAR)
    sizeUp = pixelated.resize(img.size,Image.NEAREST)
    sizeUp.save("mosaic.jpg")

def findDeltaE(color):
    lab_color_1 = convert_color(color,LabColor)
    if(color[0] == 0 and color[1] == 0 and color[2] == 0):
        return color
    delta_e_list = []
    for stdcolor in Lego_colors:
        lab_color_2 = convert_color(stdcolor,LabColor)
        delta_e = delta_e_cie2000(lab_color_1, lab_color_2)
        delta_e_list.append(delta_e)
    min_delta = min(delta_e_list)
    return Lego_colors[delta_e_list.index(min_delta)]


def reColorLego():
    img = Image.open("mosaic.jpg")
    img = img.convert("RGB")
    colors = img.getdata()
    new_image = []
    for pixel in colors:
        new_color = findDeltaE(pixel)
        #new_image.append(new_color) # insert new colors here
            
    img.putdata(new_image)
    img.save("reColor.jpg")

            

LegoDatabase()

convertToPixels(image="threshold.jpg",size=(70,70))

reColorLego()

