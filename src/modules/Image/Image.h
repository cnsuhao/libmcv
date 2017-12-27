#ifndef _LIBMCV_MODULES_IMAGE_H_
#define _LIBMCV_MODULES_IMAGE_H_

#include <iostream>
#include "../../../lib/libjpeg-turbo/jpeglib.h"
#include "../../../lib/libjpeg-turbo/jerror.h"

class Image{
private:
    unsigned int width;
    unsigned int height;
    unsigned int size;
public:
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getSize();
    void loadFile(std::string filename);
};

#endif