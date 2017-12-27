#include "Image.h"

unsigned int Image::getWidth() {
    return width;
}

unsigned int Image::getHeight() {
    return height;
}

unsigned int Image::getSize() {
    return size;
}

void Image::loadFile(std::string filename) {
    // Only Support JPEG File right away
    struct jpeg_compress_struct cinfo;

}