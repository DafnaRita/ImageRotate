#ifndef _HEADER_STRUCT_H_
#define _HEADER_STRUCT_H_

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

typedef enum {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
    /* more codes */
} read_error_code_t;

#endif 