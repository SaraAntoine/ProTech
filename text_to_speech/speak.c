#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Fonction lecture()
 * But : Faire lire au rpi la chaine de caractère transmise
 * Param : chaine de caractère
 * Return : void
*/
void lecture(char text[400]){
	//initialisation du début et de la fin de la commande
	char cmd[500]="pico2wave -l fr-FR -w audio.wav \"";
	char end[50]="\" && omxplayer audio.wav";	

	//création de la ligne de commande via des concaténation
	strcat(cmd,text);
	strcat(cmd, end);
	
	//execution de la commande (création de l'audio + lecture) puis supprimer fichier audio
	system(cmd);
	system("rm audio.wav");
}

int main (int argc, char * argv[])  {
	//test de la fonction
	lecture("Bonjour les amis j'espère que vous m'entendez bien");
	lecture("Ce test est à priori réussi !");
	lecture("On peut dire que c'est beaucoup de temps passé que pour ça, mais bon au moins ça marche");
}


