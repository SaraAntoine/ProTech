from sense_hat import SenseHat
from math import *
import time
sense = SenseHat()
sense.clear()

from sense_hat import SenseHat

sense = SenseHat()

nb=100


while True :
	acc=0
	i=0
	
	for i in range(nb):
		acceleration = sense.get_accelerometer_raw()
		x = acceleration['x']
		y = acceleration['y']
		z = acceleration['z']
		
		acc=acc+sqrt(x*x+y*y+z*z)
		
	acc_moy=acc/nb

	print("acceleration= {0}" .format(acc_moy))

