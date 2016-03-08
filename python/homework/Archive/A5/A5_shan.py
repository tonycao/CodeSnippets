#######################################################################################
## Assignment 5                                                                      ##
## Discussion is allowed.                                                            ##
## Copying or sharing code is prohibited.                                            ##
## By typing your name below, you indicate agreement with the UNC Honor Code Pledge, ##
## that you have not given or received unauthorized assistance on this assignment.   ##
## Name: Liang Shan                                                                  ##
## Collaborators: None                                                               ## 
#######################################################################################

import numpy as np
import pylab
from mpl_toolkits.mplot3d import Axes3D

def readPDBfile(filename):
    anum = []
    aname = []
    resno = []
    coords = []
    for line in file(filename, 'r'):
        if line.startswith('ATOM  '):
            anum.append(int(line[6:11]))
            aname.append(line[12:16].upper())
            resno.append(int(line[22:26]))
            coords.append([float(line[30:38]),float(line[38:46]),float(line[47:54])])
            
    anum = np.array(anum)
    aname = np.array(aname)
    coords = np.array(coords)
    resno = np.array(resno)
    return anum, aname, resno, coords

def drawCA(aname, coords):
    fig = pylab.figure()
    ax = Axes3D(fig)
    select = aname == ' CA '
    ax.plot(coords[select,0],
            coords[select,1],
            coords[select,2])
    return fig


def checkHbonds(resno_i, coords_i, resno_j, coords_j):
    d = np.sqrt(np.sum((coords_i - coords_j)**2))
    return d <= 3.2 and d >= 2.6 and abs(resno_i - resno_j) >= 2
    
def Hbonds(anum, aname, resno, coords):
    pairs = []
    for i in xrange(len(aname)):
        if aname[i][1] == 'N':
            for j in xrange(i+1,len(aname)):
                if aname[j][1] == 'O' and checkHbonds(resno[i],coords[i],resno[j],coords[j]):
                    pairs.append([anum[i],anum[j]])
                    
        if aname[i][1] == 'O':
            for j in xrange(i+1,len(aname)):
                if aname[j][1] == 'N' and checkHbonds(resno[i],coords[i],resno[j],coords[j]):
                    pairs.append([anum[i],anum[j]])

    return pairs

for protein in ['7HVP', '1GFL']:
    num, name, rn, c = readPDBfile(protein + '.pdb')
    fig = drawCA(name, c)
    fig.savefig(protein+'.png')
    hydrogen_bonding_pairs = Hbonds(num, name, rn, c)
    print 'Number of hydrogen bonding pairs in', protein, 'is', len(hydrogen_bonding_pairs),'.'

