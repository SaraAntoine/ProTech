Voici les différentes informations pour le module speech to text
La solution utilisée est pico2wave

Pré requis :

==> Installation de pico2wave : sudo apt-get install libttspico-utils
wget http://archive.raspberrypi.org/debian/pool/main/s/svox/libttspico-utils_1.0+git20130326-3+rpi1_armhf.deb
wget http://archive.raspberrypi.org/debian/pool/main/s/svox/libttspico0_1.0+git20130326-3+rpi1_armhf.deb
sudo apt-get install -f ./libttspico0_1.0+git20130326-3+rpi1_armhf.deb ./libttspico-utils_1.0+git20130326-3+rpi1_armhf.deb

==> Installation du lecteur audio :
sudo apt install omxplayer


Test de base (création fichier audio et lecture) :

