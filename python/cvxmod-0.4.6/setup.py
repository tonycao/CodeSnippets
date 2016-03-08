#!/usr/bin/env python

from distutils.core import setup

setup(name='cvxmod',
      version='0.4.6',
      description='Convex Optimization in Python',
      author='Jacob Mattingley',
      author_email='jacobm@stanford.edu',
      url='http://cvxmod.net/',
      license='GNU GPL version 3',
      packages=['cvxmod', 'cvxmod.atoms', 'cvxmod.sets'],
)
