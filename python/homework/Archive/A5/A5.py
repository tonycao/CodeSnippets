#######################################################################################
## Assignment 5                                                                      ##
## Discussion is allowed.                                                            ##
## Copying or sharing code is prohibited.                                            ##
## By typing your name below, you indicate agreement with the UNC Honor Code Pledge, ##
## that you have not given or received unauthorized assistance on this assignment.   ##
## Name:                                                                             ##
## Collaborators:                                                                    ## 
#######################################################################################

import numpy as np
import pylab
from mpl_toolkits.mplot3d import Axes3D

def readPDBfile(filename):
    '''read a PDB file, extract the ATOM lines, 
    and return atom number, atom name, residue 
    number, and coords for each'''
    anum = []
    aname = []
    resno = []
    coords = []
    # Your code goes here            
    anum = np.array(anum)
    aname = np.array(aname)
    coords = np.array(coords)
    resno = np.array(resno)
    return anum, aname, resno, coords

def drawCA(aname, coords):
    '''Plot the Calpha backbone of an atom'''
    fig = pylab.figure()
    ax = Axes3D(fig)
    # Your code goes here
    return fig

def Hbonds(anum, aname, resno, coords):
    '''Find hydrogen bonds'''
    pairs = [] 
    # Your code goes here
    return pairs

# Do NOT modify the following test code
for protein in ['7HVP', '1GFL']:
    num, name, rn, c = readPDBfile(protein + '.pdb')
    fig = drawCA(name, c)
    fig.savefig(protein+'.png')
    hydrogen_bonding_pairs = Hbonds(num, name, rn, c)
    print 'Number of hydrogen bonding pairs in', protein, 'is', len(hydrogen_bonding_pairs),'.'

