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
            posX = []
            posY = []
            for line in itertools.islice(data, 0, None):
                p = line.split()
                t.append(float(p[0]))
                posX.append(float(p[3]))
                posY.append(float(p[4]))
    return posX,posY

plt.figure()
x,y = Read_six_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/SolJordFixedEuler.txt')
x2,y2 = Read_six_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/SolJordFixedVerlet.txt')
plt.plot(x,y,label="euler")
plt.plot(x2,y2, label="verlet")
plt.legend(bbox_to_anchor=(0.8, 1), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('Orbit of Earth around the sun at rest', 60)))
plt.ylabel('Y-position [AU]')
plt.xlabel('X-position [AU]')

plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/plotXYpos.png')
plt.show()
plt.figure()