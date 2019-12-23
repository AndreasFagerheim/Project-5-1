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
t,x,y = Read_eight_Column_File('C:\Users\Andreas\Documents\Project 5\Project-5\Updates After deadline\Kode\5.0\build-Project-5NoCLass-Desktop_Qt_5_13_2_MinGW_64_bit-Debug\EulerForward.txt')


#plt.xlim(-2,-1.6)
plt.title("\n".join(wrap('Orbit of Earth around the sun at rest', 60)))
plt.ylabel('Y ')
plt.xlabel('X')

#plt.savefig('probdist1.png')
plt.show()
plt.figure()
