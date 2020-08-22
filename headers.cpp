#include "headers.hpp"

namespace BitMapManipulator{

void Header::fromfStream(std::ifstream& imageFile) {
    if (!imageFile) {
        return; /*exception*/
    }
    imageFile.read((char *) this,sizeof(Header));
   
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
    if (!imageFile) {
        return; /*exception*/
    }
    imageFile.read((char *) this, sizeof(DIBHeader));

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