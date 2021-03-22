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
    
    /* Arrows*/
    
     /* clear the led matrix */
    memset(map, 0, FILESIZE);
    
    /* Arrow to the right */  
    for (i = 0; i < 8; i++) {  	
	*(p + 3) = 0xFFF;
	*(p + 4) = 0xFFF;
	*(p + 12) = 0xFFF;
	*(p + 13) = 0xFFF;
	*(p + 21) = 0xFFF;
	*(p + 22) = 0xFFF;
	*(p + 24) = 0xFFF;
	*(p + 25) = 0xFFF;
	*(p + 26) = 0xFFF;
	*(p + 27) = 0xFFF;
	*(p + 28) = 0xFFF;
	*(p + 29) = 0xFFF;
	*(p + 30) = 0xFFF;
	*(p + 31) = 0xFFF;
	*(p + 32) = 0xFFF;
	*(p + 33) = 0xFFF;
	*(p + 34) = 0xFFF;
	*(p + 35) = 0xFFF;
	*(p + 36) = 0xFFF;
	*(p + 37) = 0xFFF;
	*(p + 38) = 0xFFF;
	*(p + 39) = 0xFFF;
	*(p + 45) = 0xFFF;
	*(p + 46) = 0xFFF;
	*(p + 52) = 0xFFF;
	*(p + 53) = 0xFFF;
	*(p + 59) = 0xFFF;
	*(p + 60) = 0xFFF;
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
