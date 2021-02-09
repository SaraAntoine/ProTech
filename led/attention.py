
from sense_hat import SenseHat
sense = SenseHat()
import time

#affichage fleche vers l'avant
vert = (87,213,59)
rouge = (255,0,0)
framboise =(187,11,11)
blanc =(255,255,255)

sense.clear()
#fleche tout droit
pause=0.2

while 1 :
	sense.clear(framboise)
	
	sense.set_pixel(4,7,blanc)
	sense.set_pixel(3,7,blanc)
	sense.set_pixel(4,6,blanc)
	sense.set_pixel(3,6,blanc)
	sense.set_pixel(4,4,blanc)
	sense.set_pixel(3,4,blanc)
	sense.set_pixel(4,3,blanc)
	sense.set_pixel(3,3,blanc)
	sense.set_pixel(4,2,blanc)
	sense.set_pixel(3,2,blanc)
	sense.set_pixel(4,1,blanc)
	sense.set_pixel(3,1,blanc)
	sense.set_pixel(4,0,blanc)
	sense.set_pixel(3,0,blanc)

	time.sleep(pause)
	sense.clear(framboise)
	time.sleep(pause)



time.sleep(3)
sense.clear()
