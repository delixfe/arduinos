#include "arduinos.h"

/*
 * Due to RAM memory limitations, the 2 buffers below are used repeatedly to build communication packages
 * Memory is so tight (especially when running Nano/UIP) that I suspect that there is no room for "malloc" and 
 * hence memory fragmentation.
 */
char bufferSmall[SIZE_SMALL];
char bufferBig[SIZE_BIG]; 

/*
 * Method used to move from PROGMEM to the 2 buffers above
 */
void progmem2buffer(char *pOut, const char *pProgmem, int maxSize) {
    int i;
    for (i=0; i<maxSize; i++) {
        char c = pgm_read_byte(pProgmem++);
        *pOut++ = c;
        if (c == NULL) {
            break;
        }
    }
}

/*
 * Moved from PROGMEM to bufferSmall
 */
char *bufferSmallFill(const char *pProgmem) {
    progmem2buffer(bufferSmall, pProgmem, SIZE_SMALL); 
    return bufferSmall;
}

/*
 * Moved from PROGMEM to bufferBig
 */
char *bufferBigFill(const char *pProgmem) {
    progmem2buffer(bufferBig, pProgmem, SIZE_BIG); 
    return bufferBig;
}


