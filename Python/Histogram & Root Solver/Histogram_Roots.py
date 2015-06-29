#!/usr/bin/env python

"""
Scinet SCMP112 - Intro to Research Computing with Python
Homework # 2
Tomas Mawyin
"""

""" Question # 1: Statistical distributions and histograms """
import scipy.stats as ss
import pylab as py

# Number of samples to generate
N = 1000000

## Generate 1000000 numbers (a) from a normal distribution, centered on -2, with a standard deviation of 1.5.
# Random distribution parameters
center = -2.0
std = 1.5
# Generating normal distribution samples
a = ss.norm.rvs(loc=center, scale=std, size=N)

## Generate 1000000 numbers (b) from a uniform distribution between -1 and 1.
# Uniform distribution parameters
low = -1.0
up = 2.0
# Generating uniform distribution samples
b = ss.uniform.rvs(loc=low, scale=up, size=N)

## Multiply numbers x = a*b
x = a*b

## Generate a histogram
py.figure(1)
py.hist(x, bins=50, normed=True)

## Beautify histogram and saving figure
py.ylabel('Probability Distribution')
py.title('Random*Uniform Distributions')
py.grid(True)
py.tight_layout()
py.savefig('HW2_Histogram.eps',format='eps')

## Most probable value
print "Most probable value is near zero"


""" Question # 2: Solving roots of the equation: S^4 + S^2(z-2) + zS = 0 """
import numpy as np

## Setup values for zeta ranging from 0 to 0.62
# Number of points for z
M = 100
# Generating equally spaced values of z
z = np.linspace(0,0.62,M)
# Array to store final values of z vs root
vals = np.zeros((M,2))

## Using poly1d to set up the polynomial equation
for i in range(len(z)):
    p = np.poly1d([1,0,z[i]-2,z[i],0])
	
	## Finding roots of equation
    p_roots = p.roots
	
	## For each value in equation save root that lies between 0.0 and 0.65
    good_root = [j for j in p_roots if 0 <= j <= 0.65]
	
	## Storing final results
    vals[i,0] = z[i]
    vals[i,1] = good_root[0]
	
## Plot roots as a function of z
py.figure(2)
py.plot(vals[:,0],vals[:,1],'b',linewidth=2,label='root')

## Beautify the plot and saving figure
py.legend(loc='best')
py.xlabel('zeta value')
py.ylabel('root of polynomial')
py.title('Root of S^4 + S^2(z-2) + zS = 0 as function of z')
py.tight_layout()
py.grid(True)
py.savefig('HW2_Root.eps',format='eps')
py.show()
