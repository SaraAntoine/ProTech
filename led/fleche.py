from sense_hat import SenseHat
sense = SenseHat()
import time

#affichage fleche vers l'avant
vert = (87,213,59)
rouge =(255,0,0)
blanc =(255,255,255)

sense.clear()
#fleche tout droit
pause=0.2

sense.set_pixel(4,7,vert)
time.sleep(pause)

sense.set_pixel(4,6,vert)
time.sleep(pause)

sense.set_pixel(4,5,vert)
time.sleep(pause)

sense.set_pixel(1,4,vert)
sense.set_pixel(4,4,vert)
sense.set_pixel(7,4,vert)
time.sleep(pause)

sense.set_pixel(4,3,vert)
sense.set_pixel(6,3,vert)
sense.set_pixel(2,3,vert)
time.sleep(pause)

sense.set_pixel(3,2,vert)
sense.set_pixel(4,2,vert)
sense.set_pixel(5,2,vert)
time.sleep(pause)

sense.set_pixel(4,1,vert)
time.sleep(pause)


time.sleep(3)
sense.clear()

#fleche a droite
sense.set_pixel(0,4,vert)
sense.set_pixel(1,4,vert)
sense.set_pixel(2,4,vert)
sense.set_pixel(3,1,vert)
sense.set_pixel(3,4,vert)
sense.set_pixel(3,7,vert)
sense.set_pixel(4,2,vert)
sense.set_pixel(4,4,vert)
sense.set_pixel(4,6,vert)
sense.set_pixel(5,3,vert)
sense.set_pixel(5,4,vert)
sense.set_pixel(5,5,vert)
sense.set_pixel(6,4,vert)

time.sleep(3)
sense.clear()

#fleche a gauche
sense.set_pixel(1,4,vert)
sense.set_pixel(2,3,vert)
sense.set_pixel(2,4,vert)
sense.set_pixel(2,5,vert)
sense.set_pixel(3,2,vert)
sense.set_pixel(3,4,vert)
sense.set_pixel(3,6,vert)
sense.set_pixel(4,1,vert)
sense.set_pixel(4,4,vert)
sense.set_pixel(4,7,vert)
sense.set_pixel(5,4,vert)
sense.set_pixel(6,4,vert)
sense.set_pixel(7,4,vert)

time.sleep(3)
sense.clear()

#panneau attention
sense.set_pixel(0,5,rouge)
sense.set_pixel(0,6,rouge)
sense.set_pixel(1,3,rouge)
sense.set_pixel(1,4,rouge)
sense.set_pixel(1,6,rouge)
sense.set_pixel(2,1,rouge)
sense.set_pixel(2,2,rouge)
sense.set_pixel(2,6,rouge)
sense.set_pixel(3,0,rouge)
sense.set_pixel(3,1,rouge)
sense.set_pixel(3,6,rouge)
sense.set_pixel(4,1,rouge)
sense.set_pixel(4,2,rouge)
sense.set_pixel(4,6,rouge)
sense.set_pixel(5,3,rouge)
sense.set_pixel(5,4,rouge)
sense.set_pixel(5,6,rouge)
sense.set_pixel(6,5,rouge)
sense.set_pixel(6,6,rouge)
sense.set_pixel(1,5,rouge)
sense.set_pixel(2,3,rouge)
sense.set_pixel(2,4,rouge)
sense.set_pixel(2,5,rouge)
sense.set_pixel(4,3,rouge)
sense.set_pixel(4,4,rouge)
sense.set_pixel(4,5,rouge)
sense.set_pixel(5,5,rouge)
sense.set_pixel(3,4,rouge)




sense.set_pixel(3,2,blanc)
sense.set_pixel(3,3,blanc)
sense.set_pixel(3,5,blanc)


time.sleep(5)
sense.clear()
