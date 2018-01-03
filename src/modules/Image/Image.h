#ifndef _LIBMCV_MODULES_IMAGE_H_
#define _LIBMCV_MODULES_IMAGE_H_

#ifndef _LIBMCV_DEV_MODE
#define _LIBMCV_DEV_MODE true
#endif

#include <iostream>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../lib/libjpeg-turbo/jpeglib.h"
#include "../../../lib/libjpeg-turbo/jerror.h"
#include "../Logger/Logger.h"

struct libmcv_jpeg_error_mgr {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

typedef struct libmcv_jpeg_error_mgr * libmcv_jpeg_error_ptr;

void libmcv_jpeg_error_exit(j_common_ptr cinfo) {
    libmcv_jpeg_error_ptr libmcv_jpeg_error = (libmcv_jpeg_error_ptr) cinfo->err;
    (*cinfo->err->output_message) (cinfo);
    longjmp(libmcv_jpeg_error->setjmp_buffer,1);
}

class Image {
private:
    bool _isGray;
    unsigned int width;
    unsigned int height;
    unsigned int size;
    unsigned char * data;
public:
    Image();
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getSize();
    bool isGray();
    unsigned char* loadFile(std::string filename);
    ~Image();
};

#endif