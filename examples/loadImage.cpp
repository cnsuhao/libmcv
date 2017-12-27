#include <iostream>

#include "../src/modules/Image/Image.h"

int main() {
    Image image = Image();
    image.loadFile("./test.jpg");
    
    return 0;
}