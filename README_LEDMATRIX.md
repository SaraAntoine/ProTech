Accès à la mémoire sous Linux /dev/mem
Pour Linux chaque périphérique d'Entrée/Sortie ressemble autant que possible à un fichier.
Linux donne à notre programme l'accès à la mémoire brute en mode utilisateur, il représente la mémoire comme un seul fichier binaire /dev/mem.
Ce fichier de périphérique de caractères est une image de la mémoire. Quand on lit ou que l’on écrit l'octet n, cela revient à lire et écrire l'emplacement mémoire à l'adresse de l'octet n.
Fichiers de mappage de la mémoire
L'approche de Linux en matière d'Entrée/Sortie met l'accent sur les fichiers. Certaines fois il arrive que la lecture et l'écriture d'un fichier sur un périphérique externe (ex : disque dur) soient trop lentes. Pour pallier ce problème, Linux dispose d'une fonction de mappage de la mémoire qui lit n'importe quelle partie d'un fichier dans la mémoire de l'utilisateur. Cela nous permet de travailler directement avec elle en utilisant des pointeurs. C’est un moyen très rapide d'accéder à n'importe quel fichier (ex : /dev/mem).
Pour accéder à la mémoire : implémenter l'accès à la mémoire sous la forme d'un fichier que l'on peut lire, puis mapper ce fichier en mémoire afin de pouvoir le lire comme s'il s'agissait de mémoire.
Cela permet aux adresses physiques fixes des périphériques d'entrer dans les adresses virtuelles de l'espace utilisateur. Lorsque l’on mappe en mémoire le fichier /dev/mem dans la mémoire utilisateur, il peut être situé n'importe où et l'adresse du début de la zone de registre se trouvera dans l'espace d'adressage alloué par le programme.
La fonction clé est mmap

void *mmap(
    void *addr,
    size_t length,
    int prot, 
    int flags,
    int fd, 
    off_t offset
);

La fonction mappe en mémoire le fichier correspondant au descripteur de fichier fd et renvoie son adresse de départ. Les paramètres offset et length contrôlent la partie du fichier mappée, les parties mappées commencent à l'octet donné par offset et continuent pour les octets length.
On peut également spécifier l'adresse à laquelle on souhaite que le fichier soit chargé dans l'espace d'adressage de votre programme (Attention : le système peut l'utiliser simplement comme une indication).
Prot et flags spécifient les différentes façons dont le fichier peut être mappé en mémoire.
Maintenant, mappons /dev/mem en mémoire.

Ouverture du périphérique /dev/mem :

uint32_t memfd = open("/dev/mem", O_RDWR | O_SYNC) ;
Tant que ça fonctionne, on peut mapper le fichier en mémoire.
On peut mapper le fichier à partir de 0x2020 0000 pour le Pi 1 ou à partir de 0x3F20 0000 pour le Pi 2.
Si on travaille qu’avec les registres GPIO, nous n’avons besoin que d'offsets de 0000 à 00B0, soit 176 octets.

uint32_t * map = (uint32_t *)mmap(
    NULL,
    4*1024,
    (PROT_READ | PROT_WRITE),
    MAP_SHARED,
    memfd,
    0x3f200000);

On n’a pas défini d'adresse pour le fichier à charger, c’est le système qui s'en chargera et renverra l'adresse dans la carte.
On a demandé la permission de lire/écrire et autorisé d'autres processus à partager la carte.
Cela fait de map une variable très importante car elle donne l'emplacement du début de la zone de registre GPIO mais dans l'espace utilisateur.
