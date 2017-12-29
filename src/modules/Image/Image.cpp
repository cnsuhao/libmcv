#include "Image.h"

Image::Image() {

}

bool Image::isGray() {
    return _isGray;
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

    std::shared_ptr<spdlog::logger> logger = Logger::getLogger();

    if(NULL == (infile=fopen(filename.c_str(),"rb"))) {
        printf("can't open %s\n", filename.c_str());
        return NULL;
    }
    
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = libmcv_jpeg_error_exit;
        logger->info("error heppened");

    if(setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        jpeg_stdio_src(&cinfo,infile);
        return NULL;
    }
    
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo,infile);
    jpeg_read_header(&cinfo, true);
    jpeg_start_decompress(&cinfo);
    
    row_stride = cinfo.output_width * cinfo.output_components;
    this->width = cinfo.output_width;
    this->height = cinfo.output_height;
    // Total Size
    rgb_size = row_stride * cinfo.output_components;
    this->size = rgb_size;
    logger->info("Setting buffer");
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride,1);
    logger->info("seted buffer");
    // Allocate Memory
    if(cinfo.output_components == 3) {
        this->_isGray = false;
        this->data = new unsigned char[width*height*3+1];
    } else {
        this->_isGray = true;
        this->data = new unsigned char[width*height+1];
    }
    // Print Result if it is in Debug Mode
        logger->info("image loaded: rgb_size: {:08d}, size {:08d}, width: {:08d}, height: {:08d}, row_stride: {:08d}",rgb_size,
        cinfo.image_width*cinfo.image_height*3,
        cinfo.image_width,
        cinfo.image_height,
        row_stride);
    while(cinfo.output_scanline < cinfo.output_height) {
        // get every line
        jpeg_read_scanlines(&cinfo, buffer, 1);
        for (size_t i=0; i<cinfo.output_width;i++) {
            if(this->isGray()) {
                this->data[(cinfo.output_scanline - 1 ) * this->width + i ] = buffer[0][i];
            } else {
                this->data[(cinfo.output_scanline - 1) * this->width*3 + i*3] = buffer[0][i * 3];
                this->data[(cinfo.output_scanline - 1) * this->width*3 + i*3 + 1] = buffer[0][i*3+1];
                this->data[(cinfo.output_scanline - 1) * this->width*3 + i*3 + 2] = buffer[0][i*3+2];
            }
        }
    }
    logger->info("image load finished!");
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return NULL;
}

Image::~Image() {

}