#include <stdint.h>
#include <iostream>
#include <fstream>
#include "headers.hpp"

namespace BitMapManipulator{

void Header::fromfStream(std::ifstream& imageFile) {
    
    imageFile.read((char *) this,sizeof(Header));
    if (!imageFile) {
        return; /*exception*/
    }
    if (signature != BMPmagic) {
        return; /*exception*/
    }
    size_t pos = imageFile.tellg();
    imageFile.seekg(0, std::ios::end);
    size_t end = imageFile.tellg();
    imageFile.seekg(pos, std::ios::beg);
    if (sizeOfFile != end) {
            return; /*exception*/
    }
    
    
}

void DIBHeader::fromfStream(std::ifstream& imageFile) {
    
    imageFile.read((char *) this, sizeof(DIBHeader));
    if (!imageFile) {
        return; /*exception*/
    }
    if(this->sizeOfHeader != sizeof(*this)) {
        return; /*exception*/
    }
    if (this->bitesPerPixel != 8 && this->bitesPerPixel != 24) {
        return; /*exception*/
    }
    if (compressionIndex1 != 0 || compressionIndex2 != 0 || constant != 1) {
        return; /*exception*/
    }
    if (this->colorsInColorPallete != 0 && this->bitesPerPixel != 8) {
        return; /*exception*/
    }

}

}