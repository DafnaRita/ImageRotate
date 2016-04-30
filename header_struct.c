#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

typedef struct {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;

    uint16_t biWidth;
    uint32_t biHeight;
    uint32_t biPlanes;
    uint16_t biBitCount;

    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_header_t;

struct pixel_t { char r,g,b; };

struct image_t {
    uint32_t width, height;
    struct pixel_t* data;
};

