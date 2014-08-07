# To generator large scale input data

import random 
import os
import sys

scale = int(sys.argv[1])
file1 = open('input1','w')

for i in range(0, scale):
  input = str(random.random()) + "\n"
  file1.write(input)
file1.close()

file2 = open('input2','w')
for i in range(0, scale):
  input = str(random.random()) + "\n"
  file2.write(input)
file2.close()
