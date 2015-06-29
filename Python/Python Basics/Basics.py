#!/usr/bin/env python
import numpy as np

def DecimalToTernary(n):
    if n > 6561:
        print "Decimal value out of range. Use value up to 6561"
    else:
        d2t = np.zeros((9,), dtype=np.int)
        d = 1   # dummy variable to start the while loop
        i = -1  # counter to save reminder of function
        a = n   # saves original value for backup
        while d != 0:
            d,r = divmod(a,3)   # Calculates quotient and remainder
            d2t[i] = r          # saves remainder into array
            i = i-1             
            a = d
        return d2t

def CalcOverflow(m):
    m = float(m)    # Converting value to float
    n = 1
    while True:
        try:
            m**n    # Evaluating exponent and increasing it by one
            n = n + 1
        except:
            #print n # If exception is caught the value of n gets returned
            return n

def CalcUnderflow(m):
    m = float(m)    # Converting value to float
    p = -1          # start value for exponent
    r = 1           # dummy value for while loop
    while r != 0.0:
        r = m**p
        p -= 1
    print abs(p+1)

