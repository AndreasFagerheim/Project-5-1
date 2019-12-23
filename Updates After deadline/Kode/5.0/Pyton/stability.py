# -*- coding: utf-8 -*-
"""
Created on Sun Dec 22 20:20:04 2019

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
t,x,y = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/EulerForward0.1.txt')
t,x2,y2 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/EulerForward0.01.txt')
t,x3,y3 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/EulerForward0.002.txt')
t,x4,y4 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/EulerForward0.001.txt')
t,x5,y5 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/EulerForward0.0001.txt')


#plt.plot(x,y,label="euler")
plt.plot(x,y, label="dt = 0.1")
plt.plot(x2,y2, label="dt = 0.01")
plt.plot(x3,y3, label="dt = 0.002")
plt.plot(x4,y4, label="dt = 0.001")
plt.plot(x5,y5, label="dt = 0.0001")
plt.legend(bbox_to_anchor=(0.1, 0.5), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('Position calculated with different time steps for Euler', 60)))
plt.ylabel('Y-position [AU]')
plt.xlabel('X-position [AU]')
plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/stabilityEuler.png')
plt.show()
plt.figure()

#verlet ulike dt
t,x,y = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verlet0.1.txt')
t,x2,y2 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verlet0.01.txt')
t,x3,y3 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verlet0.002.txt')
t,x4,y4 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verlet0.001.txt')
t,x5,y5 = Read_three_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verlet0.0001.txt')
plt.plot(x,y, label="dt = 0.1")
plt.plot(x2,y2, label="dt = 0.01")
plt.plot(x3,y3, label="dt = 0.002")
plt.plot(x4,y4, label="dt = 0.001")
plt.plot(x5,y5, label="dt = 0.0001")

plt.legend(bbox_to_anchor=(0.3, 0.7), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('Position calculated with different time steps for Verlet', 60)))
plt.ylabel('Y-position [AU]')
plt.xlabel('X-position [AU]')
plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/stabilityVerlet.png')
plt.show()
plt.figure()