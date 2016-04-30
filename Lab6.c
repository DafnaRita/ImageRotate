#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <stdint.h>

#pragma pack(push, 2)
typedef struct 
{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;

    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_header;
#pragma pack(pop)

typedef enum{
    READ_OK = 0,
    READ_INVALID_SIGNATURE = 1,
    READ_INVALID_BITS = 2,
    READ_INVALID_HEADER,
    such_process,
    UNKNOW_ERROR ,
    WRONG_PALLETE = 132
    /* more codes */
} read_error_code_t;


typedef struct { char r,g,b; }pixel_t;

extern int errno;

typedef struct  {
    uint32_t width, height;
    pixel_t* data;
} image_t;

static char const* const read_error_message[]={
    "OK lol",
    "Operation not permitted ",
    "No such file or directory ",
    "No such process ",
    "Interrupted system call ",
    "I/O error ",
    "No such device or address ",
    "Argument list too long ",
    "Exec format error ",
    "Bad file number ",
    "No child processes ",
    "Try again ",
    "Out of memory ",
    "Permission denied ",
    "Bad address ",
    "Block device required ",
    "Device or resource busy ",
    "File exists ",
    "Cross-device link ",
    " No such device ",
    "Not a directory ",
    "Is a directory ",
    " Invalid argument ",
    "File table overflow ",
    " Too many open files ",
    " Not a typewriter ",
    " Text file busy ",
    " File too large ",
    " No space left on device ",
    " Illegal seek ",
    "Read-only file system ",
    "Too many links ",
    " Broken pipe ",
    "Math argument out of domain of func ",
    " Math result not representable ",
    " Resource deadlock would occur ",
    " File name too long ",
    " No record locks available ",
    "Function not implemented ",
    " Directory not empty ",
    " Too many symbolic links encountered ",
    " Operation would block ",
    " No message of desired type ",
    " Identifier removed ",
    " Channel number out of range ",
    " Level 2 not synchronized ",
    " Level 3 halted ",
    " Level 3 reset ",
    " Link number out of range ",
    " Protocol driver not attached ",
    " No CSI structure available ",
    " Level 2 halted ",
    " Invalid exchange ",
    " Invalid request descriptor ",
    " Exchange full ",
    " No anode ",
    " Invalid request code ",
    " Invalid slot ",
    " Bad font file format ",
    " Device not a stream ",
    " No data available ",
    " Timer expired ",
    " Out of streams resources ",
    " Machine is not on the network ",
    " Package not installed ",
    " Object is remote ",
    " Link has been severed ",
    " Advertise error ",
    " Srmount error ",
    " Communication error on send ",
    " Protocol error ",
    " Multihop attempted ",
    " RFS specific error ",
    " Not a data message ",
    " Value too large for defined data type ",
    " Name not unique on network ",
    " File descriptor in bad state ",
    " Remote address changed ",
    " Can not access a needed shared library ",
    " Accessing a corrupted shared library ",
    " .lib section in a.out corrupted ",
    " Attempting to link in too many shared libraries ",
    " Cannot exec a shared library directly ",
    " Illegal byte sequence ",
    " Interrupted system call should be restarted ",
    " Streams pipe error ",
    " Too many users ",
    " Socket operation on non-socket ",
    " Destination address required ",
    " Message too long ",
    " Protocol wrong type for socket ",
    " Protocol not available ",
    " Protocol not supported ",
    " Socket type not supported ",
    " Operation not supported on transport endpoint ",
    " Protocol family not supported ",
    " Address family not supported by protocol ",
    " Address already in use ",
    " Cannot assign requested address ",
    " Network is down ",
    " Network is unreachable ",
    " Network dropped connection because of reset ",
    " Software caused connection abort ",
    " Connection reset by peer",
    " No buffer space available ",
    " Transport endpoint is already connected ",
    " Transport endpoint is not connected ",
    " Cannot send after transport endpoint shutdown ",
    " Too many references: cannot splice ",
    " Connection timed out ",
    " Connection refused ",
    " Host is down ",
    " No route to host ",
    " Operation already in progress ",
    " Operation now in progress ",
    " Stale NFS file handle ",
    " Structure needs cleaning ",
    " Not a XENIX named type file ",
    " No XENIX semaphores available ",
    " Is a named type file ",
    " Remote I/O error ",
    " Quota exceeded ",
    " No medium found ",
    " Wrong medium type ",
    " Operation Canceled ",
    "Required key not available ",
    " Key has expired ",
    " Key has been revoked ",
    " Key was rejected by service ",
    " Owner died ",
    "State not recoverable",
    "UNKNOW_ERROR",
    "Wrong pallete" 
};

void handle_error(read_error_code_t errno_par) {
    printf("Error%d",errno_par);
    printf("Error:%s", read_error_message[errno_par]);
}

void check(bmp_header h) {
    printf("%d\n",  h.bfType);
    printf("%d\n",  h.bfileSize);
    printf("%d\n",  h.bfReserved);
    printf("%d\n",  h.bOffBits);
    printf("%d\n",  h.biSize);
    
    printf("%d\n",  h.biWidth);
    printf("%d\n",  h.biHeight);
    printf("%d\n",  h.biPlanes);
    printf("%d\n",  h.biBitCount);
    printf("%d\n",  h.biCompression);
    printf("%d\n",  h.biSizeImage);
    printf("%d\n",  h.biXPelsPerMeter);
    printf("%d\n",  h.biYPelsPerMeter);
    printf("%d\n",  h.biClrUsed);
    printf("%d\n",  h.biClrImportant);
}


int padding_size(uint32_t biWidth) {
    int b_size = biWidth*sizeof(pixel_t);
    if(b_size%4 == 0) {return 0;}
    else{return 4-b_size%4;}
}

read_error_code_t from_bmp(FILE* fp,image_t*  image_info) {
    size_t coint_param;
    bmp_header header;
    int i;
    pixel_t*  shift_mem;
    switch (errno) {
        case 0:
        coint_param = fread(
        &header,
        sizeof(header), 1, fp
        );
        image_info->data=malloc(
        sizeof(pixel_t)*header.biHeight*header.biWidth
        );

        printf("Error:%d\n", errno);
        printf("coint_param:%lu\n", coint_param);
        prov(header);
        image_info->width=header.biWidth;
        printf("ширина:%d\n", image_info->width);
        image_info->height=header.biHeight;
        
        shift_mem=image_info->data;
        printf("shift_mem:%p\n",(void*)shift_mem);
        printf("padding_size%d\n", padding_size(header.biWidth));
        fseek(fp, header.bOffBits, SEEK_SET);
        printf("header.biBitCount:%d",header.biBitCount);
        if(header.biBitCount != 24) {
            return WRONG_PALLETE;
        }
        for(i=0; i<header.biHeight; i++) {
            fread(shift_mem,
            1,
            image_info->width*sizeof(pixel_t), fp);
            shift_mem=shift_mem+image_info->width;
            fseek(fp, padding_size(header.biWidth), SEEK_CUR);
        }
            return  READ_OK;
        case 1:
            return READ_INVALID_SIGNATURE;
        case 2:
            return READ_INVALID_BITS;
        case 3:
            return READ_INVALID_HEADER;
        case 4:
            return such_process;
        default:
            return UNKNOW_ERROR;
    }
    fclose(fp);
}

int get_pixel(uint32_t i, uint32_t j, image_t* image_info){
        return ((image_info->height-i-1)*image_info->width+j+1);
}

image_t rotate( image_t*  img, image_t*  img_copy ){
      uint32_t i, j;
      printf("Проверка:%p",(void*)img->data);
      printf("Проверка для пикселей:%02x", img->data[0].b);
      img_copy->width=img->height;
      img_copy->height=img->width;
    
      for(i = 0; i <img->height ; ++i) {
        for(j = 0; j < img->width; ++j) {        
            img_copy->data[get_pixel(j, i, img_copy)].r = img->data[get_pixel(i, j, img)].r;
            img_copy->data[get_pixel(j, i, img_copy)].g = img->data[get_pixel(i, j, img)].g; 
            img_copy->data[get_pixel(j, i, img_copy)].b = img->data[get_pixel(i, j, img)].b; 
            }
      }
    return *img_copy;
}

/* make a copy */
void copy_image_t(FILE* fp, image_t* image_info_copy){
    int i;
    pixel_t*  shift_mem;
    bmp_header header;
    fseek(fp, 0, SEEK_SET);
    fread(&header,
        sizeof(header), 1, fp
        );
    image_info_copy->width=header.biWidth;
    image_info_copy->height=header.biHeight;
    image_info_copy->data=malloc(
        sizeof(pixel_t)*header.biHeight*header.biWidth
        );

    shift_mem=image_info_copy->data;
    fseek(fp, header.bOffBits, SEEK_SET);
    for(i=0; i<header.biHeight; i++) {
        fread(shift_mem,1,
        image_info_copy->width*sizeof(pixel_t), fp);
        shift_mem=shift_mem+image_info_copy->width;
        fseek(fp, padding_size(header.biWidth), SEEK_CUR);
    }
}

void to_bmp(FILE* out, image_t const* image_info){
    /*size_t coint_param;*/
    int i /*count_header, count_body*/;
    pixel_t*  shift_mem;
    bmp_header header;

    header.bfType=0x4D42;
    header.bfileSize=sizeof(header)+image_info->height*image_info->width*sizeof(pixel_t)+(padding_size(image_info->width))*image_info->height;
    header.bfReserved=0;
    header.bOffBits=sizeof(header);
    header.biSize=0x28;

    header.biWidth=image_info->width;
    header.biHeight=image_info->height;
    header.biPlanes=1;
    header.biBitCount=24;
    header.biCompression=0;
    header.biSizeImage=image_info->height*image_info->width*sizeof(pixel_t)+(4-image_info->width%4)*image_info->height;
    header.biXPelsPerMeter=0;
    header.biYPelsPerMeter=0;
    header.biClrUsed=0;
    header.biClrImportant=0;
    fseek(out, 0, SEEK_SET);
    fwrite(&header, sizeof(bmp_header), 1, out);
    shift_mem=image_info->data;

    fseek(out, sizeof(bmp_header), SEEK_SET);
    for(i=0; i<(image_info->height); i++) {
        fwrite(shift_mem,sizeof(char), image_info->width*3, out);

        shift_mem=shift_mem+image_info->width;

        fseek(out, padding_size(image_info->width), SEEK_CUR);
    }
}

int main( int argc, char** argv ) {
    FILE *fp;
    FILE *p_return_file;
    read_error_code_t error_reading;
    image_t image_info;
    image_t image_info_copy; 
    image_t image_info_copy2; 
    
    image_info.data = 0;

    fp = fopen("test.bmp", "rb" );
    p_return_file= fopen("test1.bmp", "wb" );
    
    error_reading = from_bmp(fp, &image_info);
    handle_error(error_reading);
     
    if(error_reading !=0) {
        abort();
    }
        
    copy_image_t(fp, &image_info_copy);
    copy_image_t(fp, &image_info_copy2);
    
    rotate(&image_info, &image_info_copy);
    rotate(&image_info_copy, &image_info_copy2);
    
    to_bmp(p_return_file, &image_info_copy2);
    
    if (image_info.data != 0) {   
        free(image_info.data);
        image_info.data = 0;
    }
    fclose(p_return_file);
    return 0;
}