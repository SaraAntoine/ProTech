#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#define FILEPATH "/dev/fb1"
#define NUM_WORDS 64
#define FILESIZE (NUM_WORDS * sizeof(uint16_t))

#define RGB565_RED 0xF800

void delay(int);

int main(void)
{
    int i;
    int fbfd;
    uint16_t *map;
    uint16_t *p;
    struct fb_fix_screeninfo fix_info;

    /* open the led frame buffer device */
    fbfd = open(FILEPATH, O_RDWR);
    if (fbfd == -1) {
	perror("Error (call to 'open')");
	exit(EXIT_FAILURE);
    }

    /* read fixed screen info for the open device */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
	perror("Error (call to 'ioctl')");
	close(fbfd);
	exit(EXIT_FAILURE);
    }

    /* now check the correct device has been found */
    if (strcmp(fix_info.id, "RPi-Sense FB") != 0) {
	printf("%s\n", "Error: RPi-Sense FB not found");
	close(fbfd);
	exit(EXIT_FAILURE);
    }

    /* map the led frame buffer device into memory */
    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (map == MAP_FAILED) {
	close(fbfd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }

    /* set a pointer to the start of the memory area */
    p = map;

    /* clear the led matrix */
    memset(map, 0, FILESIZE);
        
     /* clear the led matrix */
    memset(map, 0, FILESIZE);
    
    /* Attention sign */  
    for (i = 0; i < 8; i++) {  
	//fond rouge
	*(p + 0) = 0xF800;	
	*(p + 1) = 0xF800;
	*(p + 2) = 0xF800;
	*(p + 5) = 0xF800;
	*(p + 6) = 0xF800;
	*(p + 7) = 0xF800;
	
	*(p + 8) = 0xF800;	
	*(p + 9) = 0xF800;
	*(p + 10) = 0xF800;
	*(p + 13) = 0xF800;
	*(p + 14) = 0xF800;
	*(p + 15) = 0xF800;

	*(p + 16) = 0xF800;	
	*(p + 17) = 0xF800;
	*(p + 18) = 0xF800;
	*(p + 21) = 0xF800;
	*(p + 22) = 0xF800;
	*(p + 23) = 0xF800;


	*(p + 24) = 0xF800;	
	*(p + 25) = 0xF800;
	*(p + 26) = 0xF800;
	*(p + 29) = 0xF800;
	*(p + 30) = 0xF800;
	*(p + 31) = 0xF800;


	*(p + 32) = 0xF800;	
	*(p + 33) = 0xF800;
	*(p + 34) = 0xF800;
	*(p + 37) = 0xF800;
	*(p + 38) = 0xF800;
	*(p + 39) = 0xF800;

	*(p + 40) = 0xF800;	
	*(p + 41) = 0xF800;
	*(p + 42) = 0xF800;
	*(p + 43) = 0xF800;
	*(p + 44) = 0xF800;
	*(p + 45) = 0xF800;
	*(p + 46) = 0xF800;
	*(p + 47) = 0xF800;

	*(p + 48) = 0xF800;	
	*(p + 49) = 0xF800;
	*(p + 50) = 0xF800;
	*(p + 53) = 0xF800;
	*(p + 54) = 0xF800;
	*(p + 55) = 0xF800;
	
	*(p + 56) = 0xF800;	
	*(p + 57) = 0xF800;
	*(p + 58) = 0xF800;
	*(p + 61) = 0xF800;
	*(p + 62) = 0xF800;
	*(p + 63) = 0xF800;

	//point d'exclamation blanc
	*(p + 3) = 0xFFFF;	
	*(p + 4) = 0xFFFF;
	*(p + 11) = 0xFFFF;
	*(p + 12) = 0xFFFF;
	*(p + 19) = 0xFFFF;
	*(p + 20) = 0xFFFF;
	*(p + 27) = 0xFFFF;	
	*(p + 28) = 0xFFFF;
	*(p + 35) = 0xFFFF;
	*(p + 36) = 0xFFFF;
	*(p + 51) = 0xFFFF;
	*(p + 52) = 0xFFFF;
	*(p + 59) = 0xFFFF;
	*(p + 60) = 0xFFFF;
	delay(300);
    }

    /* clear the led matrix */
    memset(map, 0, FILESIZE);
    

    /* un-map and close */
    if (munmap(map, FILESIZE) == -1) {
	perror("Error un-mmapping the file");
    }
    close(fbfd);

    return 0;
}

void delay(int t)
{
    usleep(t * 1000);
}
