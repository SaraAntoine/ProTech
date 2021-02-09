from sense_hat import SenseHat
sense = SenseHat()
import time

#affichage fleche vers l'avant
vert = (87,213,59)
rouge =(255,0,0)
blanc =(255,255,255)

sense.clear()
#fleche tout droit
pause=0.1

while 1 :
	sense.set_pixel(7,4,vert)
	sense.set_pixel(7,3,vert)
	time.sleep(pause)
	
	sense.set_pixel(6,4,vert)
	sense.set_pixel(6,3,vert)
	time.sleep(pause)
	

	sense.set_pixel(5,4,vert)
	sense.set_pixel(5,3,vert)
	time.sleep(pause)

	sense.set_pixel(4,7,vert)
	sense.set_pixel(4,4,vert)
	sense.set_pixel(4,3,vert)
	sense.set_pixel(4,0,vert)
	time.sleep(pause)

	sense.set_pixel(3,7,vert)
	sense.set_pixel(3,6,vert)
	sense.set_pixel(3,4,vert)
	sense.set_pixel(3,3,vert)
	sense.set_pixel(3,1,vert)
	sense.set_pixel(3,0,vert)
	time.sleep(pause)
	
	sense.set_pixel(2,6,vert)
	sense.set_pixel(2,5,vert)
	sense.set_pixel(2,4,vert)
	sense.set_pixel(2,3,vert)
	sense.set_pixel(2,2,vert)
	sense.set_pixel(2,1,vert)
	time.sleep(pause)
	
	sense.set_pixel(1,5,vert)
	sense.set_pixel(1,4,vert)
	sense.set_pixel(1,3,vert)
	sense.set_pixel(1,2,vert)
	time.sleep(pause)

	sense.set_pixel(0,4,vert)
	sense.set_pixel(0,3,vert)
	time.sleep(pause)


	sense.clear()


time.sleep(3)
sense.clear()
