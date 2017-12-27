#include "Image.h"

Image::Image() {

}

unsigned int Image::getWidth() {
    return width;
}

unsigned int Image::getHeight() {
    return height;
}

unsigned int Image::getSize() {
    return size;
}

unsigned char* Image::loadFile(std::string filename) {
    // Only Support JPEG File right away
    struct jpeg_decompress_struct cinfo;
    struct libmcv_jpeg_error_mgr jerr;

    FILE *infile;
    JSAMPARRAY buffer;
    int row_stride;
    int rgb_size;
    unsigned char * tmp_buffer = NULL;

    if(NULL == (infile=fopen(filename.c_str(),"rb"))) {
        printf("can't open %s\n", filename.c_str());
        return NULL;
    }
    
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = libmcv_jpeg_error_exit;
    
    if(setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        jpeg_stdio_src(&cinfo,infile);
        return NULL;
    }
    
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo,infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    
    row_stride = cinfo.output_width * cinfo.output_components;
    this->width = cinfo.output_width;
    this->height = cinfo.output_height;
    // Total Size
    rgb_size = row_stride * cinfo.output_components;
    this->size = rgb_size;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride,1);
    // Allocate Memory
    *this->data= (unsigned char*) malloc(sizeof(char)* rgb_size);
    // Print Result if it is in Debug Mode
    if (_LIBMCV_DEV_MODE){
        printf("debug--:\nrgb_size: %d, size %d, width: %d, height: %d, row_stride: %d\n",rgb_size,
        cinfo.image_width*cinfo.image_height*3,
        cinfo.image_width,
        cinfo.image_height,
        row_stride);
    }
    tmp_buffer = *this->data;
    while(cinfo.output_scanline < cinfo.output_height) {
        // get every line
        jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(tmp_buffer, buffer[0], row_stride);
        tmp_buffer += row_stride;
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return NULL;
}

Image::~Image() {

}