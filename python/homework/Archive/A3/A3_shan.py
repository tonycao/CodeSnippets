#######################################################################################
## Assignment 3                                                                      ##
## Discussion is allowed.                                                            ##
## Copying or sharing code is prohibited.                                            ##
## By typing your name below, you indicate agreement with the UNC Honor Code Pledge, ##
## that you have not given or received unauthorized assistance on this assignment.   ##
## Name: Liang Shan                                                                  ##
## Collaborators: None                                                               ## 
#######################################################################################

import numpy as np
import pylab

# Some helpers to load and save images
# You won't need to modify these
def load_binary_image(name):
    '''Load a binary image from a file'''
    im = pylab.imread(name)
    if im.ndim == 3:
        result = im[:, :, 0] != 0
    elif im.ndim == 2:
        result = im != 0
    return result

def save_binary_image(name, value):
    '''Save a binary image to a file'''
    pylab.imsave(name, value, cmap=pylab.gray())

# Load the test image we'll use below
test_image = load_binary_image('test.png')

# 1. Scroll images.

# Define your functions to scroll images

def scrollLeft(img, amt):
    '''Return a new image that is the given image scrolled left by amt pixels'''
    new = np.zeros_like(img)
    # Do something to fill in values in new here
    new[:,:-amt] = img[:,amt:]
    return new

# Similarly define the rest of them.

def scrollRight(img, amt):
    '''Return a new image that is the given image scrolled right by amt pixels'''
    new = np.zeros_like(img)
    # Do something to fill in values in new here
    new[:,amt:] = img[:,:-amt]
    return new

def scrollUp(img, amt):
    '''Return a new image that is the given image scrolled up by amt pixels'''
    new = np.zeros_like(img)
    # Do something to fill in values in new here
    new[:-amt,:] = img[amt:,:]
    return new

def scrollDown(img, amt):
    '''Return a new image that is the given image scrolled down by amt pixels'''
    new = np.zeros_like(img)
    # do something to fill in values in new here
    new[amt:,:] = img[:-amt,:]
    return new

# 1A. Scroll the image up by 10 pixels.
up10 = scrollUp(test_image, 10)
# And save that
save_binary_image('1A_shan.png', up10)

# 1B. Now scroll the result of 1A down by 10 pixels.
updown10 = scrollDown(up10, 10)
# And save that
save_binary_image('1B_shan.png', updown10)

# 1C. Do they look the same? Why or why not?

print """They do not look the same. The scrolling lost information."""

# 1D. Scroll the test image left by half its width
left = scrollLeft(test_image,test_image.shape[1]/2)

# Save it in 1D.png as above
save_binary_image('1D_shan.png',left)

# 1E. And then scroll that result back to the right by the same amount.
leftRight = scrollRight(left,test_image.shape[1]/2)

# Save in 1E.png.
save_binary_image('1E_shan.png',leftRight)

# 2. Boundary Detector

def findBoundary(img):
    '''Return an image that is one for boundary pixels and zero elsewhere'''
    # Compute the result of finding the boundary here
    result = np.zeros_like(img)  # Replace this with your code
    
    left = scrollLeft(img,1)
    right = scrollRight(img,1)
    up = scrollUp(img,1)
    down = scrollDown(img,1)
    
    result[np.logical_and(img==1,left==0)] = 1
    result[np.logical_and(img==1,right==0)] = 1
    result[np.logical_and(img==1,up==0)] = 1
    result[np.logical_and(img==1,down==0)] = 1
    
    return result

# Save the boundary of the test image

boundary = findBoundary(test_image)
save_binary_image('2_shan.png', boundary)

# 3. Dilate and Erode

def dilateImage(img):
    '''Return an image that is the dilation of the input img'''
    # Compute the dilation here and return it below
    result = np.zeros_like(img)  # Replace this with your code
    
    left = scrollLeft(img,1)
    right = scrollRight(img,1)
    up = scrollUp(img,1)
    down = scrollDown(img,1)
    
    result[np.logical_or(img,left)] = 1
    result[np.logical_or(result,right)] = 1
    result[np.logical_or(result,up)] = 1
    result[np.logical_or(result,down)] = 1
    
    return result


def erodeImage(img):
    '''Return an image that is the erosion of the input img'''
    # Compute the value of the erosion and return it below
    result = np.copy(img)  # Replace this with your code
    bdry = findBoundary(img)
    result[bdry==1] = 0
    return result

# 3A. Dilate the test image, then dilate that result, then dilate that result so you have
# three dilations. Save the final result.

D3 = dilateImage(dilateImage(dilateImage(test_image)))
save_binary_image('3A_shan.png', D3)

E3 = erodeImage(erodeImage(erodeImage(test_image)))
save_binary_image('3B_shan.png', E3)

E3D3 = dilateImage(dilateImage(dilateImage(E3)))
save_binary_image('3C_shan.png', E3D3)

# 3D. Find the boundary of the original image, and then dilate the boundary image.  Save the result.
# save as 3D.png
save_binary_image('3D_shan.png',dilateImage(findBoundary(test_image)))


# 3E. Then take the original image, dilate it once, and then find its boundary.  Save the result.
# save as 3E.png
save_binary_image('3E_shan.png',findBoundary(dilateImage(test_image)))

# 3F. Describe the difference between the two images.
print """The second result is smoother and thinner.""" 
