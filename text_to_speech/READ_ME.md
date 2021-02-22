Voici les différentes informations pour le module speech to text
La solution utilisée est pico2wave

*****************************************

Pré requis :

==> Installation de pico2wave : sudo apt-get install libttspico-utils
wget http://archive.raspberrypi.org/debian/pool/main/s/svox/libttspico-utils_1.0+git20130326-3+rpi1_armhf.deb
wget http://archive.raspberrypi.org/debian/pool/main/s/svox/libttspico0_1.0+git20130326-3+rpi1_armhf.deb
sudo apt-get install -f ./libttspico0_1.0+git20130326-3+rpi1_armhf.deb ./libttspico-utils_1.0+git20130326-3+rpi1_armhf.deb

==> Installation du lecteur audio :
sudo apt install omxplayer

==>Choix du bon périphérique de sortie audio :
Par défaut la sortie audio est l'hdmi, si vous voulez utiliser la prise jack, il faut changer la source
Pour cela :
sudo raspi-config
->1 system Option
->2 audio
->choissisez votre source audio
->quittez le menu de config

**************************************************

Test de base (création fichier audio et lecture) :
==> pico2wave -l fr-FR -w test.wav "faites demi-tour dès que possible" && omxplayer test.wav

Execution du programme speak.c :
==>Ce programme contient un main et une fonction lecture, le main sert uniquement aux tests
==>Vous pouvez regarder les commenataires pour comprendre son fonctionnement
==>Pour utiliser cette fonctionalité, vous pouvez coller la fonction lecture() dans votre code et lui passer la chaine de caractère à jouer

