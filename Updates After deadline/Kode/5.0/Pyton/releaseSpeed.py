# -*- coding: utf-8 -*-
"""
Created on Thu Dec 19 13:19:46 2019

@author: Andreas
"""

import itertools
import numpy as np
import matplotlib.pyplot as plt
from textwrap import wrap

def Read_three_Column_File(file_name):
    with open(file_name, 'r') as data:
            t = []
            posX = []
            posY = []
            for line in itertools.islice(data, 1, None):
                p = line.split()
                t.append(float(p[0]))
                posX.append(float(p[1]))
                posY.append(float(p[2]))
    return t,posX,posY

plt.figure()
#euler ulike dt
t,x,y = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verletUnslippe0.txt')
t,x2,y2 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verletUnslippe1.txt')
t,x3,y3 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verletUnslippe2.txt')
t,x4,y4 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verletUnslippe3.txt')
t,x5,y5 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verletUnslippe4.txt')


#plt.plot(x,y,label="euler")
plt.plot(x,y, label="V = 2.6 pi")
plt.plot(x2,y2, label="V = 2.7 pi")
plt.plot(x3,y3, label="V = 2.8 pi")
plt.plot(x4,y4, label="V = 2.82 pi")
plt.plot(x5,y5, label="V = 2.9 pi")
plt.legend(bbox_to_anchor=(0.1, 01.0), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('Earth movement with different start velocities over 40 years', 60)))
plt.ylabel('Y-position [AU]')
plt.xlabel('X-position [AU]')
#plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Data/NoClass/velocityEscape40.png')
plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/velocityEscape.png')
plt.show()
plt.figure()