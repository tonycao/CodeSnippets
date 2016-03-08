import numpy as np
import scipy
import pylab
import pymorph
import mahotas
from scipy import ndimage

dna = mahotas.imread('dna.jpeg')
#pylab.imshow(dna)
#pylab.show()

print dna.shape
print dna.dtype
print dna.max()
print dna.min()

#pylab.imshow(dna // 2)
#pylab.show()

dnaf = ndimage.gaussian_filter(dna,16)
T = mahotas.thresholding.otsu(dnaf)
#pylab.imshow(dnaf>T)
#pylab.gray()
#pylab.show()

# label cells
labeled,nr_objects = ndimage.label(dnaf>T)
print nr_objects
#pylab.imshow(labeled)
#pylab.jet()
#pylab.show()

# find the seeds
rmax = pymorph.regmax(dnaf)
#pylab.imshow(pymorph.overlay(dna,rmax))
#pylab.show()

seeds,nr_nuclei = ndimage.label(rmax)
print nr_nuclei

# watershed
dist = ndimage.distance_transform_edt(dnaf>T)
dist = dist.max()-dist
dist -= dist.min()
dist = dist/float(dist.ptp())*255
dist = dist.astype(np.uint8)
#pylab.imshow(dist)
#pylab.show()
nuclei = pymorph.cwatershed(dist, seeds)
#pylab.imshow(nuclei)
#pylab.show()
whole = mahotas.segmentation.gvoronoi(nuclei)
#pylab.imshow(whole)
#pylab.show()
borders = np.zeros(nuclei.shape, np.bool)
borders[0,:] = 1
borders[-1,:] = 1
borders[:,0] = 1
borders[:,-1] = 1
at_border = np.unique(nuclei[borders])
for obj in at_border:
	whole[whole==obj] = 0
#pylab.imshow(whole)
#pylab.show()
