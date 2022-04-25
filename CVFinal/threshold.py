# organizing imports
import cv2
import numpy as np
 
image1 = cv2.imread("CompVision/CVFinal/images/291.jpg")
 
 

thresh_val = 70
image1[image1 < thresh_val] = 0

ret, thresh3 = cv2.threshold(image1, 250, 255, cv2.THRESH_TRUNC)

 
cv2.imshow('Truncated Threshold', thresh3)

   
# De-allocate any associated memory usage 
if cv2.waitKey(0) & 0xff == 27:
    cv2.destroyAllWindows()