# -*- coding: utf-8 -*-
"""
Created on Sun Dec 22 16:18:35 2019

@author: Andreas
"""

# -*- coding: utf-8 -*-
"""
Created on Thu Dec 19 13:19:46 2019

@author: Andreas
"""

import itertools
import numpy as np
import matplotlib.pyplot as plt
from textwrap import wrap

def Read_six_Column_File(file_name):
    with open(file_name, 'r') as data:
            t = []
            jordX = []
            jordY = []
            jupiterX = []
            jupiterY = []
            for line in itertools.islice(data, 0, None):
                p = line.split()
                t.append(float(p[0]))
                jordX.append(float(p[3]))
                jordY.append(float(p[4]))
                jupiterX.append(float(p[6]))
                jupiterY.append(float(p[7]))
    return jordX,jordY,jupiterX,jupiterY

plt.figure()
plt.figure(num=None, figsize=(6, 6), dpi=100, facecolor='w', edgecolor='k')
x,y,x2,y2 = Read_six_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/JupiterEnters1000LowDT.txt')
#x2,y2 = Read_six_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/SolJordFixedVerlet.txt')
plt.plot(x,y,label="Earth")
plt.plot(x2,y2, label="Juipiter")
plt.plot([0], [0], marker='o', markersize=10, color="orange",label="Sun")
#plt.figure(num=None, figsize=(8, 6), dpi=80, facecolor='w', edgecolor='k')
plt.legend(bbox_to_anchor=(0.8, 1), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('Orbit of Earth with Jupiters mass increasd by a factor of 1000 and dt = 1/10000', 60)))
plt.ylabel('Y-position [AU]')
plt.xlabel('X-position [AU]')
print ("im her")

plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/JupiterIsHere100Years1000MassTest2.png')

plt.show()
plt.figure()