# -*- coding: utf-8 -*-
"""
Created on Thu Dec 19 13:19:46 2019

@author: Andreas
"""

import itertools
import numpy as np
import matplotlib.pyplot as plt
from textwrap import wrap

def Read_four_Column_File(file_name):
    with open(file_name, 'r') as data:
            Ek = []
            Ep= []
            Etot = []
            aMom = []
            for line in itertools.islice(data, 0, None):
                p = line.split()
                Ek.append(float(p[0]))
                Ep.append(float(p[1]))
                Etot.append(float(p[2]))
                aMom.append(float(p[3]))
    return Ek,Ep,Etot,aMom


k,p,tot,aM = Read_four_Column_File('C:/Users/Andreas/Documents/Project 5/Updates After deadline/Project-5/Data/Class/energiEuler.txt')
t = np.linspace(0.0,1.0,len(k))
#plt.plot(x,y,label="euler")
plt.plot(t,k)
plt.legend(bbox_to_anchor=(0.8, 1), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('The calculated kinetic energy over 1 year with n = 10000 using Euler', 60)))
plt.ylabel('kinetic energy  [kg (Au/year)^2]')
plt.xlabel('Time [year]')
plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/plotEulerKinetisk.png')
plt.show()
plt.figure()
plt.plot(t,p)
plt.legend(bbox_to_anchor=(0.8, 1), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('The calculated kinetic energy over 1 year with n = 10000 using Euler', 60)))
plt.ylabel('kinetic energy  [kg (Au/year)^2]')
plt.xlabel('Time [year]')
plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/plotEulerPotensiel.png')
plt.show()
plt.figure()
k2,p2,t,aM2 = Read_four_Column_File('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/energiVerlet.txt')
t = np.linspace(0.0,1.0,len(k))
#plt.plot(x,y,label="euler")
plt.plot(t,k2)
plt.legend(bbox_to_anchor=(0.8, 1), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('The calculated kinetic energy over 1 year with n = 10000 using velocity Verlet', 60)))
plt.ylabel('kinetic energy  [kg (Au/year)^2]')
plt.xlabel('Time [year]')
plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/plotKinetiskVerlet.png')
plt.show()
plt.figure()

plt.plot(t,p2)
plt.legend(bbox_to_anchor=(0.8, 1), loc='upper left', borderaxespad=0.)
plt.title("\n".join(wrap('The calculated potensial energy over 1 year with n = 10000 using velocity Verlet', 60)))
plt.ylabel('potensial energy')
plt.xlabel('Time [year]')
plt.savefig('C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/plotVerletPotensiel.png')
plt.show()
plt.figure()





