import cv2
import numpy as np
import imutils

image1 = cv2.imread("threshold.jpg")
mosaicX = 50
mosaicY = 50

lego1 = cv2.imread("302104.jpg")
def trimage(img, border = 1):
    # https://stackoverflow.com/a/49907762
    # width of border around map, will not exceed what exists

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    coords = cv2.findNonZero(gray) # find map pixels 
    x, y, w, h = cv2.boundingRect(coords) # find minimum spanning bounding box

    # fix border  
    if x - border >= 0:
        x1 = x - border
    else: 
        x1 = 0

    if x + w + border <= img.shape[1]:
        x2 = x + w + border
    else:
        x2 = img.shape[1]

    if y - border >= 0:
        y1 = y - border
    else: 
        y1 = 0

    if y + h + border <= img.shape[0]:
        y2 = y + h + border
    else:
        y2 = img.shape[0]

    return img[y1:y2, x1:x2]

trimage(lego1,1)

cv2.imwrite("clean.jpg", lego1)